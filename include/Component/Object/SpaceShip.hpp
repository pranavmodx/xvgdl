#pragma once

#include <vector>
#include "Player.hpp"
#include "Block.hpp"

using BlockPtr = std::shared_ptr<Block>;

class SpaceShip : public Player {
    std::vector<BlockPtr> bullets;
    int health;

public:
    void moveController(bool useAlternate=false);
};