add_library(ORM src/ORMGenerator.cpp)

target_include_directories(ORM PUBLIC include)
target_link_libraries(ORM mysql-connector-cpp-build/lib64/libmysqlcppconn8.so)
