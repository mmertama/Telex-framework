cmake_minimum_required (VERSION 3.16)

set(NAME snowflakes)
project (${NAME}test)

include(../../scripts/addResource.cmake_script)

set(CMAKE_CXX_STANDARD 17)

include_directories(
     ../../gempyrelib/include
    include
)

#maybe only for msvc, but shall not hurt..
add_compile_options(-D_USE_MATH_DEFINES)
#find_package (gempyre REQUIRED PATHS ../..)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/koch.cpp
    src/koch.h
    gui/${NAME}.html
    )

addResource(PROJECT ${PROJECT_NAME} TARGET include/${NAME}_resource.h SOURCES gui/${NAME}.html)

target_link_libraries (${PROJECT_NAME}  PRIVATE "$<TARGET_FILE:gempyre>" "$<TARGET_PROPERTY:gempyre,socket_lib>")



