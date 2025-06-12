#pragma once

#include "sim_core/Gain.h"
#include "sim_core/Integrator.h"
#include "sim_core/OutputBuffer.h"
#include "sim_core/SimEngine.h"
#include "sim_core/SineWaveGenerator.h"
#include <vector>

class BouncingBallSimulation {
   private:
    SimEngine simEngine_;
    SineWaveGenerator<double> sineGen_;
    Gain<double, 1> gain1_;
    Integrator<double, 1> integrator_;
    OutputBuffer<double> output_;

   public:
    BouncingBallSimulation(double stepSize = 0.1, double stopTime = 10.0);

    void run();

    const std::vector<double>& getOutput() const;
};