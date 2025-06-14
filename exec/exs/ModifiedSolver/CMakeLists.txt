# create executable

file(GLOB exec_files "./*.cpp" "./**/*.cpp")
add_executable(ModifiedSolver ${exec_files} )
target_include_directories(ModifiedSolver PRIVATE ${CMAKE_SOURCE_DIR}/src)

