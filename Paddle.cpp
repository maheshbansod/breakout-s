
#include "Paddle.hpp"
#include <iostream>

Paddle::Paddle(int width, int height) :
    rectshape(sf::Vector2f(width, height)) {
    vel = 0;
    rectshape.setFillColor(sf::Color(127,127, 255));
}

void Paddle::update(float dt) {
    move(vel*dt, 0);
}

void Paddle::revert(float dt) {
    move(-vel*dt, 0);
}

bool Paddle::isOutOfBounds(int zero, int width) {
    sf::Vector2f pos = getPosition();
    //std::cout << pos.x <<","<<width<<std::endl;
    if(pos.x < zero || pos.x > width- rectshape.getSize().x) return true;
    return false;
}

void Paddle::setVelocity(int v) {
    vel = v;
}

int Paddle::getVelocity() {
    return vel;
}

sf::Vector2f Paddle::getSize() {
    return rectshape.getSize();
}

