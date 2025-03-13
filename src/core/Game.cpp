#include "Game.hpp"

//*********************************************************************
//********************** Private Game Functions ***********************
//*********************************************************************

// Initializing Variables
void Game::initVariables()
{
    // Window Variables
    {
        this->video_mode.size.x = 800; // Width
        this->video_mode.size.y = 600; // Height
    }

    // Clock
    this->game_clock = new sf::Clock();

    // Time
    this->delta_time = 0.0f;
}

// Initializing Window
void Game::initWindow()
{
    // Init the window
    this->window = new sf::RenderWindow(this->video_mode, "Ball Bounce", sf::Style::Close | sf::Style::Titlebar);

    // Window Position
    this->window->setPosition(sf::Vector2i{this->window->getPosition().x, 50});

    // FrameRate
    this->window->setFramerateLimit(60);
}

// Initializing Fonts
void Game::initFont()
{
    this->font_blinky_star = new sf::Font();
    if (!this->font_blinky_star->openFromFile("./font/Blinky_Star.otf"))
    {
        std::cout << "Error loading the font" << std::endl;
    }
}

// Initializing Text
void Game::initText()
{
    // FPS Text
    this->text_fps = new sf::Text(*this->font_blinky_star);
    this->text_fps->setCharacterSize(24);
    this->text_fps->setFillColor(sf::Color(255, 0, 0));
    this->text_fps->setPosition(sf::Vector2f{10.0f, 10.0f});
    this->text_fps->setString(sf::String("FPS: 60"));
}

// Initializing Ball
void Game::initBall()
{
    Ball ball(this->window);
    this->balls.push_back(ball);
}

// Updating the FPS text
void Game::updateFpsText()
{
    // FPS Text
    int Fps = static_cast<int>((1 / delta_time) * 100);

    std::string s_fps = std::to_string(static_cast<float>(Fps) / 100.0f);

    std::string display_string = "FPS: " + s_fps;

    this->text_fps->setString(display_string);
}

void Game::spawnBalls()
{
    static bool mouse_clicked = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->window->hasFocus())
    {
        if (!mouse_clicked)
        {
            this->initBall();
        }
        mouse_clicked = true;
    }
    else
    {
        mouse_clicked = false;
    }
}

//*********************************************************************
//************************* Main Game Functions ***********************
//*********************************************************************

// Constructor
Game::Game()
{
    this->initVariables(); // Init Variables
    this->initWindow();    // Init Window

    this->initFont(); // Init Fonts
    this->initText(); // Init Text
}

// Destructor
Game::~Game()
{

    delete this->text_fps;
    delete this->font_blinky_star;

    delete this->window;
}

// Assessor
bool Game::running() const
{
    if (this->window->isOpen())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Game Poll Event
void Game::pollEvent()
{
    // Poll Event
    {
        while (std::optional event = this->window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
                break;
            }

            if (const auto *key_pressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (key_pressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    this->window->close();
                    break;
                }
            }
        }
    }
}

// Update Function
void Game::update()
{
    // Calcutating Delta Time
    this->delta_time = game_clock->restart().asSeconds();
    this->pollEvent();

    this->spawnBalls();

    for (Ball i : this->balls)
    {
        i.updateBall(this->delta_time);
    }

    this->updateFpsText();
}

// Render Function
void Game::render()
{
    // Set Window Color
    this->window->clear(sf::Color(86, 86, 86));

    // Draw or Render On the Window
    this->window->draw(*this->text_fps);

    for (Ball i : this->balls)
    {
        i.renderBall(this->window);
    }

    this->window->display();
}
