#pragma once

enum class EndConditionType {
    Timeout,
};

std::string getStringForEndConditionType(EndConditionType type);