#include "sim_core/BouncingBallSimulation.h"

BouncingBallSimulation::BouncingBallSimulation(double stepSize, double stopTime)
    : simEngine_(static_cast<size_t>(stopTime / stepSize)),
      sineGen_(1.0, 0.1, 0.0, stepSize),  // amplitude=1.0, frequency=0.1 Hz, phase=0.0, sampleTime=stepSize
      gain1_(2.0),
      integrator_(0.0, stepSize)  // initial value 0.0, step size=stepSize
{
    simEngine_.addBlock(&sineGen_);
    simEngine_.addBlock(&gain1_);
    simEngine_.addBlock(&integrator_);
    simEngine_.addBlock(&output_);
    simEngine_.addLink(&sineGen_, &gain1_, 0, 0);
    simEngine_.addLink(&gain1_, &integrator_, 0, 0);
    simEngine_.addLink(&integrator_, &output_, 0, 0);
}

void BouncingBallSimulation::run() {
    simEngine_.run();
}

const std::vector<double>& BouncingBallSimulation::getOutput() const {
    return output_.getBuffer();
}