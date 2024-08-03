cmake_minimum_required(VERSION 3.14)

project(XenUI)

include_directories(
        ..
)

add_library(XenUI STATIC App.h App.cpp
        Window.cpp
        Window.h
        Platform.h
        Canvas.cpp
        Canvas.h
        Widget.cpp
        Widget.h
        EventSystem.cpp
        EventSystem.h
        Events.h
        Context.cpp
        Context.h
        Mathematics.h
        Types.h
        Color.h
        Color.cpp
        Offset.cpp
        Offset.h
        Size.h
        Rectangle.cpp
        Rectangle.h
        Dimension.h
)

target_link_libraries(XenUI PRIVATE
        d2d1.lib
        dwrite.lib
)