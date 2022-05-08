#include "Component/Object/Block.hpp"

void Block::draw(std::unique_ptr<sf::RenderWindow> &window) {
	sf::RectangleShape block(sf::Vector2f(100.0f, 100.0f));
	window->draw(block);
}