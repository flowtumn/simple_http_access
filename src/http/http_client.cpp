#include "http_client.h"

namespace flowTumn {
    class HttpClient::impl {
    public:
        impl(
            std::string host,
            boost::asio::io_service& ioService,
            size_t receiveSize,
            bool ssl
        )
            : host_(std::move(host))
            , ioService_(ioService)
            , resolver_(ioService_)
            , context_(ioService_, boost::asio::ssl::context::sslv23_client)
            , sslStream_(ioService_, context_)
            , receiveSize_{receiveSize}
            , ssl_{ ssl }
            , ready_{ false }
        {
            this->resolver_.async_resolve(
                { this->host_, (this->ssl_ ? "https" : "http")},
                [this](const boost::system::error_code& err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
                    this->handler_resolve(err, endpoint_iterator);
                }
            );
        }

        bool ready() const {
            return this->ready_;
        }

        bool sendRequest(
            std::string path,
            Http::Method method,
            const std::vector <std::string>& httpHeader,
            const std::map <std::string, std::string>& query,
            std::function <void()> complete_handler
        ) {
            if (!this->ready_) {
                return false;
            }

            auto request = std::make_shared <boost::asio::streambuf> ();
            std::ostream request_stream(request.get());

            request_stream << flowTumn::toStr(method) << "   " << path << "  " << "HTTP/1.0\r\n";
            request_stream << "Host: " << this->host_ << "\r\n";

            for (auto&& each : httpHeader) {
                request_stream << each << "\r\n";
            }

            request_stream << "\r\n";

            bool f{ false };
            for (auto&& each : query) {
                if (f) {
                    request_stream << "&";
                }
                request_stream << each.first << "=" << each.second;
                f = true;
            }

            // send a request.
            boost::asio::async_write(
                this->sslStream_,
                *request,
                [this, request, complete_handler](const boost::system::error_code& ec, int64_t sentSize) {
                    if (!ec)  {
                        complete_handler();
                    }
                }
            );

            return true;
        }

        void receive(flowTumn::HttpClient::ReciveHandler handler) {
            auto buf = std::make_shared <flowTumn::HttpClient::BufferType> (this->receiveSize_);

            boost::asio::async_read(
                this->sslStream_,
                boost::asio::buffer(buf->data(), this->receiveSize_),
                boost::asio::transfer_at_least(this->receiveSize_),
                [handler, buf](const boost::system::error_code& ec, size_t receivedSize) {
                    handler(ec, buf, receivedSize);
                }
            );
        }

    private:
        void handler_sent(
            const boost::system::error_code& errCode,
            std::shared_ptr <boost::asio::streambuf> data
        ) {
            if (!errCode) {
            }
        }

        void handler_resolve(
            const boost::system::error_code& errCode,
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator
        ) {
            if (!errCode) {
                boost::system::error_code ec;
                this->sslStream_.lowest_layer().async_connect(
                    *endpoint_iterator,
                    [this](const boost::system::error_code& ec) {
                        this->handler_connect(ec);
                    }
                );
            }
            this->errCode_ = errCode;
        }

        void handler_connect(const boost::system::error_code& errCode) {
            if (!errCode) {
                if (this->ssl_) {
                    this->sslStream_.async_handshake(
                        boost::asio::ssl::stream_base::client,
                        [this](const boost::system::error_code& ec) {
                            this->handler_handshake(ec);
                        }
                    );
                } else {
                    this->ready_ = true;
                }
            }
            this->errCode_ = errCode;
        }

        void handler_handshake(const boost::system::error_code& errCode) {
            if (!errCode) {
                this->ready_ = true;
            }
            this->errCode_ = errCode;
        }

    private:
        std::string host_;
        boost::asio::io_service& ioService_;
        boost::asio::ip::tcp::resolver resolver_;
        boost::asio::ssl::context context_;
        boost::asio::ssl::stream <boost::asio::ip::tcp::socket> sslStream_;
        std::function <void()> handler_;
        boost::system::error_code errCode_;
        size_t receiveSize_;
        bool ssl_;
        bool ready_;
    };

    HttpClient::HttpClient(
        std::string host,
        boost::asio::io_service& ioService,
        size_t receiveSize,
        bool ssl
    )
    : impl_(
        std::make_unique <flowTumn::HttpClient::impl>(
            std::move(host),
            ioService,
            receiveSize,
            ssl
        )
    )
    {}

    HttpClient::~HttpClient() = default;

    bool HttpClient::ready() const {
        return this->impl_->ready();
    }

    bool HttpClient::sendRequest(
        std::string path,
        Http::Method method,
        const std::vector <std::string>& httpHeader,
        const std::map <std::string, std::string>& query,
        std::function <void()> complete_handler
    ) {
        return this->impl_->sendRequest(
            path,
            method,
            httpHeader,
            query,
            complete_handler
        );
    }

    void HttpClient::receive(flowTumn::HttpClient::ReciveHandler handler) {
        this->impl_->receive(handler);
    }
};
