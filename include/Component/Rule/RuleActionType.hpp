#pragma once

enum class RuleActionType {
	SpeedUp, 
	Bounce,
};

std::string getStringForRuleActionType(RuleActionType type);