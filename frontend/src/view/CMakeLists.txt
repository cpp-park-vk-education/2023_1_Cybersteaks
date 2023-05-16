add_library(feedView src/feedView.cpp)
target_include_directories(feedView PUBLIC include)
target_link_libraries(feedView model)