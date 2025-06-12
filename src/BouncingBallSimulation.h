#pragma once

#include "sim_core/Simulation.h"
#include "sim_core/Constant.h"
#include "sim_core/Integrator.h"
#include "sim_core/OutputBuffer.h"
#include "sim_core/Compare.h"
#include "sim_core/Gain.h"
#include <vector>

// Bouncing ball simulation: models position and velocity with gravity and bounce
class BouncingBallSimulation : public Simulation {
   private:
    Constant<double, 1> gravity_;              // Provides constant acceleration (gravity)
    Integrator<double, 1> velocityIntegrator_; // Integrates acceleration to velocity
    Integrator<double, 1> positionIntegrator_; // Integrates velocity to position
    OutputBuffer<double> positionOutput_;      // Stores position for plotting
    Compare<double> groundHit_;                // Detects when position <= 0
    Gain<double, 1> restitution_;              // Applies restitution on bounce

   public:
    BouncingBallSimulation(double stepSize = 0.1, double stopTime = 10.0, double restitution = 0.8, double initialHeight = 10.0);
    void run();
    const std::vector<double>& getOutput() const;
};