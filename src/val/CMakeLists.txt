# build library
file(GLOB source_files "./*.cpp" "./**/*.cpp")
add_library(scinumtools-val STATIC ${source_files})
target_compile_definitions(scinumtools-val PRIVATE)
target_link_libraries(scinumtools-val PRIVATE)

# install libraries and executables
install(TARGETS scinumtools-val EXPORT TargetsOpenSNT
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})
