cmake_minimum_required(VERSION 3.1...3.29)
project(Vulk VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})  # Optional for clarity
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(vulk ${SOURCES})

target_link_libraries(vulk Vulkan::Vulkan glfw glm::glm-header-only)