cmake_minimum_required(VERSION 3.15)
project(Engine)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
add_subdirectory(Dependencies/GLAD)
add_subdirectory(Dependencies/GLM/glm)
add_subdirectory(Dependencies/ENTT)

add_compile_definitions(${STB_DEFINES})

file(GLOB IMGUI
        "vendor/imgui/*.h"
        "vendor/imgui/*.cpp"
        )

add_library(Engine STATIC engine/EntryPoint.cpp engine/Engine.h engine/core/Window.cpp engine/core/Window.h engine/platform/GLFW/GLFWWindow.cpp engine/platform/GLFW/GLFWWindow.h engine/core/Application.h engine/core/Logger.h engine/event/Event.h engine/event/EventListener.h engine/core/Core.h engine/core/Timestep.h engine/event/WindowClose.cpp engine/event/WindowClose.h engine/core/Application.cpp engine/tools/Tools.h ${IMGUI} engine/rendering/RenderingCommand.cpp engine/rendering/RenderingCommand.h engine/core/GraphicsLibrary.h engine/platform/OpenGL/OpenGLRenderingCommand.cpp engine/platform/OpenGL/OpenGLRenderingCommand.h engine/rendering/Texture.h engine/platform/OpenGL/OpenGLTexture.cpp engine/platform/OpenGL/OpenGLTexture.h engine/rendering/Texture.cpp vendor/stb_image/stb_image.h engine/core/ResourceManager.cpp engine/core/ResourceManager.h engine/rendering/Buffer.h engine/rendering/Vertex.h engine/rendering/Buffer.cpp engine/platform/OpenGL/OpenGLArrayBuffer.cpp engine/platform/OpenGL/OpenGLArrayBuffer.h engine/rendering/VertexArray.cpp engine/rendering/VertexArray.h engine/platform/OpenGL/OpenGLVertexArray.cpp engine/platform/OpenGL/OpenGLVertexArray.h engine/platform/OpenGL/OpenGLIndexBuffer.cpp engine/platform/OpenGL/OpenGLIndexBuffer.h engine/rendering/VertexArrayRenderer.h engine/platform/OpenGL/OpenGLVertexArrayRenderer.h engine/rendering/Shader.h engine/rendering/Shader.cpp engine/platform/OpenGL/OpenGLShader.cpp engine/platform/OpenGL/OpenGLShader.h engine/core/Material.cpp engine/core/Material.h engine/rendering/Renderer.cpp engine/rendering/Renderer.h engine/Scene/Scene.cpp engine/Scene/Scene.h engine/Scene/Entity.hpp engine/components/TestComponent.hpp engine/components/ScriptComponent.hpp engine/components/Components.h engine/components/VoxComponent.h engine/components/VoxComponent.cpp)
target_link_libraries(Engine opengl32)
target_link_libraries(Engine Glad)
target_link_libraries(Engine glm)
target_link_libraries(Engine EnTT)
#target_link_libraries(Engine Imgui)
target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/Dependencies/GLFW/src/glfw3.lib)
target_include_directories(Engine PUBLIC Dependencies/GLFW/include)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/engine)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/vendor)