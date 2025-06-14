# create executable

file(GLOB exec_files "./*.cpp" "./**/*.cpp")
add_executable(CustomSolver ${exec_files} )
target_include_directories(CustomSolver PRIVATE ${CMAKE_SOURCE_DIR}/src)

