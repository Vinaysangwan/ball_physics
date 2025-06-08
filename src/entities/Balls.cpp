#include "Balls.h"

#include <cmath>

// ###########################################################################
//                            Private Functions
// ###########################################################################

// Init Vairables
void Balls::init_Variables()
{
    // Random
    random = new Random();

    // Ball Count
    ball_count = 0;

    // Ball Count Text
    ball_count_text = new Texts("Balls: 0", sf::Vector2f(window_width / 2.0f, 50.0f));

    // Cell Size
    cell_size = 20.0f;
}

// Spawn Ball
void Balls::spawn_Ball()
{
    // Spawn Once when Mouse Left Click is Pressed
    {
        static bool mouse_clicked = false;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (!mouse_clicked)
            {
                balls.push_back(std::make_unique<Ball>(mouse_position, sf::Color(random->get_RandomInt(0, 255), random->get_RandomInt(0, 255), random->get_RandomInt(0, 255), 255)));
                ball_count++;
                mouse_clicked = true;
            }
        }
        else
        {
            mouse_clicked = false;
        }
    }

    // Spawn Multiple times when Right click is Pressed
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {

            balls.push_back(std::make_unique<Ball>(mouse_position, sf::Color(random->get_RandomInt(0, 255), random->get_RandomInt(0, 255), random->get_RandomInt(0, 255), 255)));
            ball_count++;
        }
    }
}

// Despawn Balls
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

// Find Neighbour
void Balls::find_neighbour()
{
    std::unordered_map<std::pair<int, int>, std::vector<Ball *>, PairHash> grid;

    // Adding Balls inside grid
    for (const auto &i : balls)
    {
        grid[{static_cast<int>(i->getPosition().x / cell_size), static_cast<int>(i->getPosition().y / cell_size)}].push_back(i.get());
    }

    // Collsion for each ball
    for (const auto &ball_ptr : balls)
    {
        Ball *A = ball_ptr.get();

        int cell_y = static_cast<int>(A->getPosition().y / cell_size);
        int cell_x = static_cast<int>(A->getPosition().x / cell_size);

        // Check for 9 neighbours
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                const auto it = grid.find({cell_x + j, cell_y + i});

                // No neighbour is found
                if (it == grid.end())
                {
                    continue;
                }

                // Neighbours are Found
                const std::vector<Ball *> &neighbours = it->second;
                for (const auto &neighbour : neighbours)
                {
                    Ball *B = neighbour;

                    // Same Ball is Found
                    if (A >= B)
                    {
                        continue;
                    }

                    handle_Collision(A, B);
                }
            }
        }
    }
}

// Handle Collision Between 2 Balls (A & B)
void Balls::handle_Collision(Ball *A, Ball *B)
{
    sf::Vector2f displacement = A->getPosition() - B->getPosition();
    float square_distance = (displacement.x * displacement.x + displacement.y * displacement.y);
    float min_distance = A->radius + B->radius;

    // A and B are Colliding
    if (square_distance <= min_distance * min_distance)
    {
        sf::Vector2f normal;
        float distance;

        // If overlapping
        if (square_distance == 0.0f)
        {
            float angle = random->get_RandomFloat(0, 2.0f * 3.1415926f);
            normal = sf::Vector2f{std::cos(angle), std::sin(angle)};
            distance = 0.0f;
        }
        else
        {
            distance = std::sqrt(square_distance);
            normal = displacement / distance;
        }

        // Set A and b Position
        float overlap = (min_distance - distance) * 0.5f; // For Each
        sf::Vector2f correction = normal * overlap;
        A->setPosition(A->getPosition() + correction);
        B->setPosition(B->getPosition() - correction);

        // Checking there velocity direction
        sf::Vector2f rel_velocity = A->velocity - B->velocity;
        float rel_velocity_along_normal = rel_velocity.x * normal.x + rel_velocity.y * normal.y;

        // If moving in same Direction and velocity of A > B
        if (rel_velocity_along_normal > 0.0f)
        {
            return;
        }

        float restitution = get_Min(A->restitution, B->restitution);
        float velocity_after_collision = -(1 + restitution) * rel_velocity_along_normal;
        sf::Vector2f velocity_along_normal = normal * velocity_after_collision;
        velocity_along_normal /= 2.0f; // Since mass of A = mass of B

        // Set the velocity of both A & B
        A->velocity += velocity_along_normal;
        B->velocity -= velocity_along_normal;
    }
}

// ###########################################################################
//                         Constructor & Destructor
// ###########################################################################

// Constructor
Balls::Balls()
{
    init_Variables();
}

// Destructor
Balls::~Balls()
{
    delete random;
}

// ###########################################################################
//                            Main Functions
// ###########################################################################

// Update Function
void Balls::update(const float &delta_time)
{
    spawn_Ball();

    // Update Balls + handle Collision between them
    if (ball_count > 0)
    {
        for (const auto &i : balls)
        {
            i->update(delta_time);
        }

        find_neighbour();
    }

    // Update or Stream Ball Count Text
    ball_count_text->stream_StringInt("Balls: ", ball_count);

    despawn_Balls();
}

// Render Function
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

    window.draw(*ball_count_text);
}