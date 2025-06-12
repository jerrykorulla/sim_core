#pragma once

#include "Block.h"
#include <cmath>
#include <cstddef>

// SineWaveGenerator block: outputs a sine wave value at each step
template <typename T>
class SineWaveGenerator : public Block {
   public:
    SineWaveGenerator(T amplitude, T frequency, T phase = 0.0, T sampleTime = 1.0)
        : amplitude_(amplitude),
          frequency_(frequency),
          phase_(phase),
          sampleTime_(sampleTime),
          currentTime_(0),
          output_(0) {
    }

    ~SineWaveGenerator() override = default;

    void initialize() override {
        output_ = amplitude_ * std::sin(phase_);
    }

    void output() override {
        output_ = amplitude_ * std::sin(2 * M_PI * frequency_ * currentTime_ + phase_);
    }

    void update() override {
        currentTime_ += sampleTime_;
    }

    void terminate() override {
        // No resources to release
    }

    void setInput(const void*, size_t) override {
        // No inputs for sine wave generator
    }

    const void* getOutput(size_t index) const override {
        if (index == 0) {
            return static_cast<const void*>(&output_);
        }
        return nullptr;
    }

   private:
    T amplitude_;
    T frequency_;
    T phase_;
    T currentTime_;
    T sampleTime_;
    size_t step_;
    T output_;
};