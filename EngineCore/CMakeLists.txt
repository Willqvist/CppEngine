cmake_minimum_required(VERSION 3.15)
project(EngineCore)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glm/glm)
add_subdirectory(dependencies/glfw)
add_compile_definitions(${STB_DEFINES})


file(GLOB_RECURSE cpp_files src/*.cpp src/*.c src/*.hpp src/*.inl internal/*.h internal/*.inl internal/*.hpp include/*.hpp include/*.h)
file(GLOB_RECURSE include_files include/*.h)
add_library(EngineCore ${cpp_files} ${include_files})

target_link_libraries(EngineCore opengl32)
target_link_libraries(EngineCore Glad)
target_link_libraries(EngineCore glm)
target_link_libraries(EngineCore glfw)

#target_link_libraries(Engine Imgui)
#target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/Dependencies/GLFW/src/glfw3.lib)
target_include_directories(EngineCore PUBLIC Dependencies/glfw/include)
target_include_directories(EngineCore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/dependencies/stb_image)
target_include_directories(EngineCore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
