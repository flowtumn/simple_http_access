# cmake -DCMAKE_MODULE_PATH=/path/to -DLIBRESSL_ROOT_DIR=/path/to -DBOOST_ROOT=/path/to -DBOOST_LIBRARYDIR=/path/to
cmake_minimum_required(VERSION 2.8.8)

message("module:   ${CMAKE_MODULE_PATH}")
find_package(LibreSSL)

if (LibreSSL_FOUND)
  message("SSL OK:   ")
endif()

#if (LibreSSL_FOUND)
#    message("SSL OK:   ")
#else()
#  message("NG")
#endif()

#project("simple_http_access")
#
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#
## boost find.
#find_package(Boost 1.6.1 REQUIRED COMPONENTS regex filesystem system)
#IF(Boost_FOUND)
#    message("BOSST OK")
#    message("BOOST-header: ${Boost_INCLUDE_DIRS}")
#    message("BOOST-library: ${Boost_LIBRARIES}")
#endif()
#
#find_package(LibreSSL)
#find_package(OpenSSL)
#
#message("OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
##message("OpenSSL libraries: ${OPENSSL_LIBRARIES}")
