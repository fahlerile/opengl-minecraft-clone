# wsl cross-compile - cmake .. -D CMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -D CMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++
# w64devkit - cmake .. -G "MinGW Makefiles"

cmake_minimum_required(VERSION 3.18.4)
project(minecraft)

set(
  SOURCES
  src/main.cpp
  src/Application/Application.cpp
  src/Window/Window.cpp
  src/Model/Model.cpp
  src/ModelRenderer/ModelRenderer.cpp
  src/Renderer/Renderer.cpp
  src/Shader/Shader.cpp
  src/Camera/Camera.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")  # force .exe to build/bin

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC lib/include)
target_include_directories(${PROJECT_NAME} PUBLIC src)

find_library(
  GLFW_LIB
  NAMES glfw3
  HINTS "${CMAKE_SOURCE_DIR}/lib"
  NO_DEFAULT_PATH
)
if(NOT GLFW_LIB)
  message(FATAL_ERROR "GLFW library not found")
endif()

find_library(
  GLEW_LIB
  NAMES glew32s
  HINTS "${CMAKE_SOURCE_DIR}/lib"
  NO_DEFAULT_PATH
)
if(NOT GLEW_LIB)
  message(FATAL_ERROR "GLEW library not found")
endif()

target_link_libraries(
  ${PROJECT_NAME}
  ${GLFW_LIB}
  ${GLEW_LIB}
  opengl32
  gdi32
  -static  # dll error if there is no this option (https://stackoverflow.com/questions/69545451/cant-cross-compile-c-files-in-mingw-properly)
)

file(COPY res DESTINATION bin/res)  # copy resources to bin
