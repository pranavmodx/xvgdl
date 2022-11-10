#include <iostream>
#include <time.h>
#include "Engine/Engine.hpp"

int main(int argc, const char *argv[])
{
    srand((int)(time(0)));
    std::string filePath = "examples/pong.xml";

    Engine engine;
    if (engine.loadGameContext(filePath)) {
        std::cout << "Game created successfully\n";
        engine.launchGame();
    }
    
    return 0;
}
