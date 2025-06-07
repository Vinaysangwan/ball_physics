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

                is_z_pressed = true;
            }
        }
        else
        {
            is_z_pressed = false;
        }
    }
}

void Balls::handle_Collision(const float &delta_time)
{
    for (int i = 0; i < ball_count - 1; i++)
    {
        for (int j = i + 1; j < ball_count; j++)
        {
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
    }

    // handle_Collision(delta_time);

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