# - Try to find LibreSSL

# Variables defined by this module:
#
# LIBRESSL_FOUND System has LibreSSL, include and library dirs found
# LIBRESSL_INCLUDE_DIR The LibreSSL include directories.
# LIBRESSL_LIBRARIES The LibreSSL libraries.
# LIBRESSL_CYRPTO_LIBRARY The LibreSSL crypto library.
# LIBRESSL_SSL_LIBRARY The LibreSSL ssl library.


find_path(LIBRESSL_ROOT_DIR
NAMES include/openssl/ssl.h
)

find_path(
  LibreSSL_INCLUDE_DIR
  NAMES openssl/ssl.h
  HINTS ${LIBRESSL_ROOT_DIR}/include
)

find_library(
  LibreSSL_SSL_LIBRARY
  NAMES ssl ssleay32 ssleay32MD 
  HINTS ${LIBRESSL_ROOT_DIR}/lib
)

find_library(
  LibreSSL_CRYPTO_LIBRARY
  NAMES crypto
  HINTS ${LIBRESSL_ROOT_DIR}/lib
)
set(LibreSSL_LIBRARIES ${LibreSSL_SSL_LIBRARY} ${LibreSSL_CRYPTO_LIBRARY}

CACHE STRING "LibreSSL libraries" FORCE)

message("ssl:   ${LibreSSL_SSL_LIBRARY}")
message("crypto:  ${LibreSSL_CRYPTO_LIBRARY}")

message("${LIBRESSL_ROOT_DIR}")
message("${LibreSSL_INCLUDE_DIR}")
message("${LibreSSL_LIBRARIES}")
message("${LibreSSL_CRYPTO_LIBRARY}")
message("${LibreSSL_SSL_LIBRARY}")

# stdout
mark_as_advanced(
    LibreSSL_ROOT_DIR
    LibreSSL_INCLUDE_DIR
    LibreSSL_LIBRARIES
    LibreSSL_CRYPTO_LIBRARY
    LibreSSL_SSL_LIBRARY
)
