#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <vector>
#include <string>

// Class to load data from a CSV file
class DataLoader {
public:
    static std::vector<std::vector<int>> loadCSV(const std::string& fileName);
};

#endif 
