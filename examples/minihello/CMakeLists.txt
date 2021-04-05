cmake_minimum_required (VERSION 3.8)

set(NAME minihello)
project (${NAME})

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ../../gempyrelib/include
    include
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    gui/${NAME}.html
    )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/gui/minihello.html
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )

target_link_libraries (${PROJECT_NAME}  PRIVATE "$<TARGET_FILE:gempyre>" "$<TARGET_PROPERTY:gempyre,socket_lib>")



