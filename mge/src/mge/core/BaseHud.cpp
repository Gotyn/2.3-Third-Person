#include <cassert>
#include <iostream>
#include <cstdio>
#include <GL/glew.h>

#include "BaseHud.hpp"
#include "Texture.hpp"
#include <SFML/Graphics/Text.hpp>
#include "mge/config.hpp"

// init static members
sf::RenderWindow* BaseHud::_window = 0;
sf::Font BaseHud::_font;

BaseHud::BaseHud(sf::RenderWindow* aWindow)
{
    _window = aWindow;

    assert (_window != NULL);

    if (!_font.loadFromFile(config::MGE_FONT_PATH+ "arial.ttf")) {
        std::cout << "Could not load font, exiting..." << std::endl;
        return;
    }
}

BaseHud::~BaseHud()
{

}

bool BaseHud::Button(int x, int y, std::string caption)
{
//    std::cout << "button testing" << std::endl;
//    return false;

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


bool BaseHud::InteractiveButton(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName)
{
    //create text
    sf::Text text(caption, _font, fontSize);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x + width/2, y + height/2));
    text.setColor(sf::Color::White);

    sf::Texture texture;
    texture.setRepeated(true);
    if (!texture.loadFromFile(config::MGE_TEXTURE_PATH + imageName + ".jpg"))
    {
        std::cout << "Could not load texture for button" << std::endl;
        return false;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,width,height));
    sprite.setPosition(sf::Vector2f(x, y)); // absolute position

    glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();
    _window->draw(sprite);
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

void BaseHud::RiddleBox(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName)
{
    //create text
    sf::Text text(caption, _font, fontSize);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x + width/2, y + height/2));
    text.setColor(sf::Color::White);

    //sprite
    sf::Texture texture;
    texture.setRepeated(true);
    if (!texture.loadFromFile(config::MGE_TEXTURE_PATH + imageName + ".jpg"))
    {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,width,height));
    sprite.setPosition(sf::Vector2f(x, y)); // absolute position

    glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates(); //console openGL Error here
    _window->draw(sprite);
    _window->draw(text);
    _window->popGLStates();
}

void BaseHud::HintsBox(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName)
{
    //create text
    sf::Text text(caption, _font, fontSize);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x + width/2, y + height/2));
    text.setColor(sf::Color::White);

    //sprite
    sf::Texture texture;
    texture.setRepeated(true);
    if (!texture.loadFromFile(config::MGE_TEXTURE_PATH + imageName + ".jpg"))
    {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,width,height));
    sprite.setPosition(sf::Vector2f(x, y)); // absolute position

    glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates(); //console openGL Error here
    _window->draw(sprite);
    _window->draw(text);
    _window->popGLStates();
}

// todo: remove?
void BaseHud::draw()
{

}
