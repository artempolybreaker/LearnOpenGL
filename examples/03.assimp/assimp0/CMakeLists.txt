project(assimp0)

include(CMakeFiles.txt)
include("./../../../Functions.cmake")

add_executable(${PROJECT_NAME} ${PRIVATE_SOURCES})
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Base
)
CopyResource(assimp0 COMMON 
  "resource/basic_light.fs"
  "resource/basic_light.vs"
  "resource/basic.vs"
  "resource/basic.fs"
  "resource/container-tex-1.jpg"
  "resource/models/backpack/backpack.obj"
)