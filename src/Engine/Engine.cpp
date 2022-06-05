#include <SFML/Graphics.hpp>
#include <sstream>

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
    scoreBoard = std::make_unique<ScoreBoard>("0 - 0", sf::Vector2f(desktop.width / 2 - 20, desktop.height / 2 - 50));
    timer = std::make_unique<Timer>("0", sf::Vector2f(desktop.width / 2 - 150, 0.1 * desktop.height));
    // todo : set position explicitly to get globalBounds 
}

void Engine::initWindow()
{
    std::string winTitle = "XVGDL";
    // todo : get game title from properties and use
    window = std::make_unique<sf::RenderWindow>(videoMode, winTitle);
    window->setFramerateLimit(60); // fixed for now; adapt to all fps later
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

    auto objs = gameContext->getObjectsByType(ObjectType::Object);
    auto ball = std::static_pointer_cast<Ball>(objs[0]);

    p1->getIsAI() ? p1->AIController(ball->getPosition()) : p1->moveController();
    p2->getIsAI() ? p2->AIController(ball->getPosition(), 2) : p2->moveController(true);
}

void Engine::update()
{
    this->pollEvents();
    gameContext->processEvents();
    gameContext->processRules();
    gameContext->processEndConditions(clock, scoreBoard->getMaxScore());
    timer->update(clock.getElapsedTime().asSeconds());
}

void Engine::render()
{
    window->clear(sf::Color(35, 35, 35));

    auto players = gameContext->getPlayers();
    auto p1 = std::static_pointer_cast<Block>(players[0]);
    auto p2 = std::static_pointer_cast<Block>(players[1]);

    auto objs = gameContext->getObjectsByType(ObjectType::Object);
    auto ball = std::static_pointer_cast<Ball>(objs[0]);

    p1->draw(window);
    p2->draw(window);
    ball->draw(window);
    ball->update(window, scoreBoard.get()); // should ideally be in Engine::update(); change later

    for (auto dbg: debugs)
        dbg->draw(window.get());

    scoreBoard->draw(window.get());
    timer->draw(window.get());

    window->display();
}