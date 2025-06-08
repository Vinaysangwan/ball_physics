#pragma once

#include "Fonts.h"

class Texts : public sf::Text
{
private: // Private Functions
    void init_Font(const std::string &font_address);
    void init_Text(const std::string &text, const sf::Vector2f &text_pos, const int font_size);

public: // Public Functions
    // Constructor & Destructor
    Texts(const std::string &text, const sf::Vector2f &text_pos, const std::string &font_address = "assets/fonts/Roboto-Regular.ttf", const int font_size = 20);
    ~Texts();

    // Main Texts Functions

    // Return Functions

private: // Private Members
    Fonts *font;
};