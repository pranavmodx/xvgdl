#include "Engine/Engine.hpp"

int main(int argc, const char *argv[])
{
    std::string filePath = "/Users/pranavmodx/Dev/git_clones/xvgdl/examples/pacman.xml"; // relative path not working for some reason :/

    Engine engine;
    if (engine.loadGameContext(filePath)) {
        engine.launchGame();
    }

    return 0;
}
