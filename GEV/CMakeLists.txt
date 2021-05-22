cmake_minimum_required(VERSION 3.15)
project(GEV)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE cpp_files src/*.cpp src/*.c src/*.hpp src/*.inl internal/*.h internal/*.inl internal/*.hpp include/*.hpp include/*.h dependencies/imgui/imgui/*.cpp)
file(GLOB_RECURSE include_files include/*.h dependencies/imgui/imgui/*.h)
#set(IMGUI_IMPL_OPENGL3 ON)
#add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD) #TODO: remove this line!
#add_subdirectory(dependencies/imgui)

add_executable(GEV ${cpp_files} ${include_files})

target_include_directories(GEV PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(GEV PRIVATE dependencies/imgui)
target_link_libraries(GEV EngineCore)
#target_link_libraries(GEV imgui)