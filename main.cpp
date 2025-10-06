#include "frequency_random.h"
#include "distribution_analysis.h"
#include "reader.h"
#include "result_printer.h"
#include <iostream>


int main() {

    const int EXPERIMENT_NUMBER = 10000;
    const std::string file_path = "input.txt";

    auto data = Reader::getData(file_path);
    WeightedDistribution generator(data.values, data.weights);
    DistributionAnalysis analyzer(generator, EXPERIMENT_NUMBER);
    auto analysis_results = analyzer.runAnalysis();
    ResultPrinter(std::cout).print(data.values, analysis_results);
}