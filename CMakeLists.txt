cmake_minimum_required(VERSION 3.5)
project("SpacePipes")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
add_subdirectory(external/imgui ${CMAKE_CURRENT_BINARY_DIR}/imgui)


set(SP_SRC 
    cxx/Main.cxx
    cxx/Renderer.cxx
    cxx/World.cxx
    cxx/Camera.cxx
)

add_executable(${CMAKE_PROJECT_NAME} ${SP_SRC})

target_include_directories(${CMAKE_PROJECT_NAME} 
    PRIVATE include
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
elseif (UNIX)
    set(OPENGL_LIBRARIES 
        PRIVATE GL
        PRIVATE GLU
    )
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} 
    PRIVATE glad
    PRIVATE glfw
    PRIVATE imgui_core
    PRIVATE glfw_opengl3
    ${OPENGL_LIBRARIES}
)
