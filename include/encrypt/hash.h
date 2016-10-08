#ifndef HASH_H_INCLUDE__
#define HASH_H_INCLUDE__

#include <vector>

using byte = unsigned char;

namespace flowTumn {
    std::vector <byte> hashCalculation_SHA256(const std::vector <byte>& data);
    std::vector <byte> hashCalculation_SHA512(const std::vector <byte>& data);
    std::vector <byte> hashCalculation_MD5(const std::vector <byte>& data);
};

#endif // HASH_H_INCLUDE__
