#include "Component/Object/Player.hpp"

Player::Player(std::string name) : Object(name) {

}

void Player::setType(ObjectType type) {
	this->type = type;
}

ObjectType Player::getType() {
	return type;
}

std::string Player::getName() {
	return this->name;
}