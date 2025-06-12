#pragma once

#include "Block.h"
#include <cstddef>

// Compare block: compares input to a threshold and outputs 1 if true, 0 otherwise
template <typename T>
class Compare : public Block {
public:
    enum class Mode {
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        Equal,
        NotEqual
    };

    Compare(T threshold, Mode mode = Mode::Less)
        : threshold_(threshold), mode_(mode), input_(nullptr), output_(0) {}

    ~Compare() override = default;

    void initialize() override {
        output_ = 0;
    }

    void output() override {
        if (!input_) {
            output_ = 0;
            return;
        }
        switch (mode_) {
            case Mode::Less:         output_ = (*input_ <  threshold_) ? 1 : 0; break;
            case Mode::LessEqual:    output_ = (*input_ <= threshold_) ? 1 : 0; break;
            case Mode::Greater:      output_ = (*input_ >  threshold_) ? 1 : 0; break;
            case Mode::GreaterEqual: output_ = (*input_ >= threshold_) ? 1 : 0; break;
            case Mode::Equal:        output_ = (*input_ == threshold_) ? 1 : 0; break;
            case Mode::NotEqual:     output_ = (*input_ != threshold_) ? 1 : 0; break;
        }
    }

    void update() override {
        // No state to update
    }

    void terminate() override {
        // No resources to release
    }

    void setInput(const void* input, size_t) override {
        input_ = static_cast<const T*>(input);
    }

    const void* getOutput(size_t index) const override {
        if (index == 0) {
            return static_cast<const void*>(&output_);
        }
        return nullptr;
    }

private:
    T threshold_;
    Mode mode_;
    const T* input_;
    int output_;
};