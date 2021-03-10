function(add_cpp FILENAME)
   add_executable(${FILENAME} "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.cpp")
endfunction()