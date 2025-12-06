cmake_minimum_required(VERSION 3.16)
project(libpacc C)

file(GLOB_RECURSE SOURCES "src/*.c")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library({PROJECT_NAME})

target_include_directories({PROJECT_NAME} PRIVATE
    include
    "${CMAKE_SOURCE_DIR}/third_party"
)

target_compile_options({PROJECT_NAME} PRIVATE -g -O0)
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options({PROJECT_NAME} PRIVATE -fsanitize=address)
  target_link_options({PROJECT_NAME} PRIVATE -fsanitize=address)
endif()
