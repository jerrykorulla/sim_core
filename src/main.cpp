#include "sim_core/Gain.h"
#include "sim_core/Model.h"
#include <iostream>

// Demonstration
int main() {
    Gain<double, 1> gainAmplifier1(2.0);
    Gain<double, 1> gainAmplifier2(4.0);

    double inputSignal = 1;
    gainAmplifier1.setInput(&inputSignal, 0);  // Set input for the first gain block
    Model model;
    model.addBlock(&gainAmplifier1);
    model.addBlock(&gainAmplifier2);
    model.addLink(&gainAmplifier1, &gainAmplifier2, 0, 0);
    model.run();

    const double* result = static_cast<const double*>(gainAmplifier2.getOutput(0));
    if (result) {
        std::cout << "Amplified output: " << *result << std::endl;  // Should print 7.0
    }

    return 0;
}
