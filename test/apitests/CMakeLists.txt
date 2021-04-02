cmake_minimum_required (VERSION 3.16)

include(GoogleTest)

project (apitests)
set(CMAKE_CXX_STANDARD 17)
include_directories(
     ../../gempyrelib/include
    include
    ${TEST_INCLUDE_DIR}
)


find_package (gempyre REQUIRED PATHS ../..)

add_executable(${PROJECT_NAME}
    apitests.cpp
    gui/${PROJECT_NAME}.html
    )

gtest_add_tests(TARGET ${PROJECT_NAME})

# add HTML into resources
addResource(PROJECT ${PROJECT_NAME}
    TARGET include/${PROJECT_NAME}_resource.h
    SOURCES gui/${PROJECT_NAME}.html)


# copy HTML to binary for tests
add_compile_definitions(TEST_HTML="${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.html")
configure_file(gui/${PROJECT_NAME}.html ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.html COPYONLY)

find_library(gtest PATHS ${TEST_LIBRARY_DIR})

target_link_libraries (${PROJECT_NAME} gempyre gtest)

