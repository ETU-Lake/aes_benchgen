cmake_minimum_required(VERSION 3.13)
project(aes_benchgen)

set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "")
set(CMAKE_C_FLAGS_MINSIZEREL "")

set(BASE_COMPILE_OPTIONS -pipe -march=native -fcf-protection=full -fstack-protector-strong)
set(WARNINGS -Wall -Wextra -Wpedantic -Wuninitialized -Wundef -Wcast-align -Wstrict-overflow=2 -Wwrite-strings -Wno-format-nonliteral)
set(DEBUG_OPTIONS ${BASE_COMPILE_OPTIONS} -ggdb -g3 -O0)
set(RELEASE_OPTIONS ${BASE_COMPILE_OPTIONS} -O3)

set(CMAKE_C_STANDARD 99)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_LINK_WHAT_YOU_USE ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/self_aes.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/openssl_aes.c
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(OpenSSL 1.1.1 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME}
    PRIVATE ${WARNINGS}
    PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>" "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:NDEBUG>")
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:-s>")
