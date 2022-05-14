#include "Context/GameContext.hpp"

GameContext::GameContext() {
	properties = nullptr;
}

int GameContext::parseGameDefinition(std::string filePath) {
	std::string schemaPath = "schema/xvgdl.xsd";

	XVGDLValidator validator;
    XMLPlatformUtils::Initialize();
    if (!validator.validateSchema(schemaPath, filePath)) {
		XMLPlatformUtils::Terminate();
		std::cout << "Couldn't validate schema\n";
		return 0;
	}
    XMLPlatformUtils::Terminate();

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filePath.c_str());
    if (!result) {
        return 0;
	}

	pugi::xml_node gameDefinition = doc.first_child();
	for (const pugi::xml_node &component : gameDefinition) {
		std::string tagName = component.name();

		if (tagName == PROPERTY) {
			if (!properties)
				properties = std::make_unique<Properties>();
			parseProperty(component);
		} else if (tagName == CONTROLS) {
			controls = std::make_unique<Controls>();
			parseControl(component);
		} else if (tagName == MAP) {
			map = std::make_unique<Map>();
			parseMap(component);
		} else if (tagName == PLAYERS) {
			parsePlayers(component);
		} else if (tagName == OBJECTS) {
			parseObjects(component);
		} else if (tagName == RULES) {
			parseRule(component);
		}
	}

	RulePtr rule = std::make_unique<Rule>("somename", RuleType::Collision);
	RuleActionPtr ruleAction = std::make_unique<RuleAction>("block1", RuleActionType::SpeedUp);
	RuleActionPtr ruleAction2 = std::make_unique<RuleAction>("block2", RuleActionType::SpeedUp);
	rule->addRuleAction(std::move(ruleAction));
	rule->addRuleAction(std::move(ruleAction2));
	if (rules.find(RuleType::Collision) == rules.end()) {
		rules[RuleType::Collision] = std::vector<RulePtr>{};
	}
	rules[RuleType::Collision].emplace_back(std::move(rule));

	return 1;
}

void GameContext::parseProperty(const pugi::xml_node &property) {
	for (pugi::xml_attribute attr = property.first_attribute(); attr; attr = attr.next_attribute())
        {
            std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
			// properties.setProperty(attr.value());
        }
}

void GameContext::parseControl(const pugi::xml_node &control) {
	for (pugi::xml_attribute attr = control.first_child().first_attribute(); attr; attr = attr.next_attribute())
        {
            std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
			// controls.setControl(attr.value());
        }
}

void GameContext::parseMap(const pugi::xml_node &map) {
	for (pugi::xml_attribute attr = map.first_attribute(); attr; attr = attr.next_attribute())
        {
            std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
			// controls.setControl(attr.value());
        }
}

void GameContext::parseObjects(const pugi::xml_node &xmlObjects) {
	for (pugi::xml_node object : xmlObjects.children())
        {
			for (pugi::xml_attribute attr : object.attributes()) {
            	std::cout << " " << attr.name() << "=" << attr.value() << std::endl;

				std::string name = attr.name(), value = attr.value();

				if (name == "name") {
					// controls.setControl(attr.value());
					std::shared_ptr<Block> obj = std::make_shared<Block>(value);
					ObjectPtr object = std::static_pointer_cast<Object>(obj);
				}
			}
        }
}

void GameContext::parsePlayers(const pugi::xml_node &xmlPlayers) {
	for (pugi::xml_node object : xmlPlayers.children())
        {
			for (pugi::xml_attribute attr : object.attributes()) {
            	std::cout << " " << attr.name() << "=" << attr.value() << std::endl;

				std::string name = attr.name(), value = attr.value();

				if (name == "name") {
					// controls.setControl(attr.value());
					std::shared_ptr<Block> obj = std::make_shared<Block>(value);
					ObjectPtr player = std::static_pointer_cast<Object>(obj);
					std::cout << player->getName();
					if (objects.find(ObjectType::Player) == objects.end())
						objects[ObjectType::Player] = std::vector<ObjectPtr> {player};
					else
						objects[ObjectType::Player].push_back(player);
				}
			}
        }
}

void GameContext::parseRule(const pugi::xml_node &xmlRules) {
	// for (pugi::xml_node rule : rules.children())
    //     {
	// 		for (auto att : rule.attributes())
	// 			std::cout << att.name() << " " << att.value();
	// 		for (auto obj : rule.children()) {
    //         	for (pugi::xml_attribute attr : obj.attributes()) {
	// 				std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
	// 			}
	// 		}
    //     }

	// RulePtr rule = std::make_unique<Rule>("somename", RuleType::Collision);
	// RuleActionPtr ruleAction = std::make_unique<RuleAction>("block1", RuleActionType::SpeedUp);
	// rule->addRuleAction(std::move(ruleAction));
	// if (rules.find(RuleType::Collision) == rules.end())
	// 	rules[RuleType::Collision] = std::vector<RulePtr>{};
	// rules[RuleType::Collision].emplace_back(std::move(rule));
	// std::cout << "here is fine";
}

std::vector<ObjectPtr> GameContext::getPlayers() {
	return objects[ObjectType::Player];
}

std::vector<ObjectPtr> GameContext::getObjectsByType(ObjectType objType) {
	return objects[objType];
}

ObjectPtr GameContext::getObject(std::string objName) {
	// std::cout << objects[ObjectType::Player].size();
	for (auto objPair : objects) {
		// if (objPair.first == objName) // type is enum, name is string : handle this
		// if (objName == "block")
		// 	return objPair.second.back();
		for (auto obj : objPair.second) {
			if (obj->getName() == objName)
				return obj;
		}
	}
	return nullptr;
}

void GameContext::processRules() {
	if (rules.find(RuleType::Collision) == rules.end()) {
		std::cout << "no rule to process!\n";
		return;
	}
	for (auto &rule: rules[RuleType::Collision])
        rule->apply(this);
}