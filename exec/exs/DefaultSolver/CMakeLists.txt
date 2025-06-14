# create executable

file(GLOB exec_files "./*.cpp" "./**/*.cpp")
add_executable(DefaultSolver ${exec_files} )
target_include_directories(DefaultSolver PRIVATE ${CMAKE_SOURCE_DIR}/src)

