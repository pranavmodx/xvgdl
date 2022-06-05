#pragma once

enum class EndConditionType {
    Timeout,
    MaxScoreReached,
};

std::string getStringForEndConditionType(EndConditionType type);