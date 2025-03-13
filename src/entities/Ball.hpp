#pragma once

#include <iostream>

#include "../common.hpp"

class Ball
{
private:
    // Private Functions
    void initVariables();
    void initBall();

    // Move
    void moveBall();

public:
    // Public Functions

    // Constructor
    Ball(sf::RenderWindow *window);

    // Destructor
    ~Ball();

    // Main Ball Function
    void updateBall(float delta_time);
    void renderBall(sf::RenderWindow *window);

private:
    // Private Members

    // Video Mode
    sf::VideoMode video_mode;

    // Time
    float delta_time;

    // Mouse Position
    sf::Vector2f mouse_pos;

    // Ball
    sf::CircleShape *ball;
    float radius;

    sf::Vector2f speed;
};