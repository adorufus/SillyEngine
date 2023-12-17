cmake_minimum_required(VERSION 3.13)
project(rendering_engine)

set(CMAKE_CXX_STANDARD 14)

include_directories(core)
include_directories(includes)
include_directories(includes/glad)
include_directories(includes/GLFW)
include_directories(includes/KHR)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)


add_executable(rendering_engine
        core/Shader.cpp
        core/Shader.h
        includes/glad/glad.h
        includes/GLFW/glfw3.h
        includes/GLFW/glfw3native.h
        includes/KHR/khrplatform.h
        glad.c
        main.cpp)

target_link_libraries(rendering_engine glfw)
target_link_libraries(rendering_engine OpenGL::GL)


