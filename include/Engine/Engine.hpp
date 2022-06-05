#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Context/GameContext.hpp"
#include "Util/Debug.hpp"
#include "Component/ScoreBoard/ScoreBoard.hpp"
#include "Component/Timer/Timer.hpp"

using DebugPtr = std::shared_ptr<Debug>;

class Engine {
	std::unique_ptr<GameContext> gameContext;

	sf::VideoMode videoMode;
    std::unique_ptr<sf::RenderWindow> window;
    sf::Event event;
    sf::Clock clock;

    std::vector<DebugPtr> debugs; // stack alloc throws seg fault; investigate later
    std::unique_ptr<ScoreBoard> scoreBoard;
    std::unique_ptr<Timer> timer;

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