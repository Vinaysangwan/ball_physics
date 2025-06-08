#include "common.h"

const unsigned int window_width = 640u;
const unsigned int window_height = 480u;

sf::Vector2f mouse_position = sf::Vector2f(0.0f, 0.0f);

namespace Collision
{
    bool is_Collision_Circles(const float &r1, const sf::Vector2f &pos1, const float &r2, const sf::Vector2f &pos2)
    {
        if (pos1.x + r1 >= pos2.x - r2 && pos1.x - r1 <= pos2.x + r2 && pos1.y + r1 >= pos2.y - r2 && pos1.y - r1 <= pos2.y + r2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}