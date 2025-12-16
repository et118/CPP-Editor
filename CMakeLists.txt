cmake_minimum_required(VERSION 4.0)
project(CPP-Editor)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPP-Editor main.cpp
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
        TestWindow.h
        include/Windows/Window.h
        include/Windows/Window.h
        src/Windows/Window.cpp
        include/Windows/WindowDimensions.h
        include/Util/Container4D.h
        include/Util/Container2D.h)
