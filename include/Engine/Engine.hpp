#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Context/GameContext.hpp"
#include "Util/Debug.hpp"

// class Object;
// using ObjectPtr = std::unique

using DebugPtr = std::shared_ptr<Debug>;

class Engine {
	std::unique_ptr<GameContext> gameContext;

	sf::VideoMode videoMode;
    std::unique_ptr<sf::RenderWindow> window;
    sf::Event event;
    sf::Clock clock;

    std::vector<DebugPtr> debugs; // stack alloc throws seg fault; investigate later

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