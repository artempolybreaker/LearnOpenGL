project(colors5)

include(CMakeFiles.txt)
include("./../../../Functions.cmake")

add_executable(${PROJECT_NAME} ${PRIVATE_SOURCES})
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Base
)
CopyResource(colors5 COMMON 
  "resource/basic_light.fs"
  "resource/basic_light.vs"
  "resource/basic.vs"
  "resource/basic.fs"
  "resource/container-tex-1.jpg"
  "resource/container-tex-specular.jpg"
  "resource/matrix.jpg"
)