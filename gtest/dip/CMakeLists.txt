# build test
file(GLOB test_files "*.cpp")
add_executable(GTestModule-dip ${test_files})
target_link_libraries(GTestModule-dip PRIVATE GTest::gtest_main opensnt-dip)

include(GoogleTest)
gtest_discover_tests(GTestModule-dip)
