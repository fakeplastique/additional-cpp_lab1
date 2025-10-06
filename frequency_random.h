#pragma once

#include <vector>
#include <random>

class WeightedDistribution {
private:
    std::vector<int> values_;
    std::vector<double> weights_;
    std::mt19937 engine_;
    std::discrete_distribution<size_t> distribution_;

    void validateInputValues() const;

public:
    WeightedDistribution(const std::vector<int>& values,
                         const std::vector<double>& weights);

    int operator()();

    const std::vector<int>& getValues() const { return values_; }
    const std::vector<double>& getWeights() const { return weights_; }
};