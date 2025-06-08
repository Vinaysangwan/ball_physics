#pragma once

#include "Fonts.h"

class Texts : public sf::Text
{
private: // Private Functions
    void init_Font(const std::string &font_address);
    void init_Text(const std::string &text, const sf::Vector2f &text_pos, const int font_size);

public: // Public Functions
    // Constructor & Destructor
    Texts(const std::string &text, const sf::Vector2f &text_pos, const std::string &font_address = "font/Blinky_Star.otf", const int font_size = 20);
    ~Texts();

    // Main Texts Functions
    void stream_StringInt(const std::string &text, const int &num);

private: // Private Members
    Fonts *font;
};