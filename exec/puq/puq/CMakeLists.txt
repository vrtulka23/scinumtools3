# create executable
file(GLOB exec_files "./*.cpp" "./**/*.cpp")
add_executable(puq ${exec_files} )
target_include_directories(puq PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(puq PRIVATE scnt-puq)

# install libraries and executables
install(TARGETS puq EXPORT TargetsSCNT
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
