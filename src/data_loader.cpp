#include "data_loader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
// Function to load data from a CSV file
std::vector<std::vector<int>> DataLoader::loadCSV(const std::string& fileName) {
    std::vector<std::vector<int>> data;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + fileName);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> row;
        std::string value;
        while (std::getline(ss, value, ',')) {
            row.push_back(std::stoi(value));
        }
        data.push_back(row);
    }
    return data;
}
