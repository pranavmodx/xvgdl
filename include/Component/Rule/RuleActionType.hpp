#pragma once

enum class RuleActionType {
	SpeedUp, 
	Bounce,
};

std::string getStringForRuleActionType(RuleActionType type);
RuleActionType getRuleActionTypeFromString(std::string ruleActionName);