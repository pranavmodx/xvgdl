#include "Context/GameContext.hpp"

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

	Generator generator;
	
	for (pugi::xml_node x : doc.first_child()) {
		std::string tag = x.name();
		std::cout << tag << std::endl;

		// if (tag == PROPERTY) {
		// 	// properties = generator.createProperty(x);
		// }
		// else if ()

		for (auto y: x.children())
			std::cout << y.name() << " ";
		std::cout << std::endl;
	}

	return 1;
}