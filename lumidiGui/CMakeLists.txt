cmake_minimum_required(VERSION 3.14)
project(LumidiGui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Bibliothek bauen
file(GLOB_RECURSE GUI_SRC "src/*.cpp")
add_library(lumidiGui STATIC ${GUI_SRC})


# Header-Verzeichnisse (öffentlich, damit Tests sie auch sehen)
target_include_directories(lumidiGui PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include/components
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components/3D
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components/2D
    ${CMAKE_CURRENT_SOURCE_DIR}/include/colliders
    ${CMAKE_CURRENT_SOURCE_DIR}/include/fluentAPI
    ${CMAKE_CURRENT_SOURCE_DIR}/include/events
    ${CMAKE_CURRENT_SOURCE_DIR}/include/helpers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/colors
    ${CMAKE_CURRENT_SOURCE_DIR}/include/input
    ${CMAKE_CURRENT_SOURCE_DIR}/include/shapes
    ${CMAKE_CURRENT_SOURCE_DIR}/include/persistence
    ${CMAKE_CURRENT_SOURCE_DIR}/include/windows
)

    find_package(Lua REQUIRED)
    target_include_directories(lumidiGui PRIVATE ${LUA_INCLUDE_DIR})
    target_link_libraries(lumidiGui PRIVATE ${LUA_LIBRARIES})

        find_package(sol2 CONFIG REQUIRED)
target_link_libraries(lumidiGui PRIVATE sol2::sol2)


message(STATUS "lumidiGui source files: ${GUI_SRC}")

# raylib
find_package(raylib CONFIG REQUIRED)
target_link_libraries(lumidiGui PUBLIC raylib)

# lohman json
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(lumidiGui PRIVATE nlohmann_json::nlohmann_json)

# ========================
target_link_libraries(lumidiGui PRIVATE externalWindowLauncher)

# pugixml

find_package(pugixml CONFIG REQUIRED)
target_link_libraries(lumidiGui PRIVATE  pugixml::pugixml)
# ========================
# TESTS
# ========================
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    include(FetchContent)
    enable_testing()

    # GoogleTest herunterladen
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    # Testquellen
    file(GLOB_RECURSE TEST_SRC "tests/*.cpp")
    message(STATUS "TEST_SRC contains: ${TEST_SRC}")

    add_executable(runLumidiGuiTests ${TEST_SRC})

    target_include_directories(runLumidiGuiTests PRIVATE
  ${googletest_SOURCE_DIR}/googletest/include
  ${googletest_SOURCE_DIR}/googlemock/include
)

    target_link_libraries(runLumidiGuiTests
    lumidiGui
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

    include(GoogleTest)
    gtest_discover_tests(runLumidiGuiTests)
endif()
