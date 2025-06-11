#pragma once

#include "Block.h"
#include <array>

// Constant block that outputs a fixed value
template <typename T, size_t N>
class Constant : public Block {
   public:
    explicit Constant(const std::array<T, N>& values) : values_(values) {
    }
    explicit Constant(T value) {
        values_.fill(value);
    }
    ~Constant() override = default;

    void initialize() override {
        // Nothing to initialize
    }

    void output() override {
        // Output is always the constant value
    }

    void update() override {
        // No state to update
    }

    void terminate() override {
        // No resources to release
    }

    void setInput(const void*, size_t) override {
        // No inputs for constant block
    }

    const void* getOutput(size_t index) const override {
        if (index < N) {
            return static_cast<const void*>(&values_[index]);
        }
        return nullptr;
    }

   private:
    std::array<T, N> values_{};
};