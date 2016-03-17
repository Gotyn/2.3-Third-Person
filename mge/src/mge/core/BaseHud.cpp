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
sf::Texture* BaseHud::hintsButtonTexture = new sf::Texture;
sf::Texture* BaseHud::menuButtonTexture = new sf::Texture;
sf::Texture* BaseHud::storyBookButtonTexture = new sf::Texture;
sf::Texture* BaseHud::helpBoxTexture = new sf::Texture;
sf::Texture* BaseHud::riddleBoxTexture = new sf::Texture;
sf::Texture* BaseHud::hintsBoxTexture = new sf::Texture;
sf::Texture* BaseHud::progressBarTexture = new sf::Texture;
sf::Texture* BaseHud::menuBoxTexture = new sf::Texture;
sf::Texture* BaseHud::storyBookTexture = new sf::Texture;
// initialize static sprites
sf::Sprite* BaseHud::hintsButtonSprite = new sf::Sprite;
sf::Sprite* BaseHud::menuButtonSprite = new sf::Sprite; //contains play, exit, restart, resume, empty
sf::Sprite* BaseHud::storyBookButtonSprite = new sf::Sprite;
sf::Sprite* BaseHud::helpBoxSprite = new sf::Sprite;
sf::Sprite* BaseHud::riddleBoxSprite = new sf::Sprite;
sf::Sprite* BaseHud::hintsBoxSprite = new sf::Sprite;
sf::Sprite* BaseHud::progressBarSprite = new sf::Sprite;
sf::Sprite* BaseHud::menuBoxSprite = new sf::Sprite;
sf::Sprite* BaseHud::storyBookSprite = new sf::Sprite;
// initialize static texts
sf::Text* BaseHud::riddleBoxText = new sf::Text;
sf::Text* BaseHud::hintsBoxText = new sf::Text;
// initialize static texture names (set default valid file name to avoid errors)
std::string BaseHud::hintsButtonTextureName  = "land.jpg";
std::string BaseHud::menuButtonTextureName = "land.jpg";
std::string BaseHud::storyBookButtonTextureName = "land.jpg";
std::string BaseHud::helpBoxTextureName = "land.jpg";
std::string BaseHud::riddleBoxTextureName = "land.jpg";
std::string BaseHud::hintsBoxTextureName = "land.jpg";
std::string BaseHud::progressBarTextureName = "land.jpg";
std::string BaseHud::menuBoxTextureName = "land.jpg";
std::string BaseHud::storyBookTextureName = "land.jpg";

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

    if (!hintsButtonTexture->loadFromFile (config::MGE_SPRITE_PATH + hintsButtonTextureName))        return;
    if (!menuButtonTexture->loadFromFile(config::MGE_SPRITE_PATH + menuButtonTextureName))           return;
    if (!storyBookButtonTexture->loadFromFile(config::MGE_SPRITE_PATH + storyBookButtonTextureName)) return;
    if (!helpBoxTexture->loadFromFile    (config::MGE_SPRITE_PATH + helpBoxTextureName))             return;
    if (!riddleBoxTexture->loadFromFile  (config::MGE_SPRITE_PATH + riddleBoxTextureName))           return;
    if (!hintsBoxTexture->loadFromFile   (config::MGE_SPRITE_PATH + hintsBoxTextureName))            return;
    if (!menuBoxTexture->loadFromFile    (config::MGE_SPRITE_PATH + menuBoxTextureName))             return;
    if (!storyBookTexture->loadFromFile(config::MGE_SPRITE_PATH + storyBookTextureName))             return;
    if (!progressBarTexture->loadFromFile(config::MGE_SPRITE_PATH + progressBarTextureName))         return;

    hintsButtonTexture->setSmooth(true);
    menuButtonTexture->setSmooth(true);
    storyBookButtonTexture->setSmooth(true);
    helpBoxTexture->setSmooth(true);
    riddleBoxTexture->setSmooth(true);
    hintsBoxTexture->setSmooth(true);
    menuBoxTexture->setSmooth(true);
    storyBookTexture->setSmooth(true);
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
    return false; //return CheckMouseOnButton(x,y,width,height);
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::HintsButton(int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY) {
    int spriteSheetColumns = 2;
    int spriteSheetRows = 4;

    sf::Vector2u spriteSize(hintsButtonTexture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX / spriteSheetColumns;
    int scaledSpriteHeight = spriteSize.y * scaleY / spriteSheetRows;
    int tileWidth = ( spriteSize.x / spriteSheetColumns );                          //unscaled!
    int tileHeight = spriteSize.y / spriteSheetRows;                                //unscaled!

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);

    //create sprite
    hintsButtonSprite->setTexture(*hintsButtonTexture);
    hintsButtonSprite->setScale(scaleX, scaleY);

    if      (spriteID == 0) hintsButtonSprite->setTextureRect(sf::IntRect(        0,              0, tileWidth, tileHeight)); //R1 C1    //Sphinx
    else if (spriteID == 1) hintsButtonSprite->setTextureRect(sf::IntRect(tileWidth,              0, tileWidth, tileHeight)); //R1 C2    //Sphinx*
    else if (spriteID == 2) hintsButtonSprite->setTextureRect(sf::IntRect(        0, tileHeight * 1, tileWidth, tileHeight)); //R2 C1    //One
    else if (spriteID == 3) hintsButtonSprite->setTextureRect(sf::IntRect(tileWidth, tileHeight * 1, tileWidth, tileHeight)); //R2 C2    //One*
    else if (spriteID == 4) hintsButtonSprite->setTextureRect(sf::IntRect(        0, tileHeight * 2, tileWidth, tileHeight)); //R3 C1    //Two
    else if (spriteID == 5) hintsButtonSprite->setTextureRect(sf::IntRect(tileWidth, tileHeight * 2, tileWidth, tileHeight)); //R3 C2    //Two*
    else if (spriteID == 6) hintsButtonSprite->setTextureRect(sf::IntRect(        0, tileHeight * 3, tileWidth, tileHeight)); //R4 C1    //Three
    else if (spriteID == 7) hintsButtonSprite->setTextureRect(sf::IntRect(tileWidth, tileHeight * 3, tileWidth, tileHeight)); //R5 C2    //Three*

    hintsButtonSprite->setPosition(alignedPos);

    _window->draw(*hintsButtonSprite);

    return CheckMouseOnButton(alignedPos, scaledSpriteWidth, scaledSpriteHeight); //check for mouseclick
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::MenuButton (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY)
{
    int spriteSheetColumns = 2;
    int spriteSheetRows = 5;

    sf::Vector2u spriteSize(menuButtonTexture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX / spriteSheetColumns;
    int scaledSpriteHeight = spriteSize.y * scaleY / spriteSheetRows;
    int tileWidth = ( spriteSize.x / spriteSheetColumns );                          //unscaled!
    int tileHeight = spriteSize.y / spriteSheetRows;                                //unscaled!

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);

    //create sprite
    menuButtonSprite->setTexture(*menuButtonTexture);
    menuButtonSprite->setScale(scaleX, scaleY);

    if      (spriteID == 0) menuButtonSprite->setTextureRect(sf::IntRect(        0,              0, tileWidth, tileHeight)); //R1 C1    //Play
    else if (spriteID == 1) menuButtonSprite->setTextureRect(sf::IntRect(tileWidth,              0, tileWidth, tileHeight)); //R1 C2    //Play*
    else if (spriteID == 2) menuButtonSprite->setTextureRect(sf::IntRect(        0, tileHeight * 1, tileWidth, tileHeight)); //R2 C1    //Exit
    else if (spriteID == 3) menuButtonSprite->setTextureRect(sf::IntRect(tileWidth, tileHeight * 1, tileWidth, tileHeight)); //R2 C2    //Exit*
    else if (spriteID == 4) menuButtonSprite->setTextureRect(sf::IntRect(        0, tileHeight * 2, tileWidth, tileHeight)); //R3 C1    //Restart
    else if (spriteID == 5) menuButtonSprite->setTextureRect(sf::IntRect(tileWidth, tileHeight * 2, tileWidth, tileHeight)); //R3 C2    //Restart*
    else if (spriteID == 6) menuButtonSprite->setTextureRect(sf::IntRect(        0, tileHeight * 3, tileWidth, tileHeight)); //R4 C1    //Resume
    else if (spriteID == 7) menuButtonSprite->setTextureRect(sf::IntRect(tileWidth, tileHeight * 3, tileWidth, tileHeight)); //R4 C2    //Resume*
    else if (spriteID == 8) menuButtonSprite->setTextureRect(sf::IntRect(        0, tileHeight * 4, tileWidth, tileHeight)); //R5 C1    //Empty
    else if (spriteID == 9) menuButtonSprite->setTextureRect(sf::IntRect(tileWidth, tileHeight * 4, tileWidth, tileHeight)); //R5 C2    //Empty*

    menuButtonSprite->setPosition(alignedPos);

    _window->draw(*menuButtonSprite);

    return CheckMouseOnButton(alignedPos, scaledSpriteWidth, scaledSpriteHeight); //check for mouseclick
}



//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::StoryBookButton (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY)
{
    int spriteSheetRows = 2;

    sf::Vector2u spriteSize(storyBookButtonTexture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX;
    int scaledSpriteHeight = spriteSize.y * scaleY / spriteSheetRows;
    int tileHeight = ( spriteSize.y / spriteSheetRows );                               //unscaled!

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);

    //create sprite
    storyBookButtonSprite->setTexture(*storyBookButtonTexture);
    storyBookButtonSprite->setScale(scaleX, scaleY);
    if (spriteID == 0) storyBookButtonSprite->setTextureRect(sf::IntRect(0,0,spriteSize.x,tileHeight));
    else storyBookButtonSprite->setTextureRect(sf::IntRect(0,tileHeight,spriteSize.x,tileHeight));
    storyBookButtonSprite->setPosition(alignedPos);

    _window->draw(*storyBookButtonSprite);

    return CheckMouseOnButton(alignedPos, scaledSpriteWidth, scaledSpriteHeight); //check for mouseclick
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
void BaseHud::HelpBox(int xOffset, int yOffset, int alignment, float scaleX, float scaleY)
{
    sf::Vector2u spriteSize(helpBoxTexture->getSize());                              // Get the image size
    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, spriteSize.x * scaleX, spriteSize.y * scaleY);

    //create sprite
    helpBoxSprite->setTexture(*helpBoxTexture);
    helpBoxSprite->setScale(scaleX, scaleY);
    helpBoxSprite->setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
    helpBoxSprite->setPosition(alignedPos);

    _window->draw(*helpBoxSprite);
}

//----------------------------------------------------------------
//              image/sprite SFML label with text
//----------------------------------------------------------------
void BaseHud::RiddleBox(int xOffset, int yOffset, int fontSize, std::string caption, int alignment, float scaleX, float scaleY)
{
    sf::Vector2u spriteSize(riddleBoxTexture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX;
    int scaledSpriteHeight = spriteSize.y * scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);

    //create sprite
    riddleBoxSprite->setTexture(*riddleBoxTexture);
    riddleBoxSprite->setScale(scaleX, scaleY);
    riddleBoxSprite->setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y)); //unscaled!
    riddleBoxSprite->setPosition(alignedPos);

    //create text
    sf::FloatRect textRect = riddleBoxText->getLocalBounds();
    riddleBoxText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    riddleBoxText->setPosition(alignedPos.x + scaledSpriteWidth / 2, alignedPos.y + scaledSpriteHeight / 2);
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
void BaseHud::HintsBox(int xOffset, int yOffset, int fontSize, std::string caption, int alignment, float scaleX, float scaleY)
{
    sf::Vector2u spriteSize(hintsBoxTexture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX;
    int scaledSpriteHeight = spriteSize.y * scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);

    //create sprite
    hintsBoxSprite->setTexture(*hintsBoxTexture);
    hintsBoxSprite->setScale(scaleX, scaleY);
    hintsBoxSprite->setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y)); //unscaled!
    hintsBoxSprite->setPosition(alignedPos);

    //create text
    sf::FloatRect textRect = hintsBoxText->getLocalBounds();
    hintsBoxText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    hintsBoxText->setPosition(alignedPos.x + scaledSpriteWidth / 2, alignedPos.y + scaledSpriteHeight / 2);
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
void BaseHud::MenuBox(int xOffset, int yOffset, int alignment, float scaleX, float scaleY)
{
    sf::Vector2u spriteSize(menuBoxTexture->getSize());                              // Get the image size
    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, spriteSize.x * scaleX, spriteSize.y * scaleY);

    //create sprite
    menuBoxSprite->setTexture(*menuBoxTexture);
    menuBoxSprite->setScale(scaleX, scaleY);
    menuBoxSprite->setTextureRect(sf::IntRect(0,0,spriteSize.x,spriteSize.y)); //unscaled!
    menuBoxSprite->setPosition(alignedPos);

    _window->draw(*menuBoxSprite);
}

//----------------------------------------------------------------
//              image/sprite SFML label with text
//----------------------------------------------------------------
void BaseHud::StoryBook(int xOffset, int yOffset, int alignment, float scaleX, float scaleY)
{
    sf::Vector2u spriteSize(storyBookTexture->getSize());                              // Get the image size
    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, spriteSize.x * scaleX, spriteSize.y * scaleY);

    //create sprite
    storyBookSprite->setTexture(*storyBookTexture);
    storyBookSprite->setScale(scaleX, scaleY);
    storyBookSprite->setTextureRect(sf::IntRect(0,0,spriteSize.x,spriteSize.y)); //unscaled!
    storyBookSprite->setPosition(alignedPos);

    _window->draw(*storyBookSprite);
}

//----------------------------------------------------------------
// ProgressBar:
// Essentially a label that uses a spritesheet and manipulates
// sprite's position.
// parameter: row --> row on the spritesheet to show
//----------------------------------------------------------------
void BaseHud::ProgressBar(int xOffset, int yOffset, int row, int alignment, float scaleX, float scaleY) {
    sf::Vector2u textureSize(progressBarTexture->getSize());    //get the image size
    int rowHeight = textureSize.y / 8;                          //calculate rowHeight       // 8 = amount of rows

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, textureSize.x * scaleX, rowHeight * scaleY);

    //sprite
    progressBarTexture->setRepeated(false);

    progressBarSprite->setScale(scaleX, scaleY);
    progressBarSprite->setTexture(*progressBarTexture);
    progressBarSprite->setTextureRect(sf::IntRect(0, rowHeight * row, textureSize.x, rowHeight));
    progressBarSprite->setPosition(alignedPos);

    _window->draw(*progressBarSprite);
}

//----------------------------------------------------------------
// regular SFML label with no image just displaying text
// This can be used for ingame debugging, maybe even subtitles(?).
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
void BaseHud::setHintsButtonTextureName(const std::string name)     { hintsButtonTextureName     = name;  }
void BaseHud::setHelpBoxTextureName(const std::string name)         { helpBoxTextureName         = name;  }
void BaseHud::setRiddleBoxTextureName(const std::string name)       { riddleBoxTextureName       = name;  }
void BaseHud::setHintsBoxTextureName(const std::string name)        { hintsBoxTextureName        = name;  }
void BaseHud::setMenuBoxTextureName(const std::string name)         { menuBoxTextureName         = name;  }
void BaseHud::setStoryBookTextureName(const std::string name)       { storyBookTextureName       = name;  }
void BaseHud::setProgressbarTextureName(const std::string name)     { progressBarTextureName     = name;  }
void BaseHud::setDisplayTime(const int value)                       { displayTime                = value; }
void BaseHud::setMenuButtonTextureName(const std::string name)      { menuButtonTextureName      = name;  }
void BaseHud::setStoryBookButtonTextureName(const std::string name) { storyBookButtonTextureName = name;  }

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
bool BaseHud::CheckMouseOnButton(sf::Vector2f buttonPosition, int buttonWidth, int buttonHeight) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    if (mousePos.x < buttonPosition.x) { return false; }
    if (mousePos.y < buttonPosition.y) { return false; }
    if (mousePos.x > buttonPosition.x + buttonWidth) { return false; }
    if (mousePos.y > buttonPosition.y + buttonHeight) { return false; }
    //If this part is reached, we can conclude that the mouse is on the button...

    //GetMouseButtonDown substitute
    if (!lmbPressedLastFrame && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        lmbPressedLastFrame = true;
        return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    }

    //Mouse is not pressed
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

    switch ( alignment ) {                    //X Alignment                    //Y Alignment
        case 1:  correctPosition = sf::Vector2f(Align_X_Left(xOffset)          , Align_Y_Top(yOffset));            break; // LEFT_TOP
        case 2:  correctPosition = sf::Vector2f(Align_X_Left(xOffset)          , Align_Y_Center(height, yOffset)); break; // LEFT_CENTER
        case 3:  correctPosition = sf::Vector2f(Align_X_Left(xOffset)          , Align_Y_Bottom(height, yOffset)); break; // LEFT_BOTTOM
        case 4:  correctPosition = sf::Vector2f(Align_X_Center(width, xOffset) , Align_Y_Top(yOffset));            break; // CENTER_TOP
        case 5:  correctPosition = sf::Vector2f(Align_X_Center(width, xOffset) , Align_Y_Center(height, yOffset)); break; // CENTER_CENTER
        case 6:  correctPosition = sf::Vector2f(Align_X_Center(width, xOffset) , Align_Y_Bottom(height, yOffset)); break; // CENTER_BOTTOM
        case 7:  correctPosition = sf::Vector2f(Align_X_Right(width, xOffset)  , (yOffset));                       break; // RIGHT_TOP
        case 8:  correctPosition = sf::Vector2f(Align_X_Right(width, xOffset)  , Align_Y_Center(height, yOffset)); break; // RIGHT_CENTER
        case 9:  correctPosition = sf::Vector2f(Align_X_Right(width, xOffset)  , Align_Y_Bottom(height, yOffset)); break; // RIGHT_BOTTOM
        default: std::cout << "WARNING: Alignment '" << alignment << "' doesn't exist!" << std::endl;              break; // WARNING
    }
    return correctPosition;
}

//----------------------------------------------------------------------
//              setters used in fixAlignment function
//----------------------------------------------------------------------
// Alignment on X
int BaseHud::Align_X_Left   (int xOffset)            { return xOffset; }
int BaseHud::Align_X_Center (int width, int xOffset) { return (wSize.x / 2 - width / 2 + xOffset);   }
int BaseHud::Align_X_Right  (int width, int xOffset) { return (wSize.x - width - xOffset); }
// Alignment on Y
int BaseHud::Align_Y_Top    (int yOffset)            { return yOffset; }
int BaseHud::Align_Y_Center (int height, int yOffset){ return (wSize.y / 2 - height / 2 + yOffset);   }
int BaseHud::Align_Y_Bottom (int height, int yOffset){ return (wSize.y - height - yOffset); }

void BaseHud::handleExit()
{
    exit(0);
}
