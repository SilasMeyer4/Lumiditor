add_executable(lumidiWindows main.cpp)
target_link_libraries(lumidiWindows PRIVATE raylib lumidiGui) # ggf. weitere libs

target_include_directories(lumidiWindows PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/dialog
)



set_target_properties(lumidiWindows PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)