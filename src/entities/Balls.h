#pragma once

#include <unordered_map>
#include <utility>

#include "Ball.h"
#include "../components/Texts.h"

struct PairHash
{
    std::size_t operator()(const std::pair<int, int> &p) const
    {
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second << 1));
    }
};

class Balls
{
private:
    void init_Variables();

    void spawn_Ball();
    void despawn_Balls();

    void find_neighbour();
    void handle_Collision(Ball *A, Ball *B);

public:
    Balls();
    ~Balls();

    void update(const float &delta_time);
    void render(sf::RenderTarget &window);

private:
    // Random
    Random *random;

    // Text
    Texts *ball_count_text;

    // Ball
    std::vector<std::unique_ptr<Ball>> balls;
    int ball_count;

    int cell_size;
};