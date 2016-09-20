#ifndef HTTP_CLIENT_H_INCLUDE__
#define HTTP_CLIENT_H_INCLUDE__

#include <functional>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream.hpp>

#include "http_method.h"

namespace flowTumn {
    /**
     * HTTP/S‚ðˆµ‚¤Client
     */
    class HttpClient {
    public:
        using BufferType = std::vector <std::string::value_type>;
        using BufferPtr = std::shared_ptr <BufferType>;
        using SentCompleteHandler = std::function <void()>;
        using ReciveHandler = std::function <void(const boost::system::error_code&, BufferPtr, size_t)>;

        HttpClient(
            std::string host,
            boost::asio::io_service& ioService,
            size_t receiveSize = 512 * 1024,
            bool ssl = true
        );
        ~HttpClient();

        bool ready() const;

        bool sendRequest(
            std::string path,
            flowTumn::Http::Method method,
            const std::vector <std::string>& httpHeader,
            const std::map <std::string, std::string>& query,
            SentCompleteHandler complete_handler
        );

        void receive(ReciveHandler handler);

    private:
        class impl;
        std::unique_ptr <impl> impl_;
	};
};

#endif // HTTP_CLIENT_H_INCLUDE__
