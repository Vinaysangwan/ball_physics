#include "Random.h"

Random::Random()
    : gn(rd())
{
}

Random::~Random()
{
}

int Random::get_RandomInt(const int &min, const int &max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gn);
}

float Random::get_RandomFloat(const float &min, const float &max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gn);
}
