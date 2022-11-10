#include "Component/Object/Ball.hpp"

std::vector<int> Ball::initDirY = {-1, 1};

Ball::Ball(std::string name) : Object(name), ball(15.f), dirX(-1), dirY(Ball::initDirY[(int)rand() % 2]), speed(5) {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    ball.setPosition(sf::Vector2f(desktop.width / 2 - ball.getRadius(), desktop.height / 2 - ball.getRadius()));
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

void Ball::update(const std::unique_ptr<sf::RenderWindow> &window, ScoreBoard *scoreBoard) {
    
    auto pos = ball.getPosition(); // note : returns top left point of bbox
    if (pos.x <= 0 or pos.x >= window->getSize().x - 2 * ball.getRadius()) {
        dirX *= -1;
        if (pos.x <= 0)
            scoreBoard->update(0, 1);
        if (pos.x >= window->getSize().x - 2 * ball.getRadius())
            scoreBoard->update(1, 0);
    }
    if (pos.y <= 0 or pos.y >= window->getSize().y - 2 * ball.getRadius()) {
        dirY *= -1;
    }
    ball.move(speed * dirX, speed * dirY);
}

void Ball::setDirX(int dir) {
    dirX = dir;
}

void Ball::setDirY(int dir) {
    dirY = dir;
}