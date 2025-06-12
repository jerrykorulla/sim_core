#include "sim_core/BouncingBallSimulation.h"
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    BouncingBallSimulation simulation(0.1, 10.0);  // step size=0.1s, stop time=10s
    simulation.run();
    const std::vector<double>& results = simulation.getOutput();

    // Save results to CSV for plotting
    std::ofstream file("results.csv");
    file << "step,value\n";
    for (size_t i = 0; i < results.size(); ++i) {
        file << i << "," << results[i] << "\n";
    }
    file.close();
    std::cout << "Results written to results.csv. You can plot this file using Python/matplotlib "
                 "or Excel.\n";

    return 0;
}
