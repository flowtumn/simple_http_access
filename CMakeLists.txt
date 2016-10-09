cmake_minimum_required(VERSION 2.8.12)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions("/Zi /W4")
    if (${UNICODE})
        add_definitions(-DUNICODE -D_UNICODE)
    endif ()

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -pthread -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++1y -O3 -pthread -Wall -Wextra")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++1y -O3 -Wall -Wextra")
endif ()


set(PROJECT_NAME simple_http_access)


find_package(LibreSSL)

message("SSL:   ${LIBRESSL_INCLUDE_DIR}")
include_directories(${LIBRESSL_INCLUDE_DIR})

# boost find.
find_package(Boost 1.6.1 REQUIRED COMPONENTS regex filesystem system)
if (Boost_FOUND)
    message("BOSST OK")
    message("BOOST-header: ${Boost_INCLUDE_DIRS}")
    message("BOOST-library: ${Boost_LIBRARIES}")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

enable_testing()

set(INCLUDE_ROOT_DIR "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)
add_subdirectory(test)

