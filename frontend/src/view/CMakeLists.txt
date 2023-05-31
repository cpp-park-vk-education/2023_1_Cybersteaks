add_library(feedView src/feedView.cpp)
target_include_directories(feedView PUBLIC include)
target_link_libraries(feedView model)

add_library(loginView src/loginView.cpp)
target_include_directories(loginView PUBLIC include)
target_link_libraries(loginView model)

add_library(userView src/userView.cpp)
target_include_directories(userView PUBLIC include)
target_link_libraries(userView model)
target_link_libraries(userView postView)

add_library(postView src/postView.cpp)
target_include_directories(postView PUBLIC include)
target_link_libraries(postView model)