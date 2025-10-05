#include "frequency_random.h"
#include <numeric>
#include <stdexcept>
#include "random_engine.h"

void WeightedDistribution::validateInputValues() const {
    if (values_.empty() || weights_.empty()) {
        throw std::invalid_argument("Порожні вхідні дані");
    }

    if (values_.size() != weights_.size()) {
        throw std::invalid_argument("Кількість чисел не відповідає кількості частот");
    }

    for (double w : weights_) {
        if (w < 0) {
            throw std::invalid_argument("Частоти не можуть бути від'ємними");
        }
    }

    double total = std::accumulate(weights_.begin(), weights_.end(), 0.0);
    if (total <= 0) {
        throw std::invalid_argument("Сума частот має бути додатною");
    }
}

WeightedDistribution::WeightedDistribution(const std::vector<int>& values,
                                           const std::vector<double>& weights)
    : values_(values), weights_(weights), engine_(RandomEngine::create()) {

    validateInputValues();

    distribution_ = std::discrete_distribution<size_t>(weights_.begin(), weights_.end());
}

int WeightedDistribution::operator()() const {
    size_t index = distribution_(engine_);
    return values_[index];
}