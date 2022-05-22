#include "Component/Object/Ball.hpp"

Ball::Ball(std::string name) : Object(name), ball(50.f), dirX(-1), dirY(0), speed(10) {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    ball.setPosition(sf::Vector2f(desktop.width / 2 - 25, desktop.height / 2 - 25));
}

ObjectType Ball::type = ObjectType::Ball;

std::string Ball::getName() {
    return name;
}

ObjectType Ball::getType() {
    return ObjectType::Ball;
}

sf::Vector2f Ball::getPosition() {
    return ball.getPosition();
}

sf::FloatRect Ball::getGlobalBounds() {
    return ball.getGlobalBounds();
}

void Ball::setName(const std::string &name) {}
void Ball::setType(ObjectType type) {}

void Ball::draw(std::unique_ptr<sf::RenderWindow> &window) {
    window->draw(ball);
}

void Ball::move(float dirX, float dirY) {
    ball.move(speed * dirX, speed * dirY);
}

void Ball::update(const std::unique_ptr<sf::RenderWindow> &window) {
    auto pos = ball.getPosition();
    if (pos.x <= 0 or pos.x >= window->getSize().x)
        dirX *= -1;
    if (pos.y <= 0 or pos.y >= window->getSize().y)
        dirY *= -1;
    ball.move(speed * dirX, speed * dirY);
}

void Ball::setDirX(int dir) {
    dirX = dir;
}

void Ball::setDirY(int dir) {
    dirY = dir;
}