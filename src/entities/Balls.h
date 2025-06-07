#pragma once

#include "Ball.h"
#include "../random/Random.h"

class Balls
{
private:
    void init_Variables();

    void spawn_Ball();
    void despawn_Balls();
    void handle_Collision(const float &delta_time);

public:
    Balls();
    ~Balls();

    void update(const float &delta_time);
    void render(sf::RenderTarget &window);

private:
    // Random
    Random *random;

    std::vector<std::unique_ptr<Ball>> balls;
    int ball_count;
};