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

void BaseHud::Label(int x, int y, std::string caption)
{
    //create text
    sf::Text text(caption, _font, 15);
    text.setPosition(x, y);
    text.setOrigin(0, 0);
    text.setColor(sf::Color::White);

    //sprite
//    sf::Sprite* tipSprite;
//    sf::Texture& tex = Texture::load("mge/textures/bricks.jpg");
//    tipSprite->setTexture(tex);

    //get width/height
    int width = text.getLocalBounds().width + 5;
    int height =  text.getLocalBounds().height + 5;

    //create rectangle
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Black);

    glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();
    _window->draw(rect);
    _window->draw(text);
	_window->popGLStates();
}

// todo: remove?
void BaseHud::draw()
{
//    //glDisable( GL_CULL_FACE );
//	glActiveTexture(GL_TEXTURE0);
//    _window->pushGLStates();
//    _window->draw(_debugText);
//	_window->popGLStates();
}
