#pragma once

#include "../common.h"

class Random
{
public:
    Random();
    ~Random();

    // Return Functions
    int get_RandomInt(const int &min, const int &max);
    float get_RandomFloat(const float &min, const float &max);

private:
    std::random_device rd;
    std::mt19937 gn;
};