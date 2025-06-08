#pragma once

#include "../common.h"
#include "../random/Random.h"

class Ball : public sf::CircleShape
{
private: // Private Functions
    void init_Variables(const sf::Vector2f &position, const sf::Color &color);
    void init_Circle();

    void move_ball(const float &delta_time);
    void window_Collision(const float &delta_time);

public: // Public Functions
    // Constructor & Destructor
    Ball(const sf::Vector2f &position, const sf::Color &color);
    ~Ball();

    // Main Ball Functions
    void update(const float &delta_time);

private: // Private Members
    // Random
    Random *random;

    // Constants
    const float friction_coefficient;

    // Forces
    float gravity;
    float friction;

    // Ball Stats
    sf::Vector2f position;
    float speed;
    sf::Color color;

public: // Public Members
    // Ball Stats
    float radius;
    sf::Vector2f velocity;

    // Constant
    const float restitution;
};