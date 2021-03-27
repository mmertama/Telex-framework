cmake_minimum_required (VERSION 3.16)

include(GoogleTest)

set(NAME apitests)
project (${NAME})
set(CMAKE_CXX_STANDARD 17)
include_directories(
     ../../gempyrelib/include
    include
    ${TEST_INCLUDE_DIRS}
)


find_package (gempyre REQUIRED PATHS ../..)

add_executable(${PROJECT_NAME}
    apitests.cpp
    gui/${NAME}.html
    )

gtest_add_tests(TARGET ${PROJECT_NAME})

addResource(PROJECT ${PROJECT_NAME}
    TARGET include/${NAME}_resource.h
    SOURCES gui/${NAME}.html)

target_link_libraries (${PROJECT_NAME} gempyre googletest)

