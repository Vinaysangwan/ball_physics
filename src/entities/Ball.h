#pragma once

#include "../common.h"
#include "../random/Random.h"

class Ball : public sf::CircleShape
{
private:
    void init_Variables(const sf::Vector2f &position, const sf::Color &color);
    void init_Circle();

    void move_ball(const float &delta_time);
    void window_Collision(const float &delta_time);

public:
    Ball(const sf::Vector2f &position, const sf::Color &color);
    ~Ball();

    void update(const float &delta_time);

private:
    // Random
    Random *random;

    // Constants
    const float restitution;
    const float friction_coefficient;

    // Forces
    float gravity;
    float friction;

    // Ball Stats
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    sf::Color color;
};