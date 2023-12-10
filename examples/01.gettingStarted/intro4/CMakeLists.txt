project(intro4)

include(CMakeFiles.txt)
include("./../../../Functions.cmake")

add_executable(${PROJECT_NAME} ${PRIVATE_SOURCES})
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Base
)
CopyResource(intro4 COMMON
  "resource/container-tex-0.jpg"
  "resource/container-tex-1.jpg"
  "resource/textured.fs"
  "resource/textured.vs"
)
