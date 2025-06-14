# build library
file(GLOB source_files "./*.cpp" "./**/*.cpp")
add_library(scnt-puq STATIC ${source_files})
target_compile_definitions(scnt-puq PRIVATE)

# install libraries and executables
install(TARGETS scnt-puq EXPORT TargetsSCNT
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})
