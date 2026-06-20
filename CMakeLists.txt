cmake_minimum_required(VERSION 4.2)
project(RayLibParticle)

set(CMAKE_CXX_STANDARD 23)

find_package(raylib REQUIRED)

add_executable(RayLibParticle main.cpp)

target_link_libraries(RayLibParticle PRIVATE raylib)