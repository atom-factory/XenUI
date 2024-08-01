cmake_minimum_required(VERSION 3.14)

project(XenUI)

include_directories(
        ${CMAKE_SOURCE_DIR}/Lib
)

add_executable(XenDemo WIN32 main.cpp)
target_link_libraries(XenDemo PRIVATE XenUI)