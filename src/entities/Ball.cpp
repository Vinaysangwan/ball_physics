#include "Ball.hpp"

//***************************************************************************************
//********************************** Private Functions **********************************
//***************************************************************************************

void Ball::initVariables()
{
    // Ball Speed
    this->speed = sf::Vector2(300.0f, 300.0f);

    // Ball Radius
    this->radius = 10.0f;
}

void Ball::initBall()
{
    // Init Ball , Radius & Scale & Thichness
    this->ball = new sf::CircleShape(this->radius);
    // this->ball->setOutlineThickness(3.0f);

    // Ball Origin & Position
    this->ball->setOrigin(sf::Vector2f{this->radius, this->radius});             // Origin
    this->ball->setPosition(sf::Vector2f{this->mouse_pos.x, this->mouse_pos.y}); // Position

    // Ball Fill & Thickness Color
    this->ball->setFillColor(sf::Color(255, 255, 255));
    // this->ball->setOutlineColor(sf::Color(0, 0, 0));
}

void Ball::moveBall()
{
    // Ball Collision With Window
    { // For Right Window
        if (this->ball->getPosition().x + this->radius >= this->video_mode.size.x)
        {
            this->speed.x *= -1;
            this->ball->setPosition(sf::Vector2f{this->video_mode.size.x - this->radius - 0.1f, this->ball->getPosition().y});
        }
        // For Left Window
        else if (this->ball->getPosition().x - this->radius <= 0.0f)
        {
            this->speed.x *= -1;
            this->ball->setPosition(sf::Vector2f{this->radius + 0.1f, this->ball->getPosition().y});
        }

        // For Top Window
        if (this->ball->getPosition().y + this->radius >= this->video_mode.size.y)
        {
            this->speed.y *= -1;
            this->ball->setPosition(sf::Vector2f{this->ball->getPosition().x, this->video_mode.size.y - this->radius - 0.1f});
        }
        // For the Bottom Window
        else if (this->ball->getPosition().y - this->radius <= 0.0f)
        {
            this->speed.y *= -1;
            this->ball->setPosition(sf::Vector2f{this->ball->getPosition().x, this->radius + 0.1f});
        }
    }

    this->ball->move(this->speed * delta_time);
}

//***************************************************************************************
//********************************** Public Functions ***********************************
//***************************************************************************************

Ball::Ball(sf::RenderWindow *window)
{
    this->video_mode.size = window->getSize();

    this->mouse_pos = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y));

    std::cout << "Mouse Pos: (" << this->mouse_pos.x << " , " << this->mouse_pos.y << ")" << std::endl;

    this->initVariables(); // Init Variables
    this->initBall();      // Init ball
}

Ball::~Ball()
{
    delete this->ball;
}

void Ball::updateBall(float delta_time)
{
    this->delta_time = delta_time;

    this->moveBall();
}

void Ball::renderBall(sf::RenderWindow *window)
{
    window->draw(*this->ball);
}
