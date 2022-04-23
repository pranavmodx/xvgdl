#pragma once

#include "Token.hpp"
#include "Validator/Validator.hpp"
#include "Context/Generator.hpp"

class GameContext {
public:
	int parseGameDefinition(std::string filePath);
};