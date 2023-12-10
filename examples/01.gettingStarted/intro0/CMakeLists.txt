project(intro0)

include(CMakeFiles.txt)
include("./../../../Functions.cmake")

add_executable(${PROJECT_NAME} ${PRIVATE_SOURCES})
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Base
)
CopyResource(intro0 COMMON 
  "resource/shaderFrag.fs"
  "resource/shaderVert.vs"
)