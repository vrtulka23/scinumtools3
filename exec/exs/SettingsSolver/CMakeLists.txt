# create executable

file(GLOB exec_files "./*.cpp" "./**/*.cpp")
add_executable(SettingsSolver ${exec_files} )
target_include_directories(SettingsSolver PRIVATE ${CMAKE_SOURCE_DIR}/src)

