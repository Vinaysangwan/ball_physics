#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <random>

template <typename T>
T get_Max(const T &a, const T &b)
{
    return (a > b) ? a : b;
}

template <typename T>
T get_Min(const T &a, const T &b)
{
    return (a < b) ? a : b;
}

extern const unsigned int window_width;
extern const unsigned int window_height;
extern sf::Vector2f mouse_position;