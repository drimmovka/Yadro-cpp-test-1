#include <string>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "file_tape_handler.hpp"
#include "tape_sorter.hpp"

class TapeSortingApp {
public:
    explicit TapeSortingApp(const std::string& config_file_name, int mem_limit);

    ~TapeSortingApp();

    void sort(const std::string& input_file_name, const std::string& output_file_name);

private:
    FileTapeHandler<int> _file_tape_handler;
    TapeSorter _tape_sorter;

    const std::string tmp_directory;
    const std::string tmp_file_name;
    const std::string tmp_sorted_tape_file_name;
    const std::string merged_file_name;

private:
    DelaySettings delaySettings(const std::string& config_file_name);

    void initializeTempFiles();

    void processInputFile(std::ifstream& input_file);

    void writeOutputFile(const std::string& output_file_name);

    void cleanup();

    void mergeSortedTapes();
};