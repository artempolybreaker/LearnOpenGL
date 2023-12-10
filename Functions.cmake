function(CopyResource Name)
  cmake_parse_arguments(COPY "" "" "COMMON" ${ARGN})

  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/resource)
      add_custom_command(TARGET ${Name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resource" "$<TARGET_FILE_DIR:${Name}>/resource")
      install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/resource" DESTINATION example/${Name})
  endif()
endfunction()