cmake_minimum_required(VERSION 3.15)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sandbox src/main.cpp src/GameApplication.cpp src/GameApplication.h src/components/CameraMovement.h)

target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(Sandbox Engine)