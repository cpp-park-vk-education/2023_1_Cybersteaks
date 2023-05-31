add_library(web src/web.cpp)
target_include_directories(web PUBLIC include)

add_library(orm src/orm.cpp)
target_include_directories(orm PUBLIC include)