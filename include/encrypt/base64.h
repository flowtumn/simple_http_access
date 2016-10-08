#ifndef BASE64_H_INCLUDE__
#define BASE64_H_INCLUDE__

#include <string>
#include <vector>

using byte = unsigned char;

namespace flowTumn {
    namespace base64 {
        std::string encode(const std::vector <byte>& source);
        std::vector <byte> decode(const std::string& source);
    };
};

#endif // BASE64_H_INCLUDE__
