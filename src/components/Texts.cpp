#include "Texts.h"

// #########################################################################
//                           Private Functions
// #########################################################################

// Init Fonts
void Texts::init_Font(const std::string &font_address)
{
    font = new Fonts(font_address);
    this->setFont(*font);
}

// Init Text
void Texts::init_Text(const std::string &text, const sf::Vector2f &text_pos, const int font_size)
{
    // Text
    this->setString(text);

    // Font size
    this->setCharacterSize(font_size);

    // Position & Origin
    this->setPosition(text_pos);
    this->setOrigin(this->getGlobalBounds().size / 2.0f);
}

// #########################################################################
//                        Constructor & Destructor
// #########################################################################

// Constructor
Texts::Texts(const std::string &text, const sf::Vector2f &text_pos, const std::string &font_address, const int font_size)
    : sf::Text(*font)
{
    init_Font(font_address);
    init_Text(text, text_pos, font_size);
}

// Destructor
Texts::~Texts()
{
    delete font;
}

// #########################################################################
//                           Public Functions
// #########################################################################

// Stream Text (Text + Int)
void Texts::stream_StringInt(const std::string &text, const int &num)
{
    std::stringstream ss;
    ss << text << num;
    this->setString(ss.str());
}
