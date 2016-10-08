#ifndef ENCRYPT_H_INCLUDE__
#define ENCRYPT_H_INCLUDE__

#include <vector>

using byte = unsigned char;

namespace flowTumn {
    // Cryptography to the AES256.
    namespace aes256 {
        std::vector <byte> encrypt(
            const std::vector <byte>& key,
            const std::vector <byte>& data,
            const std::vector <byte>& iv
        );

        std::vector <byte> decrypt(
            const std::vector <byte>& key,
            const std::vector <byte>& data,
            const std::vector <byte>& iv
        );
    };

};

#endif // ENCRYPT_H_INCLUDE__
