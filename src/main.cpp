#include <iostream>

#include "Validator/Validator.hpp"
#include "Parser/Parser.hpp"

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        printf("SchemaValidator <schema file> <xml file>\n");
        return 0;
    }

    XMLPlatformUtils::Initialize();

    ValidateSchema(argv[1], argv[2]);

    XMLPlatformUtils::Terminate();



    return 0;
}
