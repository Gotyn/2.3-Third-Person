#include <cassert>
#include <iostream>
#include <cstdio>
#include <GL/glew.h>

#include "BaseHud.hpp"
#include "Texture.hpp"
#include <SFML/Graphics/Text.hpp>
#include "mge/config.hpp"
#include "mge/core/Timer.hpp"

// init static members
sf::RenderWindow* BaseHud::_window = 0;
sf::Font BaseHud::_font;
// initialize static textures
sf::Texture* BaseHud::riddleButtonTexture = new sf::Texture;
sf::Texture* BaseHud::hintsButtonTexture = new sf::Texture;
sf::Texture* BaseHud::riddleBoxTexture = new sf::Texture;
sf::Texture* BaseHud::hintsBoxTexture = new sf::Texture;
// initialize static sprites
sf::Sprite* BaseHud::riddleButtonSprite = new sf::Sprite;
sf::Sprite* BaseHud::hintsButtonSprite = new sf::Sprite;
sf::Sprite* BaseHud::riddleBoxSprite = new sf::Sprite;
sf::Sprite* BaseHud::hintsBoxSprite = new sf::Sprite;
// initialize static texts
sf::Text* BaseHud::riddleButtonText = new sf::Text;
sf::Text* BaseHud::hintsButtonText = new sf::Text;
sf::Text* BaseHud::riddleBoxText = new sf::Text;
sf::Text* BaseHud::hintsBoxText = new sf::Text;
// initialize static texture names (set default valid file name to avoid errors)
std::string BaseHud::riddleButtonTextureName = "bricks";
std::string BaseHud::hintsButtonTextureName = "land";
std::string BaseHud::riddleBoxTextureName = "bricks";
std::string BaseHud::hintsBoxTextureName = "land";

BaseHud::BaseHud(sf::RenderWindow* aWindow)
{
    _window = aWindow;
    assert (_window != NULL);

    if (!_font.loadFromFile(config::MGE_FONT_PATH+ "arial.ttf")) {
        std::cout << "Could not load font, exiting..." << std::endl;
        return;
    }
    //loadTextures();
}

BaseHud::~BaseHud()
{

}

void BaseHud::loadTextures()
{
    if (!riddleButtonTexture->loadFromFile(config::MGE_TEXTURE_PATH + riddleButtonTextureName + ".jpg"))
    {
        std::cout << "Could not load texture for button" << std::endl;
        return;
    }
    if (!hintsButtonTexture->loadFromFile(config::MGE_TEXTURE_PATH + hintsButtonTextureName + ".jpg"))
    {
        std::cout << "Could not load texture for button" << std::endl;
        return;
    }
    if (!riddleBoxTexture->loadFromFile(config::MGE_TEXTURE_PATH + riddleBoxTextureName + ".jpg"))
    {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }
    if (!hintsBoxTexture->loadFromFile(config::MGE_TEXTURE_PATH + hintsBoxTextureName + ".jpg"))
    {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }
}

bool BaseHud::Button(int x, int y, std::string caption)
{
    //create text
    sf::Text text(caption, _font, 15);
    text.setPosition(x, y);
    text.setOrigin(0, 0);
    text.setColor(sf::Color::White);

    //get width/height
    int width = text.getLocalBounds().width + 5;
    int height =  text.getLocalBounds().height + 5;

    //create rectangle
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Blue);

    glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();
    _window->draw(rect);
    _window->draw(text);
    _window->popGLStates();

    //text mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    if (mousePos.x < x) return false;
    if (mousePos.y < y) return false;
    if (mousePos.x > x + width) return false;
    if (mousePos.y > y + height) return false;

    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool BaseHud::RiddleButton(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName)
{
    //create text
    sf::FloatRect textRect = riddleButtonText->getLocalBounds();
    riddleButtonText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    riddleButtonText->setPosition(sf::Vector2f(x + width/2, y + height/2));
    riddleButtonText->setString(caption);
    riddleButtonText->setFont(_font);
    riddleButtonText->setCharacterSize(fontSize);
    riddleButtonText->setColor(sf::Color::White);

    riddleButtonTexture->setRepeated(true);
    if (!riddleButtonTexture->loadFromFile(config::MGE_TEXTURE_PATH + riddleButtonTextureName + ".jpg"))
    {
        std::cout << "Could not load texture for riddle button" << std::endl;
        return false;
    }

    riddleButtonSprite->setTexture(*riddleButtonTexture);
    riddleButtonSprite->setTextureRect(sf::IntRect(0, 0, width, height));
    riddleButtonSprite->setPosition(sf::Vector2f(x, y)); // absolute position

    _window->draw(*riddleButtonSprite);
    _window->draw(*riddleButtonText);

	//text mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    if (mousePos.x < x) return false;
    if (mousePos.y < y) return false;
    if (mousePos.x > x + width) return false;
    if (mousePos.y > y + height) return false;

    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool BaseHud::HintsButton(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName)
{
    //create text
    sf::FloatRect textRect = hintsButtonText->getLocalBounds();
    hintsButtonText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    hintsButtonText->setPosition(sf::Vector2f(x + width/2, y + height/2));
    hintsButtonText->setString(caption);
    hintsButtonText->setFont(_font);
    hintsButtonText->setCharacterSize(fontSize);
    hintsButtonText->setColor(sf::Color::White);

    hintsButtonTexture->setRepeated(true);
    if (!hintsButtonTexture->loadFromFile(config::MGE_TEXTURE_PATH + hintsButtonTextureName + ".jpg"))
    {
        std::cout << "Could not load texture for hints button" << std::endl;
        return false;
    }

    hintsButtonSprite->setTexture(*hintsButtonTexture);
    hintsButtonSprite->setTextureRect(sf::IntRect(0,0,width,height));
    hintsButtonSprite->setPosition(sf::Vector2f(x, y)); // absolute position

    _window->draw(*hintsButtonSprite);
    _window->draw(*hintsButtonText);

	//text mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    if (mousePos.x < x) return false;
    if (mousePos.y < y) return false;
    if (mousePos.x > x + width) return false;
    if (mousePos.y > y + height) return false;

    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void BaseHud::RiddleBox(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName)
{
    //create text
    sf::FloatRect textRect = riddleBoxText->getLocalBounds();
    riddleBoxText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    riddleBoxText->setPosition(sf::Vector2f(x + width/2, y + height/2));
    riddleBoxText->setString(caption);
    riddleBoxText->setFont(_font);
    riddleBoxText->setCharacterSize(fontSize);
    riddleBoxText->setColor(sf::Color::White);

    //sprite
    riddleBoxTexture->setRepeated(true);
    if (!riddleBoxTexture->loadFromFile(config::MGE_TEXTURE_PATH + riddleBoxTextureName + ".jpg"))
    {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }

    riddleBoxSprite->setTexture(*riddleBoxTexture);
    riddleBoxSprite->setTextureRect(sf::IntRect(0,0,width,height));
    riddleBoxSprite->setPosition(sf::Vector2f(x, y)); // absolute position

    _window->draw(*riddleBoxSprite);
    _window->draw(*riddleBoxText);
}

void BaseHud::HintsBox(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName)
{
    //create text
    sf::FloatRect textRect = hintsBoxText->getLocalBounds();
    hintsBoxText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    hintsBoxText->setPosition(sf::Vector2f(x + width/2, y + height/2));
    hintsBoxText->setString(caption);
    hintsBoxText->setFont(_font);
    hintsBoxText->setCharacterSize(fontSize);
    hintsBoxText->setColor(sf::Color::Black);

    //sprite
    hintsBoxTexture->setRepeated(true);

    if (!hintsBoxTexture->loadFromFile(config::MGE_TEXTURE_PATH + hintsBoxTextureName + ".jpg"))
    {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }

    hintsBoxSprite->setTexture(*hintsBoxTexture);
    hintsBoxSprite->setTextureRect(sf::IntRect(0,0,width,height));
    hintsBoxSprite->setPosition(sf::Vector2f(x, y)); // absolute position

    _window->draw(*hintsBoxSprite);
    _window->draw(*hintsBoxText);
}

// todo: remove?
void BaseHud::draw()
{

}

void BaseHud::setRiddleButtonTextureName(const std::string name)
{
    riddleButtonTextureName = name;
}

void BaseHud::setHintsButtonTextureName(const std::string name)
{
    hintsButtonTextureName = name;
}

void BaseHud::setRiddleBoxTextureName(const std::string name)
{
    riddleBoxTextureName = name;
}

void BaseHud::setHintsBoxTextureName(const std::string name)
{
    hintsBoxTextureName = name;
}
