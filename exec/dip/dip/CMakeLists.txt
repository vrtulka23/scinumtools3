# create executable
file(GLOB exec_files "./*.cpp" "./**/*.cpp")
add_executable(dip ${exec_files} )
target_include_directories(dip PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(dip PRIVATE scnt-dip)

# install libraries and executables
install(TARGETS dip EXPORT TargetsSCNT
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
