cmake_minimum_required(VERSION 3.16)
project(pacc C)

file(GLOB_RECURSE SOURCES "src/*.c")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(pacc ${SOURCES})

target_include_directories(pacc PRIVATE
    include
    "${CMAKE_SOURCE_DIR}/external/libmkdir"
    libpacc
)

target_compile_options(pacc PRIVATE -g -O0)
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pacc PRIVATE -fsanitize=address)
    target_link_options(pacc PRIVATE -fsanitize=address)
endif()

