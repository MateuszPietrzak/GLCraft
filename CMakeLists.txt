cmake_minimum_required(VERSION 3.13)
project(GLCraft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH /usr/local/lib/cmake)
set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw3)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (glfw3 REQUIRED)
find_package (Freetype REQUIRED)

include_directories(/usr/local/include glad KHR)
include_directories(${GLFW_INCLUDE_DIRS})


set(SOURCE_FILES src/cpp/main.cpp)
add_executable(GLCraft include/stb_image.h src/cpp/main.cpp src/cpp/glad.c src/cpp/Shader.cpp include/Shader.h src/cpp/Game.cpp include/Game.h src/cpp/Camera.cpp include/Camera.h src/cpp/Chunk.cpp include/Chunk.h src/cpp/TextRenderer.cpp include/TextRenderer.h src/cpp/TextureManager.cpp include/TextureManager.h src/cpp/Raycast.cpp include/Raycast.h)
target_link_libraries (GLCraft
        ${OPENGL_LIBRARIES}
        ${GLFW3_LIBRARY} glfw
        ${FREETYPE_LIBRARIES})
target_include_directories(GLCraft
        PRIVATE ${FREETYPE_INCLUDE_DIRS})