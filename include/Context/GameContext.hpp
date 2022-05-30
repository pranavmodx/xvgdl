#pragma once

#include <vector>

#include "Token.hpp"
#include <validator/Validator.hpp>
#include "pugixml/pugixml.hpp"

#include "Component/Properties.hpp"
#include "Component/Controls.hpp"
#include "Component/Map.hpp"
#include "Component/Object/Object.hpp"
#include "Component/Object/Player.hpp"
#include "Component/Object/Block.hpp"
#include "Component/Object/Ball.hpp"
#include "Component/Object/Player.hpp"
#include "Component/Event/Event.hpp"
#include "Component/Rule/Rule.hpp"
#include "Component/EndCondition/EndCondition.hpp"

#include "Component/Object/ObjectType.hpp"
#include "Component/Rule/RuleType.hpp"
#include "Component/EndCondition/EndConditionType.hpp"

using PropertiesPtr = std::unique_ptr<Properties>;
using ControlsPtr = std::unique_ptr<Controls>;
using MapPtr = std::unique_ptr<Map>;
using ObjectPtr = std::shared_ptr<Object>;
using PlayerPtr = std::shared_ptr<Player>;
using RulePtr = std::unique_ptr<Rule>;

class GameContext {
	PropertiesPtr properties;
	ControlsPtr controls;
	MapPtr map;
	std::unordered_map<ObjectType, std::vector<ObjectPtr>> objects;
	std::unordered_map<RuleType, std::vector<RulePtr>> rules; // ptr isn't needed; remove later
	std::vector<EndCondition> endConditions;
	std::vector<Event> events;

	// score system
	// map name to score
	// if any score > threshold, quit game
	// draw this from engine

public:
	GameContext();
	int parseGameDefinition(std::string filePath);
	void parseProperty(const pugi::xml_node &property);
	void parseControl(const pugi::xml_node &control);
	void parseMap(const pugi::xml_node &map);
	void parseObjects(const pugi::xml_node &objects);
	void parsePlayers(const pugi::xml_node &players);
	void parseEvents(const pugi::xml_node &events);
	void parseRules(const pugi::xml_node &rules);
	void parseEndConditions(const pugi::xml_node &endCondition);

	std::vector<ObjectPtr> getPlayers();
	std::vector<ObjectPtr> getObjectsByType(ObjectType objType);
	ObjectPtr getObject(std::string objName);
	void processEvents();
	void processRules();
	void processEndConditions(sf::Clock &clock);
};