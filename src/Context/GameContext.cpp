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
		// } else if (tagName == CONTROLS) {
		// 	controls = std::make_unique<Controls>();
		// 	parseControl(component);
		// } else if (tagName == MAP) {
		// 	map = std::make_unique<Map>();
		// 	parseMap(component);
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
		}
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
			std::string name;

			for (pugi::xml_attribute attr : xmlObject.attributes()) {
            	// std::cout << " " << attr.name() << "=" << attr.value() << std::endl;

				std::string attrName = attr.name();
				// done since order of attr can be different
				if (attrName == "name")
					name = attr.value();
			}

			std::shared_ptr<Ball> obj = std::make_shared<Ball>(name);
			ObjectPtr objjj = std::static_pointer_cast<Object>(obj);
			if (objects.find(ObjectType::Object) == objects.end())
				objects[ObjectType::Object] = std::vector<ObjectPtr> {objjj};
			else
				objects[ObjectType::Object].push_back(objjj);
        }
}

void GameContext::parsePlayers(const pugi::xml_node &xmlPlayers) {
	for (pugi::xml_node object : xmlPlayers.children())
        {
			std::string name, position = "left";

			for (pugi::xml_attribute attr : object.attributes()) {
            	// std::cout << " " << attr.name() << "=" << attr.value() << std::endl;

				std::string attrName = attr.name();
				// done since order of attr can be different
				if (attrName == "name")
					name = attr.value();
				else if (attrName == "position")
					position = attr.value();
			}

			// controls.setControl(attr.value());
			std::shared_ptr<Block> obj = std::make_shared<Block>(name, position);
			ObjectPtr player = std::static_pointer_cast<Object>(obj);
			// std::cout << player->getName();
			if (objects.find(ObjectType::Player) == objects.end())
				objects[ObjectType::Player] = std::vector<ObjectPtr> {player};
			else
				objects[ObjectType::Player].push_back(player);
        }
}

void GameContext::parseEvents(const pugi::xml_node &xmlEvents) {
	for (pugi::xml_node xmlEvent : xmlEvents.children())
	{
		std::string name;

		for (pugi::xml_attribute attr : xmlEvent.attributes()) {
			std::cout << " " << attr.name() << "=" << attr.value() << std::endl;

			std::string attrName = attr.name();
			// done since order of attr can be different
			if (attrName == "name")
				name = attr.value();
		}
	}

	events.emplace_back(Event(EventType::SpawnObject, ObjectType::Ball, 5));
}

void GameContext::parseRules(const pugi::xml_node &xmlRules) {
	for (pugi::xml_node rule : xmlRules.children())
        {
			for (auto att : rule.attributes())
				// std::cout << att.name() << " " << att.value();
			for (auto obj : rule.children()) {
            	for (pugi::xml_attribute attr : obj.attributes()) {
					// std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
				}
			}
        }

	RulePtr rule = std::make_unique<Rule>("somename", RuleType::Collision);
	RuleActionPtr ruleAction = std::make_unique<RuleAction>("block1", RuleActionType::SpeedUp);
	RuleActionPtr ruleAction2 = std::make_unique<RuleAction>("ball", RuleActionType::Bounce);
	rule->addRuleAction(std::move(ruleAction));
	rule->addRuleAction(std::move(ruleAction2));

	RulePtr rule2 = std::make_unique<Rule>("someothername", RuleType::Collision);
	RuleActionPtr rr = std::make_unique<RuleAction>("block2", RuleActionType::SpeedUp);
	RuleActionPtr rr2 = std::make_unique<RuleAction>("ball", RuleActionType::Bounce);
	rule2->addRuleAction(std::move(rr));
	rule2->addRuleAction(std::move(rr2));

	if (rules.find(RuleType::Collision) == rules.end()) {
		rules[RuleType::Collision] = std::vector<RulePtr>{};
	}
	rules[RuleType::Collision].emplace_back(std::move(rule));
	rules[RuleType::Collision].emplace_back(std::move(rule2));
}

void GameContext::parseEndConditions(const pugi::xml_node &xmlEndConditions) {
	for (pugi::xml_node xmlEndCondition : xmlEndConditions.children())
	{
		for (auto att : xmlEndCondition.attributes())
			// std::cout << att.name() << " " << att.value();
		for (auto obj : xmlEndCondition.children()) {
			for (pugi::xml_attribute attr : obj.attributes()) {
				// std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
			}
		}
	}

	// temporarily hard-coded -> move to for loop
	endConditions.emplace_back(EndCondition("timout", EndConditionType::Timeout));
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
		std::cout << "no events to process!\n";
		return;
	}
	for (auto &ev: events)
        ev.apply(this);
}

void GameContext::processRules() {
	if (rules.find(RuleType::Collision) == rules.end()) {
		std::cout << "no rule to process!\n";
		return;
	}
	for (auto &rule: rules[RuleType::Collision])
        rule->apply(this);
}

void GameContext::processEndConditions(sf::Clock &clock) {
	if (endConditions.size() == 0) {
		std::cout << "no end game conditions to process!\n";
		return;
	}
	for (auto &condition: endConditions)
        condition.apply(this, clock);
}