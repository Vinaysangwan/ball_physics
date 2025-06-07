#pragma once

#include "../common.h"
#include "../entities/Balls.h"

class Game
{
private:
    // Private Functions
    // Init Functions
    void initVariables(); // Variables
    void initWindow();    // Window
    void initFont();      // Fonts
    void initText();      // text
    void init_Balls();    // Balls

    // Update Functions
    void updateFpsText(); // Fps Update

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

    // Balls
    Balls *balls;
};