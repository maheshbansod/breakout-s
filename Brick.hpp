#ifndef BRICK_HPP_INCLUDED
#define BRICK_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Brick : public sf::Drawable, public sf::Transformable {

    sf::RectangleShape rectshape;
    //sf::Sprite sprite;
    int type;

public:
    Brick(sf::Vector2f pos, sf::Vector2f size, int type);

    void demote();
    void setAppropriateColor();

    int getType();
    sf::Vector2f getSize();
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();

        target.draw(rectshape, states);
    }
};

#endif // BRICK_HPP_INCLUDED
