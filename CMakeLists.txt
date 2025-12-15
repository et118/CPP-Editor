cmake_minimum_required(VERSION 4.0)
project(Sketch3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sketch3 main.cpp
        Content.cpp
        Content.h
        Window.cpp
        Window.h
        BorderRenderer.h
        LineBorderRenderer.cpp
        LineBorderRenderer.h
        RecursiveWindow.cpp
        RecursiveWindow.h
        EdgeDimensions.h
        TestWindow.cpp
        TestWindow.h)
