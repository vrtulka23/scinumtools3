# import GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

# add submodule tests
if (COMPILE_EXS)
   add_subdirectory(exs)
endif()
if (COMPILE_VAL)
   add_subdirectory(val)
endif()
if (COMPILE_PUQ)
   add_subdirectory(puq)
endif()
if (COMPILE_DIP) 
   add_subdirectory(dip)  
endif()
