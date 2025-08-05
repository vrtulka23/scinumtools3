#include <gtest/gtest.h>
#include <cstdio>
#include <memory>
#include <array>

std::string run_program(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

TEST(Examples, UniquePtrSolver) {
    std::string output = run_program("./build/SolverUniquePtr");
    EXPECT_EQ(output, "false\n");
}

TEST(Examples, CustomSolver) {
    std::string output = run_program("./build/SolverCustom");
    EXPECT_EQ(output, "true\n");
}

TEST(Examples, DefaultSolver) {
    std::string output = run_program("./build/SolverDefault");
    EXPECT_EQ(output, "797.5\n");
}

TEST(Examples, ArraySolver) {
    std::string output = run_program("./build/SolverArray");
    EXPECT_EQ(output, "{5}\n{5 7 9}\n");
}

TEST(Examples, SettingsSolver) {
    std::string output = run_program("./build/SolverSettings");
    EXPECT_EQ(output, "3\n");
}
