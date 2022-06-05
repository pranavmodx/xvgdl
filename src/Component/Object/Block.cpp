#include "Component/Object/Block.hpp"

Block::Block(const std::string &name, const std::string &position) : Player(name), block(sf::Vector2f(20, 300)), speed(10.0f) {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	if (position == "left")
		block.setPosition(sf::Vector2f(100, desktop.height / 2 - 50));
	else if (position == "right")
		block.setPosition(sf::Vector2f(desktop.width - 200, desktop.height / 2 - 50));
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
	if (isAI)
		return;

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

void Block::setName(const std::string &name) {

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

void Block::setIsAI() {
	isAI = true;
}

bool Block::getIsAI() {
	return isAI;
}

void Block::AIController(sf::Vector2f ballPos, int id) {
	if (id == 1)
		speed = 7;
	else
		speed = 15;

	if (block.getPosition().y + block.getSize().y > ballPos.y)
		move(0.f, -1.f);
	else if (block.getPosition().y + block.getSize().y < ballPos.y)
		move(0.f, 1.f);
}
