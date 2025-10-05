#pragma once
#include <algorithm>
#include "frequency_random.h"
#include <map>


class DistributionAnalysis {
private:
    WeightedDistribution generator;
    int iterations;
    std::map<int, int> occurrences;
    std::map<int, double> expected_frequencies;
    std::map<int, double> real_frequencies;

    void calculateExpectedFrequencies() {
        auto weights = generator.getWeights();
        auto values = generator.getValues();
        double sum = std::accumulate(weights.begin(), weights.end(), 0.0);
        for (int i = 0; i < values.size(); i++) {
            expected_frequencies[values[i]] = weights[i] / sum;
        }
    };

    void runGenerations() {
        for (int i = 0; i < iterations; i++) {
            occurrences[generator()]++;
        }
    };

    void calculateRealFrequencies() {
        for (const auto& elem: occurrences) {
            real_frequencies[elem.first] = elem.second / iterations;
        }
    }

    double getMaxDeviation() {
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

    DistributionAnalysis(const WeightedDistribution& func) : generator(func), iterations(1000) {}
    DistributionAnalysis(const WeightedDistribution& func, int iterations)
        : generator(func), iterations(iterations) {}

    void runAnalysis() {
        calculateExpectedFrequencies();
        runGenerations();
        calculateRealFrequencies();
        getMaxDeviation();
    }
};