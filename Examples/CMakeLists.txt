cmake_minimum_required(VERSION 3.14)

project(XenUI)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

add_executable(XenDemo WIN32 main.cpp)
target_link_libraries(XenDemo PRIVATE XenUI)

add_custom_command(TARGET XenDemo PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/app.ico ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/app.ico)