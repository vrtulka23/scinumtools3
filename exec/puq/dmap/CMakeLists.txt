# create executable

file(GLOB exec_files "./*.cpp" "./**/*.cpp")
add_executable(dmap ${exec_files} )
target_include_directories(dmap PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(dmap PRIVATE opensnt-puq)

