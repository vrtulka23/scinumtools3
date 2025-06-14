# import GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

# add submodule tests
add_subdirectory(exs)  
add_subdirectory(puq)  
add_subdirectory(dip)  
