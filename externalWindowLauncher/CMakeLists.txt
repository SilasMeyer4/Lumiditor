add_library(externalWindowLauncher STATIC launcher.cpp)
target_include_directories(externalWindowLauncher PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)