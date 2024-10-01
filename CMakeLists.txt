cmake_minimum_required(VERSION 3.15)
project(renderer)

find_package(vulkanHeaders REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} vulkanHeaders::vulkanHeaders)
