#pragma once

#include "../common.h"

class Fonts : public sf::Font
{
private: // Private Functions
    void init_Font(const std::string &font_address);

public: // Public Functions
    // Contsructor & Destructor
    Fonts(const std::string &font_address);
    ~Fonts();
};