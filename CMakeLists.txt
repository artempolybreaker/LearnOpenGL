cmake_minimum_required(VERSION 3.16...3.26)
cmake_policy(VERSION 3.16)

project(OpenGLExamples VERSION 1.0.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(examples)