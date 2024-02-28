cmake_minimum_required(VERSION 3.28)
project(weave)

set(SOURCES
	Main.cpp
	Renderer/Shader.cpp
	Core/Engine.cpp
	Core/GL.cpp
	Renderer/Renderer.cpp
    ../vendor/glad/glad.c
    ../vendor/stb_image/stb_image.c
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(../vendor/)
include_directories(../vendor/stb_image)
include_directories(Renderer)
include_directories(/lib/glm/)
include_directories(.)
include_directories(Core)

find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
