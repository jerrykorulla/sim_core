#pragma once

#include "Block.h"
#include <array>

// Discrete-time integrator block (Euler method)
template <typename T, size_t N = 1>
class Integrator : public Block {
   public:
    explicit Integrator(T initial = T{}, T step = T{1}) : states_(), step_(step) {
        states_.fill(initial);
    }
    ~Integrator() override = default;

    void initialize() override {
        // Optionally reset state here if needed
    }

    void output() override {
        for (size_t i = 0; i < N; ++i) {
            outputs_[i] = states_[i];
        }
    }

    void update() override {
        // Discrete Euler integration: x = x + step * u
        for (size_t i = 0; i < N; ++i) {
            if (inputs_[i]) {
                states_[i] += step_ * (*inputs_[i]);
            }
        }
    }

    void terminate() override {
        // No resources to release
    }

    void setInput(const void* input, size_t index) override {
        if (index < N) {
            inputs_[index] = static_cast<const T*>(input);
        }
    }

    const void* getOutput(size_t index) const override {
        if (index < N) {
            return static_cast<const void*>(&outputs_[index]);
        }
        return nullptr;
    }

    void setState(T value) {
        states_[0] = value;
    }

   private:
    std::array<T, N> states_{};
    std::array<T, N> outputs_{};
    std::array<const T*, N> inputs_{};
    T step_;
};