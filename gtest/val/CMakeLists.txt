# build test
file(GLOB test_files "*.cpp")
add_executable(GTestModule-val ${test_files})
target_include_directories(GTestModule-val PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(GTestModule-val PRIVATE GTest::gtest_main scinumtools-val)

include(GoogleTest)
gtest_discover_tests(GTestModule-val)
