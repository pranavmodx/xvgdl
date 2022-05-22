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

std::string getStringForEndConditionType(EndConditionType type) {
    switch(type) {
        case EndConditionType::Timeout:
            return "timeout";
        default:
            return "";
    }
}