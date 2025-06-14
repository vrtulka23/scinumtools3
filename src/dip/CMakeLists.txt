# build library
file(GLOB source_files "./*.cpp" "./**/*.cpp")
add_library(opensnt-dip STATIC ${source_files})
target_compile_definitions(opensnt-dip PRIVATE)
target_link_libraries(opensnt-dip PRIVATE opensnt-puq)

# install libraries and executables
install(TARGETS opensnt-dip EXPORT TargetsOpenSNT
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})
