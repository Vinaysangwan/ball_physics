#include "Fonts.h"

// #########################################################################
//                           Private Functions
// #########################################################################

// Init Fonts
void Fonts::init_Font(const std::string &font_address)
{
    if (!this->openFromFile(font_address))
    {
        std::cerr << "ERROR::Fonts::init_Font(): Failed to open font from file: " << font_address << std::endl;
        return;
    }

    this->setSmooth(false);
}

// #########################################################################
//                        Constructor & Destructor
// #########################################################################

// Constructor
Fonts::Fonts(const std::string &font_address)
{
    init_Font(font_address);
}

// Destructor
Fonts::~Fonts()
{
}