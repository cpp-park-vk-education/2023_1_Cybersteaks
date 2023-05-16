add_library(app src/app.cpp)

target_include_directories(app PUBLIC include)
target_link_libraries(app feedView)
target_link_libraries(app store)