cmake_minimum_required(VERSION 3.15)
project(Engine)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
add_subdirectory(Dependencies/GLAD)
add_subdirectory(Dependencies/GLM/glm)
add_subdirectory(Dependencies/ENTT)
add_subdirectory(Dependencies/GLFW)
add_compile_definitions(${STB_DEFINES})

file(GLOB IMGUI
        "vendor/imgui/*.h"
        "vendor/imgui/*.cpp"
        )

add_library(Engine STATIC engine/EntryPoint.cpp engine/Engine.h engine/core/Window.cpp engine/core/Window.h engine/platform/GLFW/GLFWWindow.cpp engine/platform/GLFW/GLFWWindow.h engine/core/Application.h engine/core/Logger.h engine/event/Event.h engine/event/EventListener.h engine/core/Core.h engine/core/Timestep.h engine/event/Events.h engine/core/Application.cpp engine/tools/Tools.h ${IMGUI} engine/rendering/RenderingCommand.cpp engine/rendering/RenderingCommand.h engine/core/GraphicsLibrary.h engine/platform/OpenGL/OpenGLRenderingCommand.cpp engine/platform/OpenGL/OpenGLRenderingCommand.h engine/rendering/Texture.h engine/platform/OpenGL/OpenGLTexture.cpp engine/platform/OpenGL/OpenGLTexture.h engine/rendering/Texture.cpp vendor/stb_image/stb_image.h engine/core/ResourceManager.cpp engine/core/ResourceManager.h engine/rendering/Buffer.h engine/rendering/Vertex.h engine/rendering/Buffer.cpp engine/platform/OpenGL/OpenGLArrayBuffer.cpp engine/platform/OpenGL/OpenGLArrayBuffer.h engine/rendering/VertexArray.cpp engine/rendering/VertexArray.h engine/platform/OpenGL/OpenGLVertexArray.cpp engine/platform/OpenGL/OpenGLVertexArray.h engine/platform/OpenGL/OpenGLIndexBuffer.cpp engine/platform/OpenGL/OpenGLIndexBuffer.h engine/rendering/VertexArrayRenderer.h engine/platform/OpenGL/OpenGLVertexArrayRenderer.h engine/rendering/Shader.h engine/rendering/Shader.cpp engine/platform/OpenGL/OpenGLShader.cpp engine/platform/OpenGL/OpenGLShader.h engine/core/Material.cpp engine/core/Material.h engine/rendering/Renderer.cpp engine/rendering/Renderer.h engine/Scene/Scene.cpp engine/Scene/Scene.h engine/scene/Entity.h engine/scene/components/TestComponent.hpp engine/scene/components/ScriptComponent.h engine/scene/components/Components.h engine/scene/components/VoxComponent.h engine/scene/components/VoxComponent.cpp engine/core/Input.h engine/core/KeyCode.h engine/core/MouseCode.h engine/scene/Layer.h engine/math/Vector3.h engine/scene/Registry.h engine/scene/components/Transform.h engine/scene/components/NamedComponent.h engine/scene/components/MeshComponent.cpp engine/scene/components/MeshComponent.h engine/scene/components/ScriptComponent.cpp engine/scene/Entity.cpp engine/threading/Lock.h engine/threading/MainThread.h engine/threading/MainThread.cpp engine/pipeline/PipelineObject.h engine/core/GraphicsLibrary.cpp engine/core/Input.cpp engine/core/Timestep.cpp engine/event/Events.cpp engine/platform/OpenGL/OpenGLVertexArrayRenderer.cpp engine/rendering/DebugRenderer.cpp engine/rendering/VertexArrayRenderer.cpp engine/scene/components/Components.cpp engine/scene/components/NamedComponent.cpp engine/scene/components/Transform.cpp engine/scene/Registry.cpp engine/threading/Lock.cpp engine/tools/DataPool.cpp)
target_link_libraries(Engine opengl32)
target_link_libraries(Engine Glad)
target_link_libraries(Engine glm)
target_link_libraries(Engine EnTT)
target_link_libraries(Engine glfw)
#target_link_libraries(Engine Imgui)
#target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/Dependencies/GLFW/src/glfw3.lib)
target_include_directories(Engine PUBLIC Dependencies/GLFW/include)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/engine)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/vendor)