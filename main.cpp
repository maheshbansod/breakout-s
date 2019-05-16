
#include <SFML/Graphics.hpp>
#include "Game.hpp"

#define WIDTH 800
#define HEIGHT 600
#define FPS 60

int main()
{
    Game game(WIDTH, HEIGHT,"Breakout S");
    sf::Clock clock;
    sf::Time elapsed = clock.getElapsedTime();

    while (game.isRunning())
    {
        game.handleEvents();
        game.update(elapsed.asSeconds());
        game.draw();
        elapsed = clock.restart();
    }

    return 0;
}
