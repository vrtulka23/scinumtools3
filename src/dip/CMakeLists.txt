# build library
file(GLOB source_files "./*.cpp" "./**/*.cpp")
add_library(scinumtools-dip STATIC ${source_files})
target_compile_definitions(scinumtools-dip PRIVATE)
target_link_libraries(scinumtools-dip PRIVATE scinumtools-puq)

# install libraries and executables
install(TARGETS scinumtools-dip EXPORT TargetsOpenSNT
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})
