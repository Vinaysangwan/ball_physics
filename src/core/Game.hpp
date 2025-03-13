#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "../common.hpp"
#include "../entities/Ball.hpp"

class Game
{
private:
    // Private Functions
    // Init Functions
    void initVariables(); // Variables
    void initWindow();    // Window
    void initFont();      // Fonts
    void initText();      // text
    void initBall();      // Ball

    // Update Functions
    void updateFpsText(); // Fps Update

    // Spawn Balls
    void spawnBalls();

public:
    // Public Functions
    // Constructors & Destructors
    Game();
    ~Game();

    // Accessor
    bool running() const;

    // Main Game Functions
    void pollEvent();
    void update();
    void render();

private:
    // Private Variables
    // Window
    sf::RenderWindow *window;
    sf::VideoMode video_mode;

    // Timer
    sf::Clock *game_clock;
    float delta_time;

    // Font
    sf::Font *font_blinky_star;

    // Text
    sf::Text *text_fps;

    // Ball
    std::vector<Ball> balls;
};