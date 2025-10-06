// Bondar Ihor K-25 (gcc)
// Burkova Veronika K-25 (clang)

#include "frequency_random.h"
#include "distribution_analysis.h"
#include "reader.h"
#include "result_printer.h"
#include <iostream>


int main() {

    const std::string file_path = "input.txt";

    auto data = Reader::getData(file_path);
    WeightedDistribution generator(data.values, data.weights);
    DistributionAnalysis analyzer(generator, data.n);
    auto analysis_results = analyzer.runAnalysis();
    ResultPrinter(std::cout).print(data.values, analysis_results);
}