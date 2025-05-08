#include <iostream>

#include "tape_sorting_app.hpp"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> <config_file> <memory_limit>" << std::endl;
        return 1;
    }

    std::string input_file_name = argv[1];
    std::string output_file_name = argv[2];
    std::string config_file_name = argv[3];
    int memory_limit = atoi(argv[4]);

    try {
        TapeSortingApp tsa(config_file_name, memory_limit);
        tsa.sort(input_file_name, output_file_name);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
