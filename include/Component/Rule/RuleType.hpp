#pragma once

enum class RuleType {
	Collision
};

std::string getStringForRuleType(RuleType type);
RuleType getRuleTypeFromString(std::string rule);