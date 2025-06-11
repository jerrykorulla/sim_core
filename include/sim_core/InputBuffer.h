#pragma once

#include "Block.h"
#include <vector>
#include <cstddef>

// InputBuffer block: outputs a sequence of values, one per step
template <typename T>
class InputBuffer : public Block {
public:
    explicit InputBuffer(const std::vector<T>& values)
        : values_(values), currentIndex_(0), output_(T{}) {}

    ~InputBuffer() override = default;

    void initialize() override {
        currentIndex_ = 0;
        output_ = values_.empty() ? T{} : values_[0];
    }

    void output() override {
        if (currentIndex_ < values_.size()) {
            output_ = values_[currentIndex_];
        } else {
            // Optionally, hold last value or set to zero
            // currentOutput_ = T{};
        }
    }

    void update() override {
        if (currentIndex_ < values_.size()) {
            ++currentIndex_;
        }
    }

    void terminate() override {
        // No resources to release
    }

    void setInput(const void*, size_t) override {
        // No inputs for input buffer
    }

    const void* getOutput(size_t index) const override {
        if (index == 0) {
            return static_cast<const void*>(&output_);
        }
        return nullptr;
    }

private:
    std::vector<T> values_;
    size_t currentIndex_;
    T output_;
};