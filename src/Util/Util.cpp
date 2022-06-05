#include "Component/Object/ObjectType.hpp"
#include "Component/Rule/RuleType.hpp"
#include "Component/Rule/RuleActionType.hpp"
#include "Component/EndCondition/EndConditionType.hpp"

std::string getStringForObjectType(ObjectType type) {
    switch(type) {
        case ObjectType::Player:
            return "collision";
        case ObjectType::Ball:
            return "ball";
        default:
            return ""; // undefined
    }
}

std::string getStringForRuleType(RuleType type) {
    switch(type) {
        case RuleType::Collision:
            return "collision";
        default:
            return "";
    }
}

RuleType getRuleTypeFromString(std::string rule) {
    if (rule == "collision")
        return RuleType::Collision;

    return RuleType::Collision;
}

std::string getStringForRuleActionType(RuleActionType type) {
    switch(type) {
        case RuleActionType::SpeedUp:
            return "speed-up";
        case RuleActionType::Bounce:
            return "bounce";
        default:
            return "";
    }
}

RuleActionType getRuleActionTypeFromString(std::string ruleAction) {
    if (ruleAction == "speed-up")
        return RuleActionType::SpeedUp;
    else if (ruleAction == "bounce")
        return RuleActionType::Bounce;
    
    return RuleActionType::Bounce;
}

std::string getStringForEndConditionType(EndConditionType type) {
    switch(type) {
        case EndConditionType::Timeout:
            return "timeout";
        case EndConditionType::MaxScoreReached:
            return "maxScoreReached";
        default:
            return "";
    }
}

EndConditionType getEndConditionTypeFromString(std::string endConditionType) {
    if (endConditionType == "timeout")
        return EndConditionType::Timeout;
    else if (endConditionType == "maxScoreReached")
        return EndConditionType::MaxScoreReached;

    return EndConditionType::MaxScoreReached;
}