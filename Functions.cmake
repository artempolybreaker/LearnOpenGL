function(CopyResource Name)
  cmake_parse_arguments(COPY "" "" "COMMON" ${ARGN})

  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/resource)
      add_custom_command(TARGET ${Name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resource" "$<TARGET_FILE_DIR:${Name}>/resource")
      install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/resource" DESTINATION example/${Name})
  endif()
endfunction()

function(CreateResourceSymlink Name)
  cmake_parse_arguments(LINK "" "" "COMMON" ${ARGN})

  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/resource)
      # Define the target directory for the symlink
      set(target_symlink_dir "$<TARGET_FILE_DIR:${Name}>/resource")

      # Add a custom command to create the symlink after the target is built
      add_custom_command(TARGET ${Name} POST_BUILD
                         COMMAND ${CMAKE_COMMAND} -E create_symlink 
                                 "${CMAKE_CURRENT_SOURCE_DIR}/resource" 
                                 "${target_symlink_dir}")

      # Optionally, install the symlink if needed (uncomment if required)
      # install(DIRECTORY "${target_symlink_dir}" DESTINATION example/${Name})
  endif()
endfunction()
