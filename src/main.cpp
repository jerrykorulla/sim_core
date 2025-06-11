#include "sim_core/Gain.h"
#include "sim_core/InputBuffer.h"
#include "sim_core/Integrator.h"
#include "sim_core/OutputBuffer.h"
#include "sim_core/Model.h"
#include <iostream>
#include <vector>

// Demonstration
int main() {
    std::vector<double> inputValues{0,1,2,3,4,5,6,7,8,9,10};
    InputBuffer<double> inputBuffer(inputValues);
    Gain<double, 1> gain1(2.0);
    Integrator<double, 1> integrator(0.0, 1.0); // initial value 0.0, step size 1.0
    OutputBuffer<double> outputBuffer;

    Model model(inputValues.size());
    model.addBlock(&inputBuffer);
    model.addBlock(&gain1);
    model.addBlock(&integrator);
    model.addBlock(&outputBuffer);
    model.addLink(&inputBuffer, &gain1, 0, 0);
    model.addLink(&gain1, &integrator, 0, 0);
    model.addLink(&integrator, &outputBuffer, 0, 0);
    model.run();

    // Print all integrated outputs
    const std::vector<double>& results = outputBuffer.getBuffer();
    std::cout << "Integrated outputs: ";
    for (double v : results) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}
