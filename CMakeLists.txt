cmake_minimum_required(VERSION 3.22)
project(sdl_bug CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(sdl_bug main.cpp)

add_subdirectory(SDL)

target_include_directories(sdl_bug PUBLIC SDL/include)

target_link_libraries(sdl_bug PRIVATE
    SDL3::SDL3
)
