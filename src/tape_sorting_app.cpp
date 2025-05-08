#include "tape_sorting_app.hpp"

TapeSortingApp::TapeSortingApp(const std::string& config_file_name, int mem_limit)
    : _file_tape_handler(delaySettings(config_file_name), mem_limit),
        tmp_directory("tmp"),
        tmp_file_name(tmp_directory + "/tmp.txt"),
        tmp_sorted_tape_file_name(tmp_directory + "/tmp_sorted_tape.txt"),
        merged_file_name(tmp_directory + "/tmp_merged.txt")
{}

TapeSortingApp::~TapeSortingApp() = default;

void TapeSortingApp::sort(const std::string& input_file_name, const std::string& output_file_name) {
    std::ifstream input_file(input_file_name);
    if (!input_file.is_open()) {
        throw std::runtime_error("Failed to open input file");
    }

    std::filesystem::create_directory(tmp_directory);
    initializeTempFiles();

    processInputFile(input_file);
    input_file.close();

    writeOutputFile(output_file_name);
    cleanup();
}

void TapeSortingApp::initializeTempFiles() {
    std::ofstream tmp_sorted_file(tmp_sorted_tape_file_name);
    if (!tmp_sorted_file.is_open()) {
        throw std::runtime_error("Failed to create sorted tape file");
    }
    tmp_sorted_file.close();
}

void TapeSortingApp::processInputFile(std::ifstream& input_file) {
    bool eof_flag = false;
    while (!eof_flag) {
        eof_flag = _file_tape_handler.readNextMemSeg(input_file);
        _tape_sorter.sort(&_file_tape_handler);

        std::ofstream tmp_file(tmp_file_name, std::ios::trunc);
        if (!tmp_file.is_open()) {
            throw std::runtime_error("Failed to open temporary file");
        }

        _file_tape_handler.moveTo(-1);
        for (int i = 0; i < _file_tape_handler.tapeSize(); ++i) {
            _file_tape_handler.shift(+1);
            tmp_file << _file_tape_handler.head() << " ";
        }

        tmp_file.close();
        mergeSortedTapes();
    }
}

void TapeSortingApp::writeOutputFile(const std::string& output_file_name) {
    std::ofstream output_file(output_file_name);
    if (!output_file.is_open()) {
        throw std::runtime_error("Failed to open output file");
    }

    std::ifstream final_sorted_file(tmp_sorted_tape_file_name);
    if (!final_sorted_file.is_open()) {
        throw std::runtime_error("Failed to open sorted tape file for reading");
    }
    output_file << final_sorted_file.rdbuf();

    final_sorted_file.close();
    output_file.close();
}

void TapeSortingApp::cleanup() {
    std::filesystem::remove_all(tmp_directory);
}

DelaySettings TapeSortingApp::delaySettings(const std::string& config_file_name) {
    std::ifstream config_file(config_file_name);
    if (!config_file.is_open()) {
        throw std::runtime_error("Failed to open config file");
    }
    nlohmann::json j;
    config_file >> j;
    int read_delay = j["read_delay_ms"].get<int>();
    int write_delay = j["write_delay_ms"].get<int>();
    int move_delay = j["move_delay_ms"].get<int>();
    return DelaySettings(read_delay, write_delay, move_delay);
}

void TapeSortingApp::mergeSortedTapes() {
    std::ifstream tmp_file(tmp_file_name);
    std::ifstream tmp_sorted_file(tmp_sorted_tape_file_name);
    std::ofstream merged_file(merged_file_name);

    if (!tmp_file.is_open() || !tmp_sorted_file.is_open() || !merged_file.is_open()) {
        throw std::runtime_error("Failed to open files for merging");
    }

    int num1, num2;
    bool has_num1 = static_cast<bool>(tmp_file >> num1);
    bool has_num2 = static_cast<bool>(tmp_sorted_file >> num2);
    while (has_num1 || has_num2) {
        if (has_num1 && (!has_num2 || num1 <= num2)) {
            merged_file << num1 << " ";
            has_num1 = static_cast<bool>(tmp_file >> num1);
        } else {
            merged_file << num2 << " ";
            has_num2 = static_cast<bool>(tmp_sorted_file >> num2);
        }
    }

    tmp_file.close();
    tmp_sorted_file.close();
    merged_file.close();

    std::filesystem::remove(tmp_sorted_tape_file_name);
    std::filesystem::rename(merged_file_name, tmp_sorted_tape_file_name);
}