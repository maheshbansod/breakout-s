#include "Ball.hpp"
#include <math.h>

Ball::Ball(int r) :
    circle(r),
    vel(0,0) {
    circle.setFillColor(sf::Color::White);
//    reverted = true;
 //   bounced = true;
}

void Ball::update(float dt) {
    //reverted = false;
    //bounced = false;
    move(vel*dt);
}

void Ball::revert(float dt) {
    //if(reverted) return;
    //reverted = true;
    move(-vel*dt);
}

void Ball::bounce(int dir) {
    //if(bounced) return;
    //bounced = true;
    switch(dir) {
    case 3:
        vel.x = -vel.x;
        vel.y = -vel.y;
        break;
    case 1:
        vel.x = -vel.x;
        break;
    case 2:
        vel.y = -vel.y;
        break;
    default:
        break;
    }
}

void Ball::setVelocity(sf::Vector2f v) {

    vel = v;
}

void Ball::setVelocity(float angle, int m){
    vel.x = m * cos(angle);
    vel.y = m * sin(angle);
}

sf::Vector2f Ball::getVelocity() {
    return vel;
}

int Ball::getRadius() {
    return circle.getRadius();
}

int Ball::isOutOfBounds(sf::Vector2f zero, sf::Vector2f bounds) {
    /**
    * 0 if inside
    * 1 for horizontal bounce
    * 2 for vertical bounce
    **/
    sf::Vector2f pos = getPosition();
    int d = 2*circle.getRadius();
    if(pos.x < zero.x || pos.x + d > bounds.x)
        return 1;
    if(pos.y < zero.y || pos.y + d > bounds.y)
            return 2;
    return 0;
}
