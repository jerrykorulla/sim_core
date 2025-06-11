#pragma once
#include "sim_core/Block.h"
#include <vector>

class Model {
   public:
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
        step();
        terminate();
    }

   private:
    void initialize() {
        for (auto& block : blocks_) {
            block->initialize();
        }
    }

    void step() {
        for (auto& block : blocks_) {
            block->output();
            block->update();
        }
    }

    void terminate() {
        for (auto& block : blocks_) {
            block->terminate();
        }
    }

    std::vector<Block*> blocks_;
};