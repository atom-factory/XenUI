cmake_minimum_required(VERSION 3.14)

project(XenUI)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(XenUI STATIC XenUI.h XenApp.h XenApp.cpp)