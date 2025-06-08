#include "Balls.h"

void Balls::init_Variables()
{
    // Random
    random = new Random();

    // Ball Count
    ball_count = 0;
}

void Balls::spawn_Ball()
{
    static bool mouse_clicked = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!mouse_clicked)
        {
            Ball ball(mouse_position, sf::Color(random->get_RandomInt(0, 255), random->get_RandomInt(0, 255), random->get_RandomInt(0, 255), 255));
            balls.push_back(std::make_unique<Ball>(ball));
            ball_count++;

            mouse_clicked = true;
        }
    }
    else
    {
        mouse_clicked = false;
    }
}

void Balls::despawn_Balls()
{
    // Despawn all the Balls (C)
    {
        static bool is_c_pressed = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C))
        {
            if (!is_c_pressed)
            {
                balls.clear();
                ball_count = 0;

                is_c_pressed = true;
            }
        }
        else
        {
            is_c_pressed = false;
        }
    }

    // DeSpawn last Ball (Z)
    {
        static bool is_z_pressed = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z))
        {
            if (!is_z_pressed)
            {
                balls.pop_back();
                ball_count--;

                is_z_pressed = true;
            }
        }
        else
        {
            is_z_pressed = false;
        }
    }
}

void Balls::handle_Collision()
{
    for (int i = 0; i < ball_count - 1; i++)
    {
        for (int j = i + 1; j < ball_count; j++)
        {
            Ball *A = balls[i].get();
            Ball *B = balls[j].get();

            sf::Vector2f displacement = A->getPosition() - B->getPosition();
            float distance_squared = displacement.x * displacement.x + displacement.y * displacement.y;
            float min_distance = A->radius + B->radius;

            // If Colliding
            if (distance_squared < min_distance * min_distance)
            {
                float distance = std::sqrt(distance_squared);
                float inv_distance = (distance_squared != 0) ? 1.0f / distance : 1.0f;
                sf::Vector2f normal = displacement * inv_distance;

                // Set there position
                float overlap = (min_distance - distance) * 0.5f;
                sf::Vector2f overlap_direction = normal * overlap;

                A->setPosition(A->getPosition() + overlap_direction);
                B->setPosition(B->getPosition() - overlap_direction);

                sf::Vector2f rel_velocity = A->velocity - B->velocity;
                float rel_velocity_along_normal = normal.x * rel_velocity.x + normal.y * rel_velocity.y;

                // If moving in same direction
                if (rel_velocity_along_normal > 0.0f)
                {
                    continue;
                }

                float restitution = get_Min(A->restitution, B->restitution);
                float vel = -(1 + restitution) * rel_velocity_along_normal;
                vel /= 2.0f; // Both have same mass
                sf::Vector2f vel_along_normal = normal * vel;

                A->velocity += vel_along_normal;
                B->velocity -= vel_along_normal;
            }
        }
    }
}

Balls::Balls()
{
    init_Variables();
}

Balls::~Balls()
{
    delete random;
}

void Balls::update(const float &delta_time)
{
    spawn_Ball();

    // Update Balls
    if (ball_count > 0)
    {
        for (const auto &i : balls)
        {
            i->update(delta_time);
        }

        handle_Collision();
    }

    despawn_Balls();
}

void Balls::render(sf::RenderTarget &window)
{
    // Render Balls
    if (ball_count > 0)
    {
        for (const auto &i : balls)
        {
            window.draw(*i);
        }
    }
}