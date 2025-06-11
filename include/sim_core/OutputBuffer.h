#pragma once

#include "Block.h"
#include <vector>
#include <cstddef>

// OutputBuffer block: stores its input values at each step
template <typename T>
class OutputBuffer : public Block {
public:
    OutputBuffer() : input_(nullptr) {}

    ~OutputBuffer() override = default;

    void initialize() override {
        buffer_.clear();
    }

    void output() override {
        // Nothing to do here, value is stored in update()
    }

    void update() override {
        if (input_) {
            buffer_.push_back(*input_);
        }
    }

    void terminate() override {
        // No resources to release
    }

    void setInput(const void* input, size_t) override {
        input_ = static_cast<const T*>(input);
    }

    const void* getOutput(size_t index) const override {
        return nullptr;
    }

    // Access the stored buffer
    const std::vector<T>& getBuffer() const {
        return buffer_;
    }

private:
    std::vector<T> buffer_;
    const T* input_;
};