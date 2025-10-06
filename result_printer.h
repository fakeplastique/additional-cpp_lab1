#pragma once
#include <ostream>
#include "distribution_analysis.h"
#include <unordered_map>
#include <format>
#include <vector>

class ResultPrinter {
private:
    std::ostream& stream;
public:
    ResultPrinter(std::ostream& stream) : stream(stream) {}

    void print(const std::string& result) const {
        stream << result << std::endl;
    }

    void print(const std::vector<int>& values, const DistributionAnalysis::AnalysisResult& result) const {
        print("Input numbers: ");
        for (const int &n: values)
            stream << n << " ";

        stream << std::endl;

        print("Input frequencies: ");
        for (const int &n: values)
            stream << result.expected_frequencies.at(n) << " ";
        stream << std::endl;

        print("Real frequencies: ");
        for (const int &n: values)
            stream << result.real_frequencies.at(n) << " ";
        stream << std::endl;

        print(std::format("Max frequencies deviation: {:.4f}", result.max_deviation));

    }

};