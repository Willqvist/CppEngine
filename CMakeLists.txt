cmake_minimum_required(VERSION 3.15)
project(Project)
add_compile_definitions(DEBUG_ENABLE)
add_compile_definitions(G_OPENGL)
#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
set(TARGET_SOURCE_DIR ${PROJECT_SOURCE_DIR})
#add_subdirectory(threading)
#add_subdirectory(Engine)
#add_subdirectory(GEV)
add_subdirectory(EngineCore)
add_subdirectory(GEV)