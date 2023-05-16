add_library(store src/store.cpp)
target_include_directories(store PUBLIC include)
target_link_libraries(store model)