project(intro3)

include(CMakeFiles.txt)
include("./../../../Functions.cmake")

add_executable(${PROJECT_NAME} ${PRIVATE_SOURCES})
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Base
)
CopyResource(intro3 COMMON
  "resource/bricks_tex_named.jpg"
  "resource/container-tex.jpg"
  "resource/textured.fs"
  "resource/textured.vs"
)
