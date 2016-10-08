#include "encrypt/base64.h"

#include <cstdint>
#include <stdexcept> 

namespace {
    static const char* TABLE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    inline std::string convBase64(byte b1, byte b2, byte b3, int cnt) {
        const int32_t V = (b1 << 16) | (b2 << 8) | (b3);
        std::string result;
        std::vector <byte> v{
            static_cast <byte> ((V >> 18) & 0x3F),
            static_cast <byte> ((V >> 12) & 0x3F),
            static_cast <byte> ((V >> 6) & 0x3F),
            static_cast <byte> ((V) & 0x3F),
        };

        //3文字で4文字になるので、+1しておく
        ++cnt;
        for (auto&& each : v) {
            if (0 <= --cnt) {
                result += TABLE[each];
            } else {
                result += '=';
            }
        }

        return result;
    }

};

namespace flowTumn {
    namespace base64 {
        std::string encode(const std::vector <byte>& source) {
            std::string result{};
            byte w[3]{};
            int idx{ 0 };

            for (auto&& each : source) {
                w[idx++] = each;
                if (3 == idx) {
                    result += convBase64(w[0], w[1], w[2], idx);
                    idx = 0;
                    w[0] = w[1] = w[2] = 0;
                }
            }

            result += convBase64(w[0], w[1], w[2], idx);
            return result;
        }

        std::vector <byte> decode(const std::string& source) {
            if (source.size() & 0x03) {
                //4の倍数で無いとダメ
                throw std::invalid_argument("invalid a decode source.");
            }

            std::vector <byte> result;
            byte v[0xff + 1];

            for (byte i = 0; i < 64; ++i) {
                v[TABLE[i]] = i;
            }

            auto size = source.size();
            for (decltype(size) i = 0; i < size; i += 4) {
                int32_t vv{ 0 };
                int32_t depth{ 0 };
                bool fin{ false };

                for (int j = 0; j < 4; ++j) {
                    auto c = source.at(i + j);
                    if ('=' != c) {
                        vv = vv << 6;
                        vv = vv | (v[c]);
                        depth += 6;
                    }
                    else {
                        fin = true;
                        break;
                    }
                }

                while (0 < depth) {
                    result.emplace_back(vv >> (depth - 8));
                    depth -= 8;
                    if (fin && depth < 8) {
                        break;
                    }
                }
            }

            return result;
        }
    };
};
