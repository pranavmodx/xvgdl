#include <SFML/Graphics.hpp>

#include "Engine/Engine.hpp"

int Engine::loadGameContext(std::string filePath) {
	gameContext = std::make_unique<GameContext>();
	if (gameContext->parseGameDefinition(filePath))
		return 1;
	return 0;
}

void Engine::launchGame() {
	initVariables();
    initWindow();

	while (isRunning()) {
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

        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {      
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
            }

        default:
            break;
        }
    }
}

void Engine::update()
{
    this->pollEvents();
}

void Engine::render()
{
    window->clear(sf::Color(35, 35, 35));

    for (auto object : gameContext->getObjects())
        object->draw(window);

    window->display();
}