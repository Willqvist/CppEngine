cmake_minimum_required(VERSION 3.15)
project(Glad)
set(CMAKE_CXX_STANDARD 17)
add_library(Glad STATIC src/glad.c)
target_include_directories(Glad PUBLIC ${PROJECT_SOURCE_DIR}/include)

#target_link_libraries(Engine glad.c)
