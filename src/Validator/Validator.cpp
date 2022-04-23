#include <iostream>

#include "Validator/Validator.hpp"


XVGDLValidator::XVGDLValidator() {
	XMLPlatformUtils::Initialize();
	domParser = std::make_unique<XercesDOMParser>();
	parserErrorHandler = std::make_unique<ParserErrorHandler>();
}

int XVGDLValidator::validateSchema(std::string schemaFilePath, std::string xmlFilePath)
{
    if (domParser->loadGrammar(schemaFilePath.c_str(), Grammar::SchemaGrammarType) == nullptr)
    {
        std::cout << "Couldn't load schema\n";
        return 0;
    }

    domParser->setErrorHandler(parserErrorHandler.get());
    domParser->setValidationScheme(XercesDOMParser::Val_Auto);
    domParser->setDoNamespaces(true);
    domParser->setDoSchema(true);
    domParser->setValidationConstraintFatal(true);

    domParser->parse(xmlFilePath.c_str());
    if (domParser->getErrorCount() == 0) {
        std::cout << "XML file validated against the schema successfully\n";
		return 1;
	}
    else {
        std::cout << "XML file doesn't conform to the schema\n";
		return 0;
	}
	XMLPlatformUtils::Terminate();
	return 0;
}