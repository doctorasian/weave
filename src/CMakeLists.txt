cmake_minimum_required(VERSION 3.28)
project(weave)

set(SOURCES
    main.cpp
    glad.c
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(../include)

find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
