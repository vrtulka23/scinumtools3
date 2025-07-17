
# build library
file(GLOB source_files "./*.cpp" "./**/*.cpp")
add_library(scinumtools-puq STATIC ${source_files})
target_link_libraries(scinumtools-puq PRIVATE scinumtools-val)

# install libraries and executables
install(TARGETS scinumtools-puq EXPORT TargetsOpenSNT
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})
