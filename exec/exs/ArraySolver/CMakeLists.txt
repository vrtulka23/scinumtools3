# create executable

file(GLOB exec_files "./*.cpp" "./**/*.cpp")
add_executable(ArraySolver ${exec_files} )
target_include_directories(ArraySolver PRIVATE ${CMAKE_SOURCE_DIR}/src)

