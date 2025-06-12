#include "sim_core/Gain.h"
#include "sim_core/SineWaveGenerator.h"
#include "sim_core/Integrator.h"
#include "sim_core/OutputBuffer.h"
#include "sim_core/SimEngine.h"
#include <iostream>
#include <vector>
#include <fstream>

// Demonstration
int main() {
    SineWaveGenerator<double> sineGen(1.0, 0.1, 0.0, 0.1); // amplitude=1.0, frequency=0.1 Hz, phase=0.0, sampleTime=0.1
    Gain<double, 1> gain1(2.0);
    Integrator<double, 1> integrator(0.0, 0.1); // initial value 0.0, step size 0.1
    OutputBuffer<double> outputBuffer;

    size_t steps = 100;
    SimEngine simEngine(steps);
    simEngine.addBlock(&sineGen);
    simEngine.addBlock(&gain1);
    simEngine.addBlock(&integrator);
    simEngine.addBlock(&outputBuffer);
    simEngine.addLink(&sineGen, &gain1, 0, 0);
    simEngine.addLink(&gain1, &integrator, 0, 0);
    simEngine.addLink(&integrator, &outputBuffer, 0, 0);
    simEngine.run();

    const std::vector<double>& results = outputBuffer.getBuffer();
    
    // Save results to CSV for plotting
    std::ofstream file("results.csv");
    file << "step,value\n";
    for (size_t i = 0; i < results.size(); ++i) {
        file << i << "," << results[i] << "\n";
    }
    file.close();
    std::cout << "Results written to results.csv. You can plot this file using Python/matplotlib or Excel.\n";

    return 0;
}
