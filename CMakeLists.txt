cmake_minimum_required(VERSION 2.8)
project(secret_message)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/command)

add_executable(${PROJECT_NAME}
        src/command/build.cpp
        src/command/build.h
        src/command/write.cpp
        src/command/write.h
        src/tool/arch.h
        src/main.cpp
        src/file/read.h
        src/file/wave.cpp
        src/file/wave.h src/tool/range_to_initializer_list.h)
