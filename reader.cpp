#include "reader.h"
#include <fstream>
#include <stdexcept>
#include <format>

Reader::InputData Reader::getData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    InputData data;

    if (!(file >> data.n) || data.n <= 0) {
        throw std::invalid_argument("Некоректне значення n у файлі");
    }

    int value;

    for (int i = 0; i < data.n; i++) {
        file >> value;
        data.values.push_back(value);
    }

    double weight;

    for (int i = 0; i < data.n; i++) {
        file >> weight;
        data.weights.push_back(weight);
    }

    if (data.values.empty() || data.weights.empty()) {
        throw std::invalid_argument("Не вдалося прочитати дані з файлу");
    }

    if (data.values.size() != data.weights.size()) {
        throw std::invalid_argument(
            std::format("Кількість чисел ({}) не відповідає кількості частот ({})",
                       data.values.size(), data.weights.size())
        );
    }

    return data;
}