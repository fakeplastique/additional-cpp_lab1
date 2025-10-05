#pragma once
#include <algorithm>
#include <iostream>

#include "frequency_random.h"
#include <ostream>
#include <unordered_map>


class DistributionAnalysis {
private:
    WeightedDistribution generator;
    int iterations;

    std::unordered_map<int, double> calculateExpectedFrequencies() {
        std::unordered_map<int, double> expected_frequencies;
        auto weights = generator.getWeights();
        auto values = generator.getValues();
        double sum = std::accumulate(weights.begin(), weights.end(), 0.0);
        for (int i = 0; i < values.size(); i++) {
            expected_frequencies[values[i]] = weights[i] / sum;
        }
        return expected_frequencies;
    };

    std::unordered_map<int, int> runGenerations() {
        std::unordered_map<int, int> occurrences;
        for (int i = 0; i < iterations; i++) {
            occurrences[generator()]++;
        }
        return occurrences;
    };

    std::unordered_map<int, double> calculateRealFrequencies(const std::unordered_map<int,int>& occurrences) {
        std::unordered_map<int, double> real_frequencies;
        for (const auto& elem: occurrences) {
            real_frequencies[elem.first] = double(elem.second) / iterations;
        }
        return real_frequencies;
    }

    double getMaxDeviation(const std::unordered_map<int,double>& expected_frequencies,
                                    const std::unordered_map<int, double>& real_frequencies) {
        double max_deviation = 0.0;
        for (const auto& [key, real_val] : real_frequencies) {
            auto it = expected_frequencies.find(key);
            double deviation = (it != expected_frequencies.end()) ?
                              std::abs(real_val - it->second) : real_val;
            max_deviation = std::max(max_deviation, deviation);
        }
        return max_deviation;
    }

public:
    struct AnalysisResult {
        std::unordered_map<int, double> expected_frequencies;
        std::unordered_map<int, double> real_frequencies;
        double max_deviation;
    };

    DistributionAnalysis(const WeightedDistribution& func, int iterations)
        : generator(func), iterations(iterations) {}

    AnalysisResult runAnalysis() {
        AnalysisResult result;
        result.expected_frequencies = calculateExpectedFrequencies();
        std::unordered_map<int,int> occurrences = runGenerations();
        result.real_frequencies = calculateRealFrequencies(occurrences);
        result.max_deviation = getMaxDeviation(result.expected_frequencies, result.real_frequencies);
        return result;
    }
};