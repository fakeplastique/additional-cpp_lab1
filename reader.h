#pragma once
#include <string>
#include <vector>

class Reader {
public:
    struct InputData {
        size_t n;
        std::vector<int> values;
        std::vector<double> weights;
    };

    static InputData getData(const std::string& filename);
};