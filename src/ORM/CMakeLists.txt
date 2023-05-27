add_library(ORM src/ORMGenerator.cpp src/ORMConnect.cpp)

target_include_directories(ORM PUBLIC include)
target_include_directories(ORM PUBLIC /usr/local/mysql/connector-c++-8.0.33/include)
target_link_libraries(ORM /usr/local/mysql/connector-c++-8.0.33/lib64/debug/libmysqlcppconn8.so.2)
