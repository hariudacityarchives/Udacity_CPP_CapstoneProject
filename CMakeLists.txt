cmake_minimum_required(VERSION 3.1.0)
project(GameApp VERSION 0.1.0)
set(OpenGL_GL_PREFERENCE "GLVND")

include(CTest)
enable_testing()

# Includes and libraries
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(OpenGL)

# subdirectories
add_subdirectory( src/game )

# Executable and link
add_executable(GameApp src/main.cpp)
target_link_libraries(GameApp game ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} OpenGL::OpenGL)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)