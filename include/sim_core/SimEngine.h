#pragma once
#include "sim_core/Block.h"
#include <vector>

class SimEngine {
   public:
    SimEngine(size_t steps = 1) : steps_(steps) {
    }

    void setSteps(size_t steps) {
        steps_ = steps;
    }

    size_t getSteps() const {
        return steps_;
    }

    void addBlock(Block* block) {
        blocks_.push_back(block);
    }

    void addLink(Block* from, Block* to, size_t fromIndex = 0, size_t toIndex = 0) {
        if (from && to) {
            to->setInput(from->getOutput(fromIndex), toIndex);
        }
    }

    void run() {
        initialize();
        for (size_t i = 0; i < steps_; ++i) {
            step();
        }
        terminate();
    }

    void initialize() {
        for (auto& block : blocks_) {
            block->initialize();
        }
    }

    void step() {
        for (auto& block : blocks_) {
            block->output();
        }
        for (auto& block : blocks_) {
            block->update();
        }
    }

    void terminate() {
        for (auto& block : blocks_) {
            block->terminate();
        }
    }

   private:
    std::vector<Block*> blocks_;
    size_t steps_;
};