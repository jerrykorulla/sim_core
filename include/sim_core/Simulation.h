#pragma once

#include "SimEngine.h"

class Simulation {
   public:
    Simulation(size_t steps = 1) : simEngine_(steps) {}
    Simulation(const Simulation&) = delete;  // Disable copy constructor
    virtual ~Simulation() = default;

    virtual void run() {
        simEngine_.run();
    };

   protected:
    SimEngine simEngine_;
};