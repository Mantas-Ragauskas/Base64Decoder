cmake_minimum_required(VERSION 3.8)
project(Base64Decoder)

set(CMAKE_CXX_STANDARD 11)


include_directories(Base64Decoder/headers/)

set(SOURCE_FILES Base64Decoder/src/Base64Decoder.cpp
                 Base64Decoder/src/main.cpp
        )

add_executable(Base64Decoder ${SOURCE_FILES})