#ifndef PADDLE_HPP_INCLUDED
#define PADDLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable, public sf::Transformable{
    sf::RectangleShape rectshape;
    int vel;
    //int x;

public:
    Paddle(int width, int height);

    bool isOutOfBounds(int zero,int width);

    void setVelocity(int v);
    int getVelocity();
    sf::Vector2f getSize();

    void update(float);
    void revert(float);

private:
    //virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();

        target.draw(rectshape, states);
    }
};

#endif // PADDLE_HPP_INCLUDED
