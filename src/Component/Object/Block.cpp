#include "Component/Object/Block.hpp"

Block::Block(std::string name) : Player(name), block(sf::Vector2f(100, 100)), speed(10.0f) {
	block.setPosition(sf::Vector2f(100, 100));
}

void Block::draw(std::unique_ptr<sf::RenderWindow> &window) {
	// window bounds
	window->draw(block);
}

void Block::move(float dirX, float dirY) {
	block.move(speed * dirX, speed * dirY);
}

sf::Vector2f Block::getPosition() {
	return block.getPosition();
}

sf::FloatRect Block::getGlobalBounds() {
	return block.getGlobalBounds();
}

void Block::moveController(bool useAlternate) {
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

	if (!useAlternate) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (this->getPosition().x > 0)
				this->move(-1.f, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (this->getPosition().x < videoMode.width)
				this->move(1.f, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (this->getPosition().y > 0)
			this->move(0.f, -1.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (this->getPosition().y < videoMode.height)
				this->move(0.f, 1.f);
		}
	} else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (this->getPosition().x > 0)
				this->move(-1.f, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (this->getPosition().x < videoMode.width)
				this->move(1.f, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (this->getPosition().y > 0)
			this->move(0.f, -1.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (this->getPosition().y < videoMode.height)
				this->move(0.f, 1.f);
		}
	}
}

void Block::setName(std::string name) {

}

std::string Block::getName() {
	return this->name;
}

ObjectType Block::getType() {
	return ObjectType::Block;
}

void Block::setType(ObjectType type) {
	type = ObjectType::Block;
}