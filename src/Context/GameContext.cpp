#include "Context/GameContext.hpp"
#include "Component/Object/Block.hpp"
#include "Component/Object/Ball.hpp"

GameContext::GameContext() {
	properties = nullptr;
}

int GameContext::parseGameDefinition(std::string filePath) {
	std::string schemaPath = "schema/xvgdl.xsd";

	XVGDLValidator validator;
    XMLPlatformUtils::Initialize();
    if (!validator.validateSchema(schemaPath, filePath)) {
		XMLPlatformUtils::Terminate();
		std::cout << "Validator Error :\nCouldn't validate schema\n";
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
		} else if (tagName == EVENTS) {
			parseEvents(component);
		} else if (tagName == RULES) {
			parseRules(component);
		} else if (tagName == END_CONDITIONS) {
			parseEndConditions(component);
		} else 
			return 0;
	}

	return 1;
}

void GameContext::parseProperty(const pugi::xml_node &property) {
	for (pugi::xml_attribute attr = property.first_attribute(); attr; attr = attr.next_attribute())
        {
            // std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
			// properties.setProperty(attr.value());
        }
}

void GameContext::parseControl(const pugi::xml_node &control) {
	for (pugi::xml_attribute attr = control.first_child().first_attribute(); attr; attr = attr.next_attribute())
        {
            // std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
			// controls.setControl(attr.value());
        }
}

void GameContext::parseMap(const pugi::xml_node &map) {
	for (pugi::xml_attribute attr = map.first_attribute(); attr; attr = attr.next_attribute())
        {
            // std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
			// controls.setControl(attr.value());
        }
}

void GameContext::parseObjects(const pugi::xml_node &xmlObjects) {
	for (pugi::xml_node xmlObject : xmlObjects.children())
        {
			std::string name, type;

			for (pugi::xml_attribute attr : xmlObject.attributes()) {
            	// std::cout << " " << attr.name() << "=" << attr.value() << std::endl;

				std::string attrName = attr.name();
				// done since order of attr can be different
				if (attrName == "name")
					name = attr.value();
				else if (attrName == "type")
					type = attr.value();
			}

			if (type == "ball") {
				std::shared_ptr<Ball> obj = std::make_shared<Ball>(name);
				ObjectPtr objjj = std::static_pointer_cast<Object>(obj);
				if (objects.find(ObjectType::Object) == objects.end())
					objects[ObjectType::Object] = std::vector<ObjectPtr> {objjj};
				else
					objects[ObjectType::Object].push_back(objjj);
			}
        }
}

void GameContext::parsePlayers(const pugi::xml_node &xmlPlayers) {
	for (pugi::xml_node object : xmlPlayers.children())
        {
			std::string name, type, position = "left";
			bool isAI = false;

			for (pugi::xml_attribute attr : object.attributes()) {
            	// std::cout << " " << attr.name() << "=" << attr.value() << std::endl;

				std::string attrName = attr.name();
				// done since order of attr can be different
				if (attrName == "name")
					name = attr.value();
				else if (attrName == "position")
					position = attr.value();
				else if (attrName == "type")
					type = attr.value();
				else if (attrName == "isAI")
					isAI = true;
			}

			// todo : controls.setControl(attr.value());

			if (type == "block") { // todo : match using ObjectType;
				std::shared_ptr<Block> obj = std::make_shared<Block>(name, position);
				if (isAI)
					obj->setIsAI();
				ObjectPtr player = std::static_pointer_cast<Object>(obj);
				// std::cout << player->getName();
				if (objects.find(ObjectType::Player) == objects.end())
					objects[ObjectType::Player] = std::vector<ObjectPtr> {player};
				else
					objects[ObjectType::Player].push_back(player);
			}
        }
}

void GameContext::parseEvents(const pugi::xml_node &xmlEvents) {
	for (pugi::xml_node xmlEvent : xmlEvents.children())
	{
		std::string name;

		for (pugi::xml_attribute attr : xmlEvent.attributes()) {
			// std::cout << " " << attr.name() << "=" << attr.value() << std::endl;

			std::string attrName = attr.name();
			// done since order of attr can be different
			if (attrName == "name")
				name = attr.value();
		}
	}

	events.emplace_back(Event(EventType::SpawnObject, ObjectType::Ball, 5));
}

void GameContext::parseRules(const pugi::xml_node &xmlRules) {
	for (pugi::xml_node xmlRule : xmlRules.children())
        {
			RulePtr rule;
			std::string ruleTypeInString;

			for (auto att : xmlRule.attributes()) {
				// std::cout << att.name() << " " << att.value();
				std::string attrName = att.name();

				if (attrName == "type") {
					ruleTypeInString = att.value();
					rule = std::make_unique<Rule>("somename", getRuleTypeFromString(ruleTypeInString));
				}
			}

			for (auto obj : xmlRule.children()) {
				std::string objectName, ruleActionTypeInString;
            	for (pugi::xml_attribute attr : obj.attributes()) {
					// std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
					std::string attrName = attr.name();
					if (attrName == "objectName")
						objectName = attr.value();
					else if (attrName == "result")
						ruleActionTypeInString = attr.value();
				}
					RuleActionPtr ruleAction = std::make_unique<RuleAction>(objectName, getRuleActionTypeFromString(ruleActionTypeInString));
					rule->addRuleAction(std::move(ruleAction));
			}

			RuleType ruleType = getRuleTypeFromString(ruleTypeInString);
			if (rules.find(ruleType) == rules.end())
				rules[ruleType] = std::vector<RulePtr>{};

			rules[ruleType].emplace_back(std::move(rule));
		}
}

void GameContext::parseEndConditions(const pugi::xml_node &xmlEndConditions) {
	for (pugi::xml_node xmlEndCondition : xmlEndConditions.children())
	{
		std::string type;
		for (auto att : xmlEndCondition.attributes()) {
			std::string attrName = att.name();

			if (attrName == "type") {
				// std::cout << att.name() << " " << att.value();
				type = att.value();
			}
		}

		EndConditionType endType = getEndConditionTypeFromString(type);
		endConditions.emplace_back(EndCondition("somename", endType));
	}
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

void GameContext::processEvents() {
	if (events.size() == 0) {
		// std::cout << "no events to process!\n";
		return;
	}
	for (auto &ev: events)
        ev.apply(this);
}

void GameContext::processRules() {
	if (rules.find(RuleType::Collision) == rules.end()) {
		// std::cout << "no rule to process!\n";
		return;
	}
	for (auto &rule: rules[RuleType::Collision])
        rule->apply(this);
}

void GameContext::processEndConditions(sf::Clock &clock, int score) {
	if (endConditions.size() == 0) {
		// std::cout << "no end game conditions to process!\n";
		return;
	}
	for (auto &condition: endConditions) {
        condition.apply(this, clock, score);
	}
}