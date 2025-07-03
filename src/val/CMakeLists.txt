# build library
file(GLOB source_files "./*.cpp" "./**/*.cpp")
add_library(opensnt-val STATIC ${source_files})
target_compile_definitions(opensnt-val PRIVATE)
target_link_libraries(opensnt-val PRIVATE opensnt-puq)

# install libraries and executables
install(TARGETS opensnt-val EXPORT TargetsOpenSNT
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})
