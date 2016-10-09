set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/encrypt/base64.cpp
    ${PROJECT_SOURCE_DIR}/src/encrypt/encrypt.cpp
    ${PROJECT_SOURCE_DIR}/src/encrypt/hash.cpp
    ${PROJECT_SOURCE_DIR}/src/http/http_client.cpp
    ${PROJECT_SOURCE_DIR}/src/http/http_method.cpp
)

add_library(
    ${PROJECT_NAME}
    OBJECT
    ${SOURCES}
)
add_executable(
    ${PROJECT_NAME}-bin
    $<TARGET_OBJECTS:${PROJECT_NAME}>
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

# if linux.
#target_link_libraries(${PROJECT_NAME}-bin ${Boost_LIBRARIES})

target_link_libraries(${PROJECT_NAME}-bin ${LibreSSL_LIBRARIES})

include_directories (${INCLUDE_ROOT_DIR})
