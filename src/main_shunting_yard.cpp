#include "algorithms/LevenshteinDistance.h"
#include "algorithms/ShuntingAlgorithm.h"

int main(int argc, char* argv[]) {
    std::string input = "σ maker2<maker ( ρ maker2←maker π maker,type Product ⋈ π maker,type Product )";
    ShuntingAlgorithm algorithm;
    algorithm(input);
    return 0;
}
