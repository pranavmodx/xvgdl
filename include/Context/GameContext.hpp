#pragma once

#include <vector>

#include "Token.hpp"
#include "Validator/Validator.hpp"
#include "pugixml/pugixml.hpp"

#include "Component/Properties.hpp"
#include "Component/Controls.hpp"
#include "Component/Map.hpp"
#include "Component/Object/Object.hpp"
#include "Component/Object/Player.hpp"
#include "Component/Object/Block.hpp"

using PropertiesPtr = std::unique_ptr<Properties>;
using ControlsPtr = std::unique_ptr<Controls>;
using MapPtr = std::unique_ptr<Map>;
using ObjectPtr = std::shared_ptr<Object>;

class GameContext {
	PropertiesPtr properties;
	ControlsPtr controls;
	MapPtr map;
	std::vector<ObjectPtr> objects;
public:
	GameContext();
	int parseGameDefinition(std::string filePath);
	void parseProperty(const pugi::xml_node &property);
	void parseControl(const pugi::xml_node &control);
	void parseMap(const pugi::xml_node &map);
	void parseObjects(const pugi::xml_node &object);

	std::vector<ObjectPtr> getObjects();
};