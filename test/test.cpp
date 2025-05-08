#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

#include "tape_sorting_app.hpp"

namespace fs = std::filesystem;

class TapeSortingAppTest : public ::testing::TestWithParam<int> {
protected:
    void SetUp() override {
        fs::create_directory("got");
    }

    void TearDown() override {
        fs::remove_all("got");
        if (fs::exists("res.txt")) {
            fs::remove("res.txt");
        }
    }

    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        return std::string((std::istreambuf_iterator<char>(file)), 
                         std::istreambuf_iterator<char>());
    }
};

TEST_P(TapeSortingAppTest, AllTestCases) {
    int test_num = GetParam();
    
    std::stringstream ss;
    ss << "tests/test_" << test_num << ".txt";
    std::string input_file = ss.str();
    
    ss.str("");
    ss << "answers/ans_" << test_num << ".txt";
    std::string expected_answer_file = ss.str();
    
    const std::string output_file = "res.txt";
    
    TapeSortingApp tsa("config.json", /* memory_limit */ 1024);
    tsa.sort(input_file, output_file);

    std::string expected = readFile(expected_answer_file);
    std::string actual = readFile(output_file);

    EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    AllCases,
    TapeSortingAppTest,
    ::testing::Range(1, 16)
);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}