#include "encrypt.h"

#include <openssl/evp.h>
#include <openssl/aes.h>

namespace flowTumn {
    namespace AES256 {
        std::vector <byte> encrypt(
            const std::vector <byte>& key,
            const std::vector <byte>& data,
            const std::vector <byte>& iv
        ) {
            EVP_CIPHER_CTX ctx;
            std::vector <byte> result;
            int32_t encryptSize{ 0 };
            int32_t destSize = data.size();

            EVP_CIPHER_CTX_init(&ctx);
            EVP_EncryptInit_ex(&ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data());

            result.resize(destSize + EVP_MAX_BLOCK_LENGTH);

            //encrypt
            if (EVP_EncryptUpdate(&ctx, result.data(), &destSize, data.data(), data.size())) {
                encryptSize += destSize;
                EVP_EncryptFinal_ex(&ctx, result.data() + destSize, &destSize);
                encryptSize += destSize;

                //整える。
                result.erase(std::begin(result) + encryptSize, std::end(result));
            }

            EVP_CIPHER_CTX_cleanup(&ctx);

            return result;
        }

        std::vector <byte> decrypt(
            const std::vector <byte>& key,
            const std::vector <byte>& data,
            const std::vector <byte>& iv
        ) {
            EVP_CIPHER_CTX ctx;
            std::vector <byte> result;
            int32_t encryptSize{ 0 };
            int32_t destSize = data.size();

            EVP_CIPHER_CTX_init(&ctx);
            EVP_DecryptInit_ex(&ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data());

            result.resize(destSize + EVP_MAX_BLOCK_LENGTH);

            //decrypt
            if (EVP_DecryptUpdate(&ctx, result.data(), &destSize, data.data(), data.size())) {
                encryptSize += destSize;
                EVP_DecryptFinal_ex(&ctx, result.data() + destSize, &destSize);
                encryptSize += destSize;

                //整える。
                result.erase(std::begin(result) + encryptSize, std::end(result));
            }

            EVP_CIPHER_CTX_cleanup(&ctx);

            return result;
        }
    };

};
