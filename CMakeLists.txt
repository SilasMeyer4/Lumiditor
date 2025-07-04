cmake_minimum_required(VERSION 3.31.0)
project(LUMIDITOR VERSION 0.1.0 LANGUAGES C CXX)

find_package(raylib CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

enable_testing()

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE TEST_FILES "tests/*.cpp")
add_executable(LUMIDITOR ${SRC_FILES})


target_include_directories(LUMIDITOR PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(LUMIDITOR PRIVATE raylib)




add_executable(tests ${TEST_FILES})

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE GTest::gtest GTest::gmock raylib)

add_test(NAME MyButtonTest COMMAND tests)