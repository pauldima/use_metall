cmake_minimum_required(VERSION 3.18)
project(use_metall)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
include(FetchContent)

# fmt
find_package(fmt REQUIRED)

# boost
find_package(Boost REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# metall is not available from conan
# todo include metall, e.g. via FetchContent_Declare https://cmake.org/cmake/help/latest/module/FetchContent.html

FetchContent_Declare(
  metall
  GIT_REPOSITORY https://github.com/dice-group/metall.git
)

FetchContent_MakeAvailable(metall)

add_executable(write_data write_data.cpp)
include_directories(${Boost_INCLUDE_DIR} ${fmt_INCLUDE_DIR})
target_include_directories(write_data 
PUBLIC
${metall_SOURCE_DIR}/include
)
target_link_libraries(write_data
fmt::fmt
Boost::Boost
Threads::Threads
)

add_executable(read_data read_data.cpp)
target_include_directories(read_data 
PUBLIC
${metall_SOURCE_DIR}/include
)
target_link_libraries(read_data
fmt::fmt
Boost::Boost
Threads::Threads
)

