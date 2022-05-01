#include "Context/GameContext.hpp"

GameContext::GameContext() {
	properties = nullptr;
}

int GameContext::parseGameDefinition(std::string filePath) {
	// Again relative path issues :/
	std::string schemaPath = "/Users/pranavmodx/Dev/git_clones/xvgdl/schema/xvgdl.xsd";

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
	for (const pugi::xml_node &tag : gameDefinition) {
		std::string tagName = tag.name();

		if (tagName == PROPERTY) {
			if (!properties)
				properties = std::make_unique<Properties>();
			parseProperty(tag);
		} else if (tagName == CONTROLS) {
			controls = std::make_unique<Controls>();
			parseControl(tag);
		} else if (tagName == MAP) {
			map = std::make_unique<Map>();
			parseMap(tag);
		} else if (tagName == OBJECTS) {
			objects.push_back(parseObject(tag));
		}
	}

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