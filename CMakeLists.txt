cmake_minimum_required(VERSION 3.11)
set(CMAKE_C_COMPILER "clang")

set(OpenGL_GL_PREFERENCE GLVND)

project(C_GLUT VERSION 0.0.1)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-Wall -Wextra -g")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(FREEGLUT_WAYLAND ON)

set(SOURCES main.c)

add_executable(main ${SOURCES})

# Добавим библиотеки к исполняемому файлу
target_link_libraries(main PUBLIC OpenGL::GL GLUT::GLUT m)
