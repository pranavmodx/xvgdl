#include "Engine/Engine.hpp"

int main(int argc, const char *argv[])
{
    std::string filePath = "examples/test.xml";

    Engine engine;
    if (engine.loadGameContext(filePath)) {
        engine.launchGame();
    }

    return 0;
}
