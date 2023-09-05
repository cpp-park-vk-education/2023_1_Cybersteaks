cmake_minimum_required(VERSION 3.0.0)
project(INCrea_ORM VERSION 0.1.0)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")

add_executable(INCrea_ORM src/ORM_test.cpp)

add_subdirectory(src/ORM)

target_link_libraries(INCrea_ORM ORM)