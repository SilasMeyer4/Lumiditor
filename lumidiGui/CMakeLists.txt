file(GLOB_RECURSE GUI_SRC "src/*.cpp")
add_library(lumidiGui STATIC ${GUI_SRC})
find_package(raylib CONFIG REQUIRED)

# component Headers
target_include_directories(lumidiGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/components)
target_include_directories(lumidiGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/colliders)
target_include_directories(lumidiGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/events)


target_link_libraries(lumidiGui PRIVATE raylib)