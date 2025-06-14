# build library
file(GLOB source_files "./*.cpp" "./**/*.cpp")
add_library(opensnt-puq STATIC ${source_files})
target_compile_definitions(opensnt-puq PRIVATE)

# install libraries and executables
install(TARGETS opensnt-puq EXPORT TargetsOpenSNT
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})
