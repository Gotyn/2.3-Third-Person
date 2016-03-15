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
sf::Vector2u BaseHud::wSize(0,0);
// initialize static textures
sf::Texture* BaseHud::helpButtonTexture = new sf::Texture;
sf::Texture* BaseHud::hintButton1Texture = new sf::Texture;
sf::Texture* BaseHud::hintButton2Texture = new sf::Texture;
sf::Texture* BaseHud::hintButton3Texture = new sf::Texture;
sf::Texture* BaseHud::helpBoxTexture = new sf::Texture;
sf::Texture* BaseHud::riddleBoxTexture = new sf::Texture;
sf::Texture* BaseHud::hintsBoxTexture = new sf::Texture;
sf::Texture* BaseHud::progressBarTexture = new sf::Texture;
sf::Texture* BaseHud::menuBoxTexture = new sf::Texture;
// initialize static sprites
sf::Sprite* BaseHud::helpButtonSprite = new sf::Sprite;
sf::Sprite* BaseHud::hintButton1Sprite = new sf::Sprite;
sf::Sprite* BaseHud::hintButton2Sprite = new sf::Sprite;
sf::Sprite* BaseHud::hintButton3Sprite = new sf::Sprite;
sf::Sprite* BaseHud::helpBoxSprite = new sf::Sprite;
sf::Sprite* BaseHud::riddleBoxSprite = new sf::Sprite;
sf::Sprite* BaseHud::hintsBoxSprite = new sf::Sprite;
sf::Sprite* BaseHud::progressBarSprite = new sf::Sprite;
sf::Sprite* BaseHud::menuBoxSprite = new sf::Sprite;
// initialize static texts
sf::Text* BaseHud::riddleBoxText = new sf::Text;
sf::Text* BaseHud::hintsBoxText = new sf::Text;
// initialize static texture names (set default valid file name to avoid errors)
std::string BaseHud::helpButtonTextureName  = "land.jpg";
std::string BaseHud::hintButton1TextureName = "land.jpg";
std::string BaseHud::hintButton2TextureName = "land.jpg";
std::string BaseHud::hintButton3TextureName = "land.jpg";
std::string BaseHud::helpBoxTextureName = "land.jpg";
std::string BaseHud::riddleBoxTextureName = "land.jpg";
std::string BaseHud::hintsBoxTextureName = "land.jpg";
std::string BaseHud::progressBarTextureName = "Progress_256.png";
std::string BaseHud::menuBoxTextureName = "land.jpg";

bool BaseHud::lmbPressedLastFrame = false;
bool BaseHud::texturesSet = false;
float BaseHud::startedRiddleDisplay = 0;
float BaseHud::displayTime = 0.0f;

BaseHud::BaseHud(sf::RenderWindow* aWindow)
{
    _window = aWindow;
    assert (_window != NULL);

    if (!_font.loadFromFile(config::MGE_FONT_PATH+ "arial.ttf")) {
        std::cout << "Could not load font, exiting..." << std::endl;
        return;
    }

    startedRiddleDisplay = Timer::now();
}

BaseHud::~BaseHud()
{

}

//------------------------------------------------------
// caching all textures to not re-upload on the fly
//------------------------------------------------------
void BaseHud::loadTextures()
{
    glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();

    if (!helpButtonTexture->loadFromFile(config::MGE_TEXTURE_PATH + helpButtonTextureName)) {
        std::cout << "Could not load texture for button" << std::endl;
        return;
    }
    if (!hintButton1Texture->loadFromFile(config::MGE_TEXTURE_PATH + hintButton1TextureName)) {
        std::cout << "Could not load texture for button" << std::endl;
        return;
    }
    if (!hintButton2Texture->loadFromFile(config::MGE_TEXTURE_PATH + hintButton2TextureName)) {
        std::cout << "Could not load texture for button" << std::endl;
        return;
    }
    if (!hintButton3Texture->loadFromFile(config::MGE_TEXTURE_PATH + hintButton3TextureName)) {
        std::cout << "Could not load texture for button" << std::endl;
        return;
    }
    if (!helpBoxTexture->loadFromFile(config::MGE_TEXTURE_PATH + helpBoxTextureName)) {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }
    if (!riddleBoxTexture->loadFromFile(config::MGE_TEXTURE_PATH + riddleBoxTextureName)) {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }
    if (!hintsBoxTexture->loadFromFile(config::MGE_TEXTURE_PATH + hintsBoxTextureName)) {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }
    if (!menuBoxTexture->loadFromFile(config::MGE_TEXTURE_PATH + menuBoxTextureName)) {
        std::cout << "Could not load texture for tutorial label" << std::endl;
        return;
    }
    if (!progressBarTexture->loadFromFile(config::MGE_TEXTURE_PATH + progressBarTextureName)) {
        std::cout << "Could not load texture for label" << std::endl;
        return;
    }

    helpButtonTexture->setRepeated(true);
    hintButton1Texture->setRepeated(true);
    hintButton2Texture->setRepeated(true);
    hintButton3Texture->setRepeated(true);
    helpBoxTexture->setRepeated(true);
    riddleBoxTexture->setRepeated(true);
    hintsBoxTexture->setRepeated(true);
    menuBoxTexture->setRepeated(true);
    _window->popGLStates();
}

//----------------------------------------------------------------
// regular SFML button with no image, triggers action upon click
//----------------------------------------------------------------
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

    _window->draw(rect);
    _window->draw(text);

    //text mouse
    std::cout << "Update BaseHud::Button function with Alignment first" << std::endl;
    //return CheckMouseOnButton(x,y,width,height);
    return false;
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::HelpButton(int x, int y, int width, int height, int spriteID, int alignment, float scaleX, float scaleY)
{
    width *= scaleX;
    height *= scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, x, y, width, height);
    int spriteWidth = helpButtonTexture->getSize().x;
    int spriteHeight = helpButtonTexture->getSize().y;
    int tileWidth = ( spriteWidth / 2 );

    //create sprite

    helpButtonSprite->setTexture(*helpButtonTexture);
    helpButtonSprite->setScale(scaleX, scaleY);
    if (spriteID == 0) helpButtonSprite->setTextureRect(sf::IntRect(0, 0, tileWidth, spriteHeight));
    else helpButtonSprite->setTextureRect(sf::IntRect(tileWidth, 0, tileWidth, spriteHeight));

    helpButtonSprite->setPosition(alignedPos);

    _window->draw(*helpButtonSprite);

	//text mouse
    return CheckMouseOnButton(alignedPos, width, height);
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::HintButton1(int x, int y, int width, int height, int spriteID, int alignment, float scaleX, float scaleY)
{
    width *= scaleX;
    height *= scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, x, y, width, height);
    int spriteWidth = hintButton1Texture->getSize().x;
    int spriteHeight = hintButton1Texture->getSize().y;
    int tileWidth = ( spriteWidth / 2 );

    //create sprite
    hintButton1Sprite->setTexture(*hintButton1Texture);
    hintButton1Sprite->setScale(scaleX, scaleY);
    if (spriteID == 0) hintButton1Sprite->setTextureRect(sf::IntRect(0,0,tileWidth,spriteHeight));
    else hintButton1Sprite->setTextureRect(sf::IntRect(tileWidth,0,tileWidth,spriteHeight));
    hintButton1Sprite->setPosition(alignedPos);

    _window->draw(*hintButton1Sprite);

	//text mouse
    return CheckMouseOnButton(alignedPos, width, height);
}


//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::HintButton2(int x, int y, int width, int height, int spriteID, int alignment, float scaleX, float scaleY)
{
    width *= scaleX;
    height *= scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, x, y, width, height);
    int spriteWidth = hintButton2Texture->getSize().x;
    int spriteHeight = hintButton2Texture->getSize().y;
    int tileWidth = ( spriteWidth / 2 );

    //create sprite
    hintButton2Sprite->setTexture(*hintButton2Texture);
    hintButton2Sprite->setScale(scaleX, scaleY);
    if (spriteID == 0) hintButton2Sprite->setTextureRect(sf::IntRect(0,0,tileWidth,spriteHeight));
    else hintButton2Sprite->setTextureRect(sf::IntRect(tileWidth,0,tileWidth,spriteHeight));
    hintButton2Sprite->setPosition(alignedPos);

    _window->draw(*hintButton2Sprite);

	//text mouse
    return CheckMouseOnButton(alignedPos, width, height);
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::HintButton3(int x, int y, int width, int height, int spriteID, int alignment, float scaleX, float scaleY)
{
    width *= scaleX;
    height *= scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, x, y, width, height);
    int spriteWidth = hintButton3Texture->getSize().x;
    int spriteHeight = hintButton3Texture->getSize().y;
    int tileWidth = ( spriteWidth / 2 );

    //create sprite
    hintButton3Sprite->setTexture(*hintButton3Texture);
    hintButton3Sprite->setScale(scaleX, scaleY);
    if (spriteID == 0) hintButton3Sprite->setTextureRect(sf::IntRect(0,0,tileWidth,spriteHeight));
    else hintButton3Sprite->setTextureRect(sf::IntRect(tileWidth,0,tileWidth,spriteHeight));
    hintButton3Sprite->setPosition(alignedPos);

    _window->draw(*hintButton3Sprite);

	//text mouse
    return CheckMouseOnButton(alignedPos, width, height);
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
void BaseHud::HelpBox(int x, int y, int width, int height, int alignment, float scaleX, float scaleY)
{
    sf::Vector2f alignedPos = fixAlignment(alignment, x, y, width * scaleX, height * scaleY);

    //create sprite
    helpBoxSprite->setTexture(*helpBoxTexture);
    helpBoxSprite->setScale(scaleX, scaleY);
    helpBoxSprite->setTextureRect(sf::IntRect(0,0,width,height));
    helpBoxSprite->setPosition(alignedPos);

    _window->draw(*helpBoxSprite);
}

//----------------------------------------------------------------
//              image/sprite SFML label with text
//----------------------------------------------------------------
void BaseHud::RiddleBox(int x, int y, int width, int height, int fontSize, std::string caption, int alignment)
{
    sf::Vector2f alignedPos = fixAlignment(alignment, x, y, width, height);

    //create sprite
    riddleBoxSprite->setTexture(*riddleBoxTexture);
    riddleBoxSprite->setTextureRect(sf::IntRect(0,0,width,height));
    riddleBoxSprite->setPosition(alignedPos);

    //create text
    sf::FloatRect textRect = riddleBoxText->getLocalBounds();
    riddleBoxText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    riddleBoxText->setPosition(alignedPos.x + width / 2, alignedPos.y + height / 2);
    riddleBoxText->setString(caption);
    riddleBoxText->setFont(_font);
    riddleBoxText->setCharacterSize(fontSize);
    riddleBoxText->setColor(sf::Color::White);

    _window->draw(*riddleBoxSprite);
    _window->draw(*riddleBoxText);
}

//----------------------------------------------------------------
//              image/sprite SFML label with text
//----------------------------------------------------------------
void BaseHud::HintsBox(int x, int y, int width, int height, int fontSize, std::string caption, int alignment)
{
    sf::Vector2f alignedPos = fixAlignment(alignment, x, y, width, height);

    //create sprite
    hintsBoxSprite->setTexture(*hintsBoxTexture);
    hintsBoxSprite->setTextureRect(sf::IntRect(0,0,width,height));
    hintsBoxSprite->setPosition(alignedPos);

    //create text
    sf::FloatRect textRect = hintsBoxText->getLocalBounds();
    hintsBoxText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    //hintsBoxText->setPosition(sf::Vector2f(x + width/2, y + height/2));
    hintsBoxText->setPosition(alignedPos.x + width / 2, alignedPos.y + height / 2);
    hintsBoxText->setString(caption);
    hintsBoxText->setFont(_font);
    hintsBoxText->setCharacterSize(fontSize);
    hintsBoxText->setColor(sf::Color::Black);

    _window->draw(*hintsBoxSprite);
    _window->draw(*hintsBoxText);
}

//----------------------------------------------------------------
//              image/sprite SFML label with text
//----------------------------------------------------------------
void BaseHud::MenuBox(int x, int y, int width, int height, int alignment)
{
    sf::Vector2f alignedPos = fixAlignment(alignment, x, y, width, height);

    //create sprite
    menuBoxSprite->setTexture(*menuBoxTexture);
    menuBoxSprite->setTextureRect(sf::IntRect(0,0,width,height));
    menuBoxSprite->setPosition(alignedPos);

    _window->draw(*menuBoxSprite);
}

//----------------------------------------------------------------
// label that uses spritesheet and manipulates sprite's position
//----------------------------------------------------------------
void BaseHud::ProgressBar(int x, int y, int width, int height, int spriteSheetRow, int alignment, float scaleX, float scaleY) {
    sf::Vector2f alignedPos = fixAlignment(alignment, x, y, width, height);

    //sprite
    progressBarTexture->setRepeated(false);

    progressBarSprite->setTexture(*progressBarTexture);
    progressBarSprite->setTextureRect(sf::IntRect(0, spriteSheetRow, width, height));
    progressBarSprite->setPosition(alignedPos);

    _window->draw(*progressBarSprite);
}

//----------------------------------------------------------------
// regular SFML label with no image just displaying text
//----------------------------------------------------------------
void BaseHud::TextLabel(int x, int y, std::string caption) {
    //create text
    sf::Text text(caption, _font, 15);
    text.setPosition(x, y);
    text.setOrigin(0, 0);
    text.setColor(sf::Color::Black);

    //get width/height
    int width = text.getLocalBounds().width + 5;
    int height =  text.getLocalBounds().height + 5;

    //create rectangle
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::White);

    _window->draw(rect);
    _window->draw(text);
}

//--------------------------------------------------------------------------------
// a bunch of sessters used outside the class for setting texture names from lua
//--------------------------------------------------------------------------------
void BaseHud::setHelpButtonTextureName(const std::string name)  { helpButtonTextureName  = name; }
void BaseHud::setHintButton1TextureName(const std::string name) { hintButton1TextureName = name; }
void BaseHud::setHintButton2TextureName(const std::string name) { hintButton2TextureName = name; }
void BaseHud::setHintButton3TextureName(const std::string name) { hintButton3TextureName = name; }
void BaseHud::setHelpBoxTextureName(const std::string name)     { helpBoxTextureName     = name; }
void BaseHud::setRiddleBoxTextureName(const std::string name)   { riddleBoxTextureName   = name; }
void BaseHud::setHintsBoxTextureName(const std::string name)    { hintsBoxTextureName    = name; }
void BaseHud::setMenuBoxTextureName(const std::string name)     { menuBoxTextureName     = name; }
void BaseHud::setDisplayTime(const int value)                   { displayTime            = value;}

//----------------------------------------------------------------------
// simple counter that sends to lua a signal to stop displaying riddle
//----------------------------------------------------------------------
bool BaseHud::DisplayRiddleAtStart() {
    if(Timer::now() - startedRiddleDisplay > displayTime) return true;
    else return false;
}

//----------------------------------------------------------------------
// Checks whether the mouse is on a button or not.
// Includes a custom mouse button down function, that substitutes
// deprecated SFML 1.6 Input.GetMouseButtonDown
//----------------------------------------------------------------------
bool BaseHud::CheckMouseOnButton(sf::Vector2f position, int width, int height) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    if (mousePos.x < position.x) { return false; }
    if (mousePos.y < position.y) { return false; }
    if (mousePos.x > position.x + width) { return false; }
    if (mousePos.y > position.y + height) { return false; }
    //Mouse is on button!

    if (!lmbPressedLastFrame && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        lmbPressedLastFrame = true;
        return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        lmbPressedLastFrame = false;
    }
}

//----------------------------------------------------------------------
// function that handles HUD items alignment on screen to get rid
// of screen dimensions dependancy. Gets alignment from LUA and
// sets offsets for eac HUD item
//----------------------------------------------------------------------
sf::Vector2f BaseHud::fixAlignment(int alignment, int xOffset, int yOffset, int width, int height) {
    sf::Vector2f correctPosition(0,0);
    wSize = _window->getSize();

    switch ( alignment ) {                    //X Alignment                  //Y Alignment
        case 1:  correctPosition = sf::Vector2f(Align_X_Left(xOffset)        , Align_Y_Top(yOffset));            break; // LEFT_TOP
        case 2:  correctPosition = sf::Vector2f(Align_X_Left(xOffset)        , Align_Y_Center(height));          break; // LEFT_CENTER
        case 3:  correctPosition = sf::Vector2f(Align_X_Left(xOffset)        , Align_Y_Bottom(height, yOffset)); break; // LEFT_BOTTOM
        case 4:  correctPosition = sf::Vector2f(Align_X_Center(width)        , Align_Y_Top(yOffset));            break; // CENTER_TOP
        case 5:  correctPosition = sf::Vector2f(Align_X_Center(width)        , Align_Y_Center(height));          break; // CENTER_CENTER
        case 6:  correctPosition = sf::Vector2f(Align_X_Center(width)        , Align_Y_Bottom(height, yOffset)); break; // CENTER_BOTTOM
        case 7:  correctPosition = sf::Vector2f(Align_X_Right(width, xOffset), (yOffset));                       break; // RIGHT_TOP
        case 8:  correctPosition = sf::Vector2f(Align_X_Right(width, xOffset), Align_Y_Center(height));          break; // RIGHT_CENTER
        case 9:  correctPosition = sf::Vector2f(Align_X_Right(width, xOffset), Align_Y_Bottom(height, yOffset)); break; // RIGHT_BOTTOM
        default: std::cout << "WARNING: Alignment '" << alignment << "' doesn't exist!" << std::endl;            break; // WARNING
    }
    return correctPosition;
}

//----------------------------------------------------------------------
//              setters used in fixAlignment function
//----------------------------------------------------------------------
// Alignment on X
int BaseHud::Align_X_Left   (int xOffset)            { return xOffset; }
int BaseHud::Align_X_Center (int width)              { return (wSize.x / 2 - width / 2);   }
int BaseHud::Align_X_Right  (int width, int xOffset) { return (wSize.x - width - xOffset); }
// Alignment on Y
int BaseHud::Align_Y_Top    (int yOffset)            { return yOffset; }
int BaseHud::Align_Y_Center (int height)             { return (wSize.y / 2 - height / 2);   }
int BaseHud::Align_Y_Bottom (int height, int yOffset){ return (wSize.y - height - yOffset); }

