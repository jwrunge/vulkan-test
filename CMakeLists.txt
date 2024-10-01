cmake_minimum_required(VERSION 3.15)
project(render CXX)

add_executable(render src/render.cpp src/main.cpp)

install(TARGETS render DESTINATION "."
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)
