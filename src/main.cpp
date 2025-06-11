#include "sim_core/Gain.h"

#include <iostream>
#include <vector>

class Model {
   private:

    virtual ~Model() = default;

    void initialize() {
    }

    void output() {
    }

    void update() {
    }

    void terminate() {
    }

};

// Demonstration
int main() {
    Gain<double, 1> gainAmplifier1(2.0);
    Gain<double, 1> gainAmplifier2(4.0);
    gainAmplifier1.initialize();
    gainAmplifier2.initialize();

    double inputSignal = 3.5;
    gainAmplifier1.setInput(&inputSignal, 0);
    gainAmplifier2.setInput(gainAmplifier1.getOutput(0), 0);
    gainAmplifier1.output();
    gainAmplifier2.output();

    const double* result = gainAmplifier2.getOutput(0);
    if (result) {
        std::cout << "Amplified output: " << *result << std::endl;  // Should print 7.0
    }

    gainAmplifier1.terminate();
    gainAmplifier2.terminate();

    return 0;
}
