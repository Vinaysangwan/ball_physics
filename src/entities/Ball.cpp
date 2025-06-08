#include "Ball.h"

void Ball::init_Variables(const sf::Vector2f &position, const sf::Color &color)
{
    // Random
    random = new Random();

    // Forces
    this->gravity = 980.0f;
    this->friction = gravity * friction_coefficient;

    this->position = position;
    this->color = color;
    this->radius = 10.0f;
    this->speed = random->get_RandomFloat(-200.0f, 200.0f);
    velocity = sf::Vector2f(speed, 0.0f);
}

void Ball::init_Circle()
{
    this->setRadius(radius);
    this->setPosition(position);
    this->setOrigin(sf::Vector2f{radius, radius});
    this->setFillColor(color);
}

void Ball::move_ball(const float &delta_time)
{
    this->move(velocity * delta_time);

    window_Collision(delta_time);

    velocity.y += gravity * delta_time;
}

void Ball::window_Collision(const float &delta_time)
{
    // Collision with Bottom Window Border
    if (this->getPosition().y + radius >= window_height && velocity.y >= 0)
    {
        this->setPosition(sf::Vector2f(this->getPosition().x, window_height - radius));
        velocity.y = -velocity.y * restitution;

        // Firiction
        if (velocity.x > 0)
        {
            velocity.x -= get_Max(0.0f, friction * delta_time);
        }
        else if (velocity.x < 0)
        {
            velocity.x += get_Min(0.0f, friction * delta_time);
        }
    }
    // Collision with Top Window Border
    else if (this->getPosition().y - radius <= 0.0f && velocity.y < 0)
    {
        this->setPosition(sf::Vector2f(this->getPosition().x, radius));
        velocity.y = -velocity.y * restitution;
    }

    // Collision with left Window Border
    if (this->getPosition().x - radius <= 0.0f && velocity.x < 0)
    {
        this->setPosition(sf::Vector2f(radius, this->getPosition().y));
        velocity.x = -velocity.x * restitution;
    }
    // Collision with Right Window Border
    else if (this->getPosition().x + radius >= window_width && velocity.x >= 0)
    {
        this->setPosition(sf::Vector2f(window_width - radius, this->getPosition().y));
        velocity.x = -velocity.x * restitution;
    }
}

Ball::Ball(const sf::Vector2f &position, const sf::Color &color)
    : friction_coefficient(0.4f), restitution(0.85f)
{
    init_Variables(position, color);
    init_Circle();
}

Ball::~Ball()
{
}

void Ball::update(const float &delta_time)
{
    move_ball(delta_time);
}
