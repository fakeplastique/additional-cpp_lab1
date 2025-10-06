#include "reader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <format>

Reader::InputData Reader::getData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    InputData data;

    std::string n_line;
    if (!std::getline(file, n_line)) {
        throw std::invalid_argument("Couldn't read the first line.");
    }

    std::istringstream n_stream(n_line);
    if (!(n_stream >> data.n) || data.n <= 0) {
        throw std::invalid_argument("Invalid experiments number.");
    }

    std::string values_line;
    if (!std::getline(file, values_line)) {
        throw std::invalid_argument("Couldn't read values line.");
    }

    std::istringstream values_stream(values_line);
    int value;
    while (values_stream >> value) {
        data.values.push_back(value);
    }

    std::string weights_line;
    if (!std::getline(file, weights_line)) {
        throw std::invalid_argument("Couldn't read weights line.");
    }

    std::istringstream weights_stream(weights_line);
    double weight;
    while (weights_stream >> weight) {
        data.weights.push_back(weight);
    }

    if (data.values.empty() || data.weights.empty()) {
        throw std::invalid_argument("Couldn't get data from the file.");
    }

    if (data.values.size() != data.weights.size()) {
        throw std::invalid_argument(
            std::format("Number of values ({}) does not equal to number of weights ({}).",
                       data.values.size(), data.weights.size())
        );
    }

    return data;
}