
#include "Brick.hpp"

Brick::Brick(sf::Vector2f pos, sf::Vector2f size, int type) :
    rectshape(sf::Vector2f(size.x, size.y)) {
    setPosition(pos);
    this->type=type;
//    this->sprite = s;
    setAppropriateColor();
    rectshape.setOutlineColor(sf::Color::Black);
    rectshape.setOutlineThickness(1);
}

void Brick::setAppropriateColor() {
    if(type==1) {
        rectshape.setFillColor(sf::Color::Red);
    } else if(type==2)
        rectshape.setFillColor(sf::Color::Yellow);
    else if(type==3)
        rectshape.setFillColor(sf::Color::Green);
}

void Brick::demote() {
    type--;
    setAppropriateColor();
}

int Brick::getType() {
    return type;
}

sf::Vector2f Brick::getSize() {
    return rectshape.getSize();
}
