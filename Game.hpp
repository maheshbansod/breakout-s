#ifndef GAMEE_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

class Game {
    int width, height;
    int screen;
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Font font;
    sf::Text startText;
    sf::Text exitText;
    sf::Text gameOverText;
    sf::RectangleShape border;
    Paddle paddle;
    Ball ball;
    std::list<Brick*> bricks;
    int ballheld;
    int lives;
    int lvl;
    int score;

    static const int paddleWidth = 200;
    static const int paddleHeight = 20;
    static const int paddleVel = 500;
    static const int ballRadius = 10;
    static const int ballInitVel = 500;
    static const int marginWidth = 10;
    static const int marginHeight = 50;
    static const int brickHeight = 30;
    static const int titleSize = 50;
    static const int bigTextSize = 100;

    int brickWidth;

public:
    Game(int width, int height, std::string title);
    void handleEvents();
    void update(float dt);
    void draw();
    void drawInfo();
    void resetTextColors();

    void toInitState();

    bool isRunning();
    int hasCollided(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);

    void loadBricksFromFile(char *str);
};

#endif
