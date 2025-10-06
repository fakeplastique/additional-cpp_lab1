#pragma once
#include <unordered_map>
#include "frequency_random.h"

class DistributionAnalysis {
private:
    WeightedDistribution generator;
    long long iterations;

    std::unordered_map<int, double> calculateExpectedFrequencies();
    std::unordered_map<int, int> runGenerations();
    std::unordered_map<int, double> calculateRealFrequencies(const std::unordered_map<int,int>& occurrences);
    double getMaxDeviation(const std::unordered_map<int,double>& expected_frequencies,
                          const std::unordered_map<int, double>& real_frequencies);

public:
    struct AnalysisResult {
        std::unordered_map<int, double> expected_frequencies;
        std::unordered_map<int, double> real_frequencies;
        double max_deviation;
    };

    DistributionAnalysis(const WeightedDistribution& func, long long iterations);
    AnalysisResult runAnalysis();
};