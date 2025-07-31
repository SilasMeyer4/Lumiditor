cmake_minimum_required(VERSION 3.31.0)
project(LUMIDITOR VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib CONFIG REQUIRED)

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
endif()


# Adding LumidiGui as a subdirectory
add_subdirectory(lumidiGui)
enable_testing()

# Lumidieditor
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(LUMIDITOR ${SRC_FILES})
target_include_directories(LUMIDITOR PRIVATE ${CMAKE_SOURCE_DIR}/include)


target_link_libraries(LUMIDITOR PRIVATE
    raylib
    lumidiGui
)
