# build test
file(GLOB test_files "*.cpp")
add_executable(GTestModule-puq ${test_files})
target_link_libraries(GTestModule-puq PRIVATE GTest::gtest_main scnt-puq)

include(GoogleTest)
gtest_discover_tests(GTestModule-puq)
