#include "BouncingBallSimulation.h"

BouncingBallSimulation::BouncingBallSimulation(double stepSize, double stopTime, double restitutionCoeff, double initialHeight)
    : Simulation(static_cast<size_t>(stopTime / stepSize)),
      gravity_(-9.81),
      velocityIntegrator_(0.0, stepSize),
      positionIntegrator_(initialHeight, stepSize),
      positionOutput_(),
      groundHit_(0.0, Compare<double>::Mode::Less),
      restitution_(-restitutionCoeff) // Negative to reverse velocity on bounce
{
    // Connect gravity to velocity integrator
    simEngine_.addBlock(&gravity_);
    simEngine_.addBlock(&velocityIntegrator_);
    simEngine_.addBlock(&positionIntegrator_);
    simEngine_.addBlock(&positionOutput_);
    simEngine_.addBlock(&groundHit_);
    simEngine_.addBlock(&restitution_);

    simEngine_.addLink(&gravity_, &velocityIntegrator_, 0, 0);
    simEngine_.addLink(&velocityIntegrator_, &positionIntegrator_, 0, 0);
    simEngine_.addLink(&positionIntegrator_, &positionOutput_, 0, 0);
    simEngine_.addLink(&positionIntegrator_, &groundHit_, 0, 0);

    // The following logic is not handled by links, but by custom logic in run()
}

void BouncingBallSimulation::run() {
    simEngine_.initialize();
    size_t steps = simEngine_.getSteps();
    for (size_t i = 0; i < steps; ++i) {
        simEngine_.step();

        // Check for bounce
        int hit = *static_cast<const int*>(groundHit_.getOutput(0));
        if (hit) {
            // Reverse and scale velocity (simulate bounce)
            double v = *static_cast<const double*>(velocityIntegrator_.getOutput(0));
            double bounced = -0.8 * v; // 0.8 is restitution, or use a member
            velocityIntegrator_.setState(bounced);
            // Reset position to zero to avoid sinking below ground
            positionIntegrator_.setState(0.0);
        }
    }
    simEngine_.terminate();
}

const std::vector<double>& BouncingBallSimulation::getOutput() const {
    return positionOutput_.getBuffer();
}