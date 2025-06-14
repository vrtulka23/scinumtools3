# build library
file(GLOB source_files "./*.cpp" "./**/*.cpp")
add_library(scnt-dip STATIC ${source_files})
target_compile_definitions(scnt-dip PRIVATE)
target_link_libraries(scnt-dip PRIVATE scnt-puq)

# install libraries and executables
install(TARGETS scnt-dip EXPORT TargetsSCNT
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})
