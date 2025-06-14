# create executable

file(GLOB exec_files "./*.cpp" "./**/*.cpp")
add_executable(UniquePtrSolver ${exec_files} )
target_include_directories(UniquePtrSolver PRIVATE ${CMAKE_SOURCE_DIR}/src)
