#include "Game.hpp"
#include <iostream>
#include <sstream>

#define PI 3.1415926535

Game::Game(int width, int height, std::string title) :
    window(sf::VideoMode(width, height), title, sf::Style::Default),
    paddle(paddleWidth,paddleHeight),
    ball(ballRadius),
    border(sf::Vector2f(width-2*marginWidth, height-2*marginHeight))
{
    this->screen = 0;
    this->width = width;
    this->height = height;

    toInitState();

    if(!font.loadFromFile("Akronim-Regular.ttf"))
    {
        std::cout << "Couldn't load the font"<<std::endl;
    }
    if(!texture.loadFromFile("texture.png"))
    {
        std::cout << "Couldn't load the texture." << std::endl;
    }

    startText.setFont(font);
    exitText.setFont(font);
    gameOverText.setFont(font);
    startText.setCharacterSize(titleSize);
    startText.setFillColor(sf::Color::Green);
    startText.setString("START");
    exitText.setCharacterSize(titleSize);
    exitText.setString("EXIT");
    startText.setPosition(sf::Vector2f((width-startText.getLocalBounds().width)/2,
                                       height/2 - titleSize));
    exitText.setPosition(sf::Vector2f((width-exitText.getLocalBounds().width)/2,
                                      height/2));

    gameOverText.setCharacterSize(bigTextSize);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(sf::Vector2f((width-gameOverText.getLocalBounds().width)/2,
                                          height/2-bigTextSize));

    border.setPosition(sf::Vector2f(marginWidth,marginHeight));
    border.setOutlineThickness(1);
    border.setOutlineColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);

//            window.setKeyRepeatEnabled(false);
}

void Game::toInitState() {

    paddle.setPosition((width-paddleWidth)/2, height - paddleHeight - marginHeight);
    ball.setPosition((width-2*ballRadius)/2, height-paddleHeight-2*ballRadius-1-marginHeight);
    ballheld = 1;

    lives = 3;
    lvl = 1;
    score = 0;

    bricks.clear();

}

void Game::loadBricksFromFile(char* str)
{
    FILE *f = fopen(str, "r");
    if(f == NULL)
    {
        //std::cout<< "Couldn't open file";
        //error
        return;
    }
    char ch;
    int px = marginWidth,py=marginHeight;
    char s[6];
    fgets(s,5,f);
    int n = atoi(s);
    brickWidth = (width-marginWidth*2)/n;
    while((ch=fgetc(f))!=EOF)
    {
        if(ch=='\n')
        {
            py+=brickHeight;
            px = marginWidth;
            continue;
        }
        int t = (int)ch-'0';
        if(t != 0)
        {
            bricks.push_back(new Brick(sf::Vector2f(px,py),
                                       sf::Vector2f(brickWidth, brickHeight),
                                       t));
        }
        px+=brickWidth;
    }
    fclose(f);
}

void Game::drawInfo()
{


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(marginHeight-10);
    text.setColor(sf::Color::Yellow);
    std::stringstream str;
    str << "Score: " << score;
    text.setString(str.str());
    text.setPosition(sf::Vector2f(width-300,0));
    window.draw(text);

    str.str(std::string());
    str << "LEVEL: " << lvl;
    text.setString(str.str());
    text.setPosition(sf::Vector2f(marginWidth,0));
    window.draw(text);

    sf::Sprite heartsprite;
    heartsprite.setTexture(texture);
    heartsprite.setTextureRect(sf::IntRect(0,0,60,60));
    heartsprite.setScale(sf::Vector2f(0.8f,0.8f));

    for(int i=0; i<lives; i++)
    {
        heartsprite.setPosition(sf::Vector2f(marginWidth+i*60,height-marginHeight));
        window.draw(heartsprite);
    }
}

void Game::draw()
{
    window.clear();

    if(screen == 0)
    {
        window.draw(startText);
        window.draw(exitText);
    }
    else if(screen == 1)
    {

        std::list<Brick*>::iterator it;
        for(it=bricks.begin(); it != bricks.end(); ++it)
        {
            window.draw(*(*it));
        }
        window.draw(paddle);
        window.draw(ball);
        drawInfo();
    } else if(screen == 2) {
        window.draw(gameOverText);
    }
    window.draw(border);

    window.display();
}

void Game::resetTextColors()
{
    exitText.setFillColor(sf::Color::Green);
    startText.setFillColor(sf::Color::Green);
}

void Game::handleEvents()
{
    sf::Event event;
    int x,y;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if(screen == 1)
            {
                if(event.key.code == sf::Keyboard::Left)
                    paddle.setVelocity(-paddleVel);
                else if(event.key.code == sf::Keyboard::Right)
                    paddle.setVelocity(paddleVel);
                else if(event.key.code == sf::Keyboard::Space)
                {
                    if(ballheld == 1)
                    {
                        ball.setVelocity(sf::Vector2f(0,-ballInitVel));
                        ballheld = 0;
                    }
                }
            } else if(screen == 2) {
                screen = 0;
            }
            break;
        case sf::Event::KeyReleased:
            if(screen == 1)
            {
                if((event.key.code == sf::Keyboard::Left && paddle.getVelocity()<0)||
                        (event.key.code == sf::Keyboard::Right && paddle.getVelocity()>0))
                    paddle.setVelocity(0);
            }
            break;
        case sf::Event::MouseMoved:
            x = event.mouseMove.x;
            y = event.mouseMove.y;
            //std::cout << x << "," << y << std::endl;
            if(screen == 0)
            {
                resetTextColors();
                sf::FloatRect startRect(startText.getPosition().x,
                                        startText.getPosition().y,
                                        startText.getLocalBounds().width,
                                        startText.getCharacterSize());
                sf::FloatRect exitRect(exitText.getPosition().x,
                                       exitText.getPosition().y,
                                       exitText.getLocalBounds().width,
                                       exitText.getCharacterSize());
                //sf::FloatRect exitRect = exitText.getLocalBounds();
                //std::cout << startRect.top << std::endl;
                if(startRect.contains(x,y))
                {
                    startText.setFillColor(sf::Color::Yellow);
                }
                else if(exitRect.contains(x,y))
                {
                    exitText.setFillColor(sf::Color::Yellow);
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            x = event.mouseButton.x;
            y = event.mouseButton.y;
            if(screen == 0)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::FloatRect startRect(startText.getPosition().x,
                                            startText.getPosition().y,
                                            startText.getLocalBounds().width,
                                            startText.getCharacterSize());
                    sf::FloatRect exitRect(exitText.getPosition().x,
                                           exitText.getPosition().y,
                                           exitText.getLocalBounds().width,
                                           exitText.getCharacterSize());
                    //sf::FloatRect exitRect = exitText.getLocalBounds();
                    //std::cout << startRect.top << std::endl;
                    if(startRect.contains(x,y))
                    {
                        screen=1;
                        loadBricksFromFile("1.lvl");
                    }
                    else if(exitRect.contains(x,y))
                    {
                        window.close();
                    }
                }
            }
        default:
            break;
        }
    }
}

void Game::update(float dt)
{
    sf::Vector2f pPos = paddle.getPosition();
    sf::Vector2f pSize = paddle.getSize();
    paddle.update(dt);
    if(paddle.isOutOfBounds(marginWidth, width-marginWidth))
    {
        paddle.revert(dt);
    }
    if(ballheld == 1)
    {
        ball.setPosition(sf::Vector2f(pPos.x+pSize.x/2-ball.getRadius(),
                                      height-paddleHeight-2*ball.getRadius()-1-marginHeight));
        ball.setVelocity(0.0,0);
    }
    else
    {
        ball.update(dt);
        int oobstat = ball.isOutOfBounds(sf::Vector2f(marginWidth, marginHeight),
                                         sf::Vector2f(width-marginWidth, height-marginHeight));
        sf::Vector2f bPos = ball.getPosition();
        int d = 2*ball.getRadius();
        if(oobstat != 0)
        {
            if(bPos.y+d >= height-marginHeight)
            {
                lives--;
                if(lives == 0) {
                    screen = 2;
                    toInitState();
                }
                ballheld=1;
                return;
            }
            ball.revert(dt);
            ball.bounce(oobstat);
        }


        if(hasCollided(bPos, sf::Vector2f(d,d),pPos, pSize) != 0)   //collided with paddle
        {
            int ballcenter = bPos.x+d/2;
            int paddlecenter = pPos.x + pSize.x/2;
            int k = pSize.x/2;
            int diff = ballcenter - paddlecenter;
            float angle = PI*(13*diff - 18*k)/(float)(36*k);
            ball.setVelocity(angle, ballInitVel);
        }

        std::list<Brick*>::iterator it = bricks.begin();
        while(it != bricks.end())
        {
            int colstat=hasCollided(bPos, sf::Vector2f(d,d), (*it)->getPosition(),(*it)->getSize());
            if(colstat != 0)
            {
                ball.revert(dt);
                ball.bounce(colstat);
                //std::cout << "i"<<(*it)->getType() <<std::endl;
                score += (*it)->getType();
                (*it)->demote();
                //std::cout << "f"<<(*it)->getType() <<std::endl;
                if((*it)->getType()==0)
                {
                    bricks.erase(it++);
                }
                else ++it;
                break;
            }
            else
            {
                ++it;
            }
        }
    }//else part of ballheld==1
}

int Game::hasCollided(sf::Vector2f pos1, sf::Vector2f size1, sf::Vector2f pos2, sf::Vector2f size2)
{
    bool xin=false, yin = false;
    bool pos1xin = (pos1.x >= pos2.x && pos1.x <= pos2.x + size2.x);
    bool pos1endxin = (pos1.x+size1.x >= pos2.x && pos1.x+size1.x <= pos2.x + size2.x);
    bool pos1yin = (pos1.y >= pos2.y && pos1.y <= pos2.y + size2.y);
    bool pos1endyin =  (pos1.y+size1.y >= pos2.y && pos1.y+size1.y <= pos2.y + size2.y);
    if( pos1xin || pos1endxin)
    {
        xin = true;
    }
    if( pos1yin || pos1endyin)
    {
        yin = true;
    }
    if(xin &&yin)
    {
        if(pos1xin && pos1endxin )
            return 2; /**vertical bounce**/
        else if(pos1yin && pos1endyin)
            return 1; /**horizontal bounces**/
        else
            return 3; /**diagonal bounce**/
    }
    return 0;
}

bool Game::isRunning()
{
    return window.isOpen();
}
