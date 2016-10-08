#include "hash.h"

#include <openssl/md5.h>
#include <openssl/sha.h>

#define GENERATE_HASH_FUNC(METHOD)                                      \
std::vector <byte> hashCalculation_##METHOD(const std::vector <byte>& data) {  \
    METHOD##_CTX ctx;                                                   \
    std::vector <byte> buf(##METHOD##_DIGEST_LENGTH);                   \
    if (!##METHOD##_Init(&ctx)) { return {}; }                            \
    if (!##METHOD##_Update(&ctx, data.data(), data.size())) { return{};}    \
    if (!##METHOD##_Final(buf.data(), &ctx)) {return {};}                \
    return buf;                                                         \
}

namespace flowTumn {
    GENERATE_HASH_FUNC(SHA256);
    GENERATE_HASH_FUNC(SHA512);
    GENERATE_HASH_FUNC(MD5);
};
