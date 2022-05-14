#include <SFML/Graphics.hpp>

#include "Engine/Engine.hpp"

int Engine::loadGameContext(std::string filePath)
{
    gameContext = std::make_unique<GameContext>();
    if (gameContext->parseGameDefinition(filePath))
        return 1;
    return 0;
}

void Engine::launchGame()
{
    initVariables();
    initWindow();

    while (isRunning())
    {
        update();
        render();
    }
}

void Engine::initVariables()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    videoMode.height = desktop.height;
    videoMode.width = desktop.width;
    window = nullptr;
}

void Engine::initWindow()
{
    window = std::make_unique<sf::RenderWindow>(videoMode, "XVGDL");
    window->setFramerateLimit(60);
}

bool Engine::isRunning()
{
    return window->isOpen();
}

void Engine::pollEvents()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            break;

        default:
            break;
        }
    }

    auto players = gameContext->getPlayers();
    auto p1 = std::static_pointer_cast<Block>(players[0]);
    auto p2 = std::static_pointer_cast<Block>(players[1]);

    p1->moveController();
    p2->moveController(true);

    gameContext->processRules();
}

void Engine::update()
{
    this->pollEvents();

}

void Engine::render()
{
    window->clear(sf::Color(35, 35, 35));

    auto players = gameContext->getPlayers();
    auto p1 = std::static_pointer_cast<Block>(players[0]);
    auto p2 = std::static_pointer_cast<Block>(players[1]);

    p1->draw(window);
    p2->draw(window);

    window->display();
}