cmake_minimum_required(VERSION 3.5)
project("SpacePipes")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
add_subdirectory(external/imgui ${CMAKE_CURRENT_BINARY_DIR}/imgui)


set(SP_SRC 
    src/app/App.cpp
    src/main.cpp
    src/scene/Scene.cpp
    src/scene/World.cpp
    src/scene/Camera.cpp
    src/scene/Mesh.cpp
    src/scene/Pipe.cpp
    src/scene/PipeGenerator.cpp
    src/window/Window.cpp
    src/window/gui/Gui.cpp
    src/renderer/Renderer.cpp
    src/renderer/shader/Shader.cpp
    src/renderer/shader/src/vertShader.cpp
    src/renderer/shader/src/fragShader.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SP_SRC})

target_include_directories(${CMAKE_PROJECT_NAME} 
    PRIVATE src/
    PRIVATE external/glad/include
    PRIVATE external/glfw/include
    PRIVATE external/imgui
    PRIVATE external/glm
)

if (WIN32)
    set(OPENGL_LIBRARIES 
        PRIVATE opengl32
        PRIVATE glu32
    )

    add_compile_definitions(SP_WINDOWS_USED)
elseif (UNIX)
    set(OPENGL_LIBRARIES 
        PRIVATE GL
        PRIVATE GLU
    )
    add_compile_definitions(SP_LINUX_USED)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} 
    PRIVATE glad
    PRIVATE glfw
    PRIVATE imgui_core
    PRIVATE glfw_opengl3
    ${OPENGL_LIBRARIES}
)
