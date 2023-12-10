project(Base)

include(CMakeFiles.txt)

add_library(${PROJECT_NAME} SHARED ${PUBLIC_SOURCES} ${PRIVATE_SOURCES})
message(STATUS "PROJECT NAME <- - - - -> ${PROJECT_NAME}")
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    glm::glm
    assimp::assimp
    glad::glad
    glfw
)


target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
    ${Stb_INCLUDE_DIR}
)
message(STATUS "DDDDDDDDDD - - - - - ${Stb_INCLUDE_DIR}")