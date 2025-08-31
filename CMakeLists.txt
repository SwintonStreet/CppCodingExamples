cmake_minimum_required(VERSION 3.24)

# set the project name and version
project(CPP_Examples VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify the C++ compiler to be clang
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add extra flags
string(CONCAT CLANG_COVERAGE_COMPILE_FLAGS
       " -g"
       " -Werror"
       " -Wall"
       " -Wextra"
       " -Wpedantic"
       " -Wshadow"
       " -Wnon-virtual-dtor"
       " -Wold-style-cast"
       " -Wcast-align"
       " -Wunused"
       " -Woverloaded-virtual"
       " -Wconversion"
       " -Wsign-conversion"
       " -Wnull-dereference"
       " -Wdouble-promotion"
       " -Wformat=2"
       " -fsanitize=address"
       " -fno-omit-frame-pointer")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CLANG_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CLANG_COVERAGE_LINK_FLAGS}")

# add sub directories
add_subdirectory(atomic)
add_subdirectory(mutex)
