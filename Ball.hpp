#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable, public sf::Transformable{
    sf::Vector2f vel;
    sf::CircleShape circle;
    //bool reverted;
    //bool bounced;

public:
    Ball(int r);

    void update(float);
    void revert(float);
    void bounce(int);
    sf::Vector2f getVelocity();
    void setVelocity(sf::Vector2f);
    void setVelocity(float angle, int magnitude);
    int isOutOfBounds(sf::Vector2f, sf::Vector2f);

    int getRadius();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();

        target.draw(circle, states);
    }
};

#endif // BALL_HPP_INCLUDED
