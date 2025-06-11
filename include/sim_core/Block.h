#pragma once

#include <cstddef>

// Abstract base class for signal processing blocks
template <typename T>
class Block {
public:
    virtual ~Block() = default;

    virtual void initialize() = 0;
    virtual void output() = 0;
    virtual void update() = 0;
    virtual void terminate() = 0;

    virtual void setInput(const T* input, size_t index) = 0;
    virtual const T* getOutput(size_t index) const = 0;
};