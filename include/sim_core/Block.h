#pragma once

#include <cstddef>

// Abstract base class for signal processing blocks
class Block {
public:
    virtual ~Block() = default;

    virtual void initialize() = 0;
    virtual void output() = 0;
    virtual void update() = 0;
    virtual void terminate() = 0;

    virtual void setInput(const void* input, size_t index) = 0;
    virtual const void* getOutput(size_t index) const = 0;
};