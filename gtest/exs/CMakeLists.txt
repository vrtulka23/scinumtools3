# build test
file(GLOB test_files "*.cpp")
add_executable(GTestModule-exs ${test_files})
target_link_libraries(GTestModule-exs PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(GTestModule-exs)
