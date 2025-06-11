#pragma once

#include "Block.h"
#include <algorithm>
#include <array>

// Gain block that multiplies input by a constant gain factor
template <typename T, size_t N>
class Gain : public Block<T> {
   public:
    explicit Gain(T gainFactor) : gain_(gainFactor) {
    }
    ~Gain() override = default;

    void initialize() override {
        std::fill(outputs_.begin(), outputs_.end(), static_cast<T>(0));
    }

    void output() override {
        for (size_t i = 0; i < N; ++i) {
            if (inputs_[i]) {
                outputs_[i] = gain_ * (*inputs_[i]);
            } else {
                outputs_[i] = static_cast<T>(0);
            }
        }
    }

    void update() override {
        // No state to update in this simple block
    }

    void terminate() override {
        // No resources to release
    }

    void setInput(const T* input, size_t index) override {
        if (index < N) {
            inputs_[index] = const_cast<T*>(input);  // Unsafe cast, but works here
        }
    }

    const T* getOutput(size_t index) const override {
        if (index < N) {
            return &outputs_[index];
        }
        return nullptr;
    }

   private:
    T gain_;
    std::array<T, N> outputs_{};
    std::array<T*, N> inputs_{};
};