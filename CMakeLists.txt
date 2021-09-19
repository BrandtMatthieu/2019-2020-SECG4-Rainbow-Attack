cmake_minimum_required(VERSION 3.10)
project(gen-passwd)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-lpthread -Wpedantic -Wall -Wextra -O3)

find_package(Threads REQUIRED)

add_executable(gen-passwd
        src/config.h
        src/hashing_thread.cpp
        src/hashing_thread.h
        src/help.cpp
        src/help.h
        src/infos.cpp
        src/infos.h
        src/main.cpp
        src/sha256.cpp
        src/sha256.hpp
        src/synchronized_writer.cpp
        src/synchronized_writer.hpp
        src/utils.cpp
        src/utils.h)

add_executable(gen-passwd_tests
        tests/tests.cpp
        src/utils.cpp
        src/utils.h)

target_link_libraries(gen-passwd ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(gen-passwd_tests ${CMAKE_THREAD_LIBS_INIT})
