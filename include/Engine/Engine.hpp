#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Context/GameContext.hpp"

// class Object;
// using ObjectPtr = std::unique

class Engine {
	std::unique_ptr<GameContext> gameContext;

	sf::VideoMode videoMode;
    std::unique_ptr<sf::RenderWindow> window;
    sf::Event event;
    sf::Clock clock;

	void initVariables();
    void initWindow();

public:
	int loadGameContext(std::string filePath);
	void launchGame();

	bool isRunning();
    void pollEvents();
    void handlePlayerControl();
    void update();
    void render();
};