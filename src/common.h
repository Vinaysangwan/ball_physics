#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <random>

template <typename T>
constexpr const T &get_Max(const T &a, const T &b)
{
    return (a > b) ? a : b;
}

template <typename T>
constexpr const T &get_Min(const T &a, const T &b)
{
    return (a < b) ? a : b;
}

extern const unsigned int window_width;
extern const unsigned int window_height;
extern sf::Vector2f mouse_position;

namespace Collision
{
    bool is_Collision_Circles(const float &r1, const sf::Vector2f &pos1, const float &r2, const sf::Vector2f &pos2);
}