cmake_minimum_required(VERSION 3.0.0)
project(ORM VERSION 0.1.0)
SET(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
INCLUDE_DIRECTORIES(/home/vfomenko/programming/technopark/2023_1_Cybersteaks/mysql-connector-cpp/build)

add_subdirectory(src/store)

add_executable(ORM src/main.cpp)

target_link_libraries(ORM app)
target_link_libraries(ORM /usr/local/lib/libwt.so )
