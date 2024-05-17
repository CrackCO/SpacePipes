cmake_minimum_required(VERSION 3.5)
project("SpacePipes")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SP_SRC  cxx/Main.cxx
            cxx/Glad.cxx)

add_executable(${CMAKE_PROJECT_NAME} ${SP_SRC})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src/glad/include)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE opengl32)