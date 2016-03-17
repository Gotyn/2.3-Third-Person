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
// initialize static book textures
sf::Texture* BaseHud::bookTextureIntro = new sf::Texture;
sf::Texture* BaseHud::bookTexture1 = new sf::Texture;
sf::Texture* BaseHud::bookTexture2 = new sf::Texture;
sf::Texture* BaseHud::bookTexture3 = new sf::Texture;
sf::Texture* BaseHud::bookTexture4 = new sf::Texture;
sf::Texture* BaseHud::bookTexture5 = new sf::Texture;
sf::Texture* BaseHud::bookTexture6 = new sf::Texture;
sf::Texture* BaseHud::bookTexture7 = new sf::Texture;
sf::Texture* BaseHud::bookTexture8 = new sf::Texture;
sf::Texture* BaseHud::bookTexture9 = new sf::Texture;
sf::Texture* BaseHud::bookTexture10 = new sf::Texture;
sf::Texture* BaseHud::bookTexture11 = new sf::Texture;
sf::Texture* BaseHud::bookTextureFinal = new sf::Texture;
std::vector<sf::Texture*> BaseHud::bookTextures;

// initialize static textures
sf::Texture* BaseHud::helpButtonTexture = new sf::Texture;
sf::Texture* BaseHud::hintButton1Texture = new sf::Texture;
sf::Texture* BaseHud::hintButton2Texture = new sf::Texture;
sf::Texture* BaseHud::hintButton3Texture = new sf::Texture;
sf::Texture* BaseHud::exitButtonTexture = new sf::Texture;
sf::Texture* BaseHud::resumeButtonTexture = new sf::Texture;
sf::Texture* BaseHud::startButtonTexture = new sf::Texture;
sf::Texture* BaseHud::storyBookButtonTexture = new sf::Texture;
sf::Texture* BaseHud::helpBoxTexture = new sf::Texture;
sf::Texture* BaseHud::riddleBoxTexture = new sf::Texture;
sf::Texture* BaseHud::hintsBoxTexture = new sf::Texture;
sf::Texture* BaseHud::progressBarTexture = new sf::Texture;
sf::Texture* BaseHud::menuBoxTexture = new sf::Texture;
sf::Texture* BaseHud::storyBookTexture = new sf::Texture;
// initialize static sprites
sf::Sprite* BaseHud::helpButtonSprite = new sf::Sprite;
sf::Sprite* BaseHud::hintButton1Sprite = new sf::Sprite;
sf::Sprite* BaseHud::hintButton2Sprite = new sf::Sprite;
sf::Sprite* BaseHud::hintButton3Sprite = new sf::Sprite;
sf::Sprite* BaseHud::exitButtonSprite = new sf::Sprite;
sf::Sprite* BaseHud::resumeButtonSprite = new sf::Sprite;
sf::Sprite* BaseHud::startButtonSprite = new sf::Sprite;
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
std::string BaseHud::helpButtonTextureName  = "land.jpg";
std::string BaseHud::hintButton1TextureName = "land.jpg";
std::string BaseHud::hintButton2TextureName = "land.jpg";
std::string BaseHud::hintButton3TextureName = "land.jpg";
std::string BaseHud::exitButtonTextureName = "land.jpg";
std::string BaseHud::resumeButtonTextureName = "land.jpg";
std::string BaseHud::startButtonTextureName = "land.jpg";
std::string BaseHud::storyBookButtonTextureName = "land.jpg";
std::string BaseHud::helpBoxTextureName = "land.jpg";
std::string BaseHud::riddleBoxTextureName = "land.jpg";
std::string BaseHud::hintsBoxTextureName = "land.jpg";
std::string BaseHud::progressBarTextureName = "land.jpg";
std::string BaseHud::menuBoxTextureName = "land.jpg";
std::string BaseHud::storyBookTextureName = "land.jpg";

// initialize static names for book
std::string BaseHud::bookTextureIntroName = "land.jpg";
std::string BaseHud::bookTexture1Name = "land.jpg";
std::string BaseHud::bookTexture2Name = "land.jpg";
std::string BaseHud::bookTexture3Name = "land.jpg";
std::string BaseHud::bookTexture4Name = "land.jpg";
std::string BaseHud::bookTexture5Name = "land.jpg";
std::string BaseHud::bookTexture6Name = "land.jpg";
std::string BaseHud::bookTexture7Name = "land.jpg";
std::string BaseHud::bookTexture8Name = "land.jpg";
std::string BaseHud::bookTexture9Name = "land.jpg";
std::string BaseHud::bookTexture10Name = "land.jpg";
std::string BaseHud::bookTexture11Name = "land.jpg";
std::string BaseHud::bookTextureFinalName = "land.jpg";

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
    fillBookTexturesVector();
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

    if (!helpButtonTexture->loadFromFile (config::MGE_SPRITE_PATH + helpButtonTextureName))
        { std::cout << "Could not load texture for button"           << std::endl; return; }
    if (!hintButton1Texture->loadFromFile(config::MGE_SPRITE_PATH + hintButton1TextureName))
        { std::cout << "Could not load texture for button"           << std::endl; return; }
    if (!hintButton2Texture->loadFromFile(config::MGE_SPRITE_PATH + hintButton2TextureName))
        { std::cout << "Could not load texture for button"           << std::endl; return; }
    if (!hintButton3Texture->loadFromFile(config::MGE_SPRITE_PATH + hintButton3TextureName))
        { std::cout << "Could not load texture for button"           << std::endl; return; }
    if (!exitButtonTexture->loadFromFile(config::MGE_SPRITE_PATH + exitButtonTextureName))
        { std::cout << "Could not load texture for exit button"      << std::endl; return; }
    if (!resumeButtonTexture->loadFromFile(config::MGE_SPRITE_PATH + resumeButtonTextureName))
        { std::cout << "Could not load texture for resume button"    << std::endl; return; }
    if (!startButtonTexture->loadFromFile(config::MGE_SPRITE_PATH + startButtonTextureName))
        { std::cout << "Could not load texture for start button"     << std::endl; return; }
    if (!storyBookButtonTexture->loadFromFile(config::MGE_SPRITE_PATH + storyBookButtonTextureName))
        { std::cout << "Could not load texture for storybook button" << std::endl; return; }
    if (!helpBoxTexture->loadFromFile    (config::MGE_SPRITE_PATH + helpBoxTextureName))
        { std::cout << "Could not load texture for label"            << std::endl; return; }
    if (!riddleBoxTexture->loadFromFile  (config::MGE_SPRITE_PATH + riddleBoxTextureName))
        { std::cout << "Could not load texture for label"            << std::endl; return; }
    if (!hintsBoxTexture->loadFromFile   (config::MGE_SPRITE_PATH + hintsBoxTextureName))
        { std::cout << "Could not load texture for label"            << std::endl; return; }
    if (!menuBoxTexture->loadFromFile    (config::MGE_SPRITE_PATH + menuBoxTextureName))
        { std::cout << "Could not load texture for menulabel"        << std::endl; return; }
    if (!storyBookTexture->loadFromFile(config::MGE_SPRITE_PATH + storyBookTextureName))
        { std::cout << "Could not load texture for storybook label"  << std::endl; return; }
    if (!progressBarTexture->loadFromFile(config::MGE_SPRITE_PATH + progressBarTextureName))
        { std::cout << "Could not load texture for label"            << std::endl; return; }
    if (!bookTextureIntro->loadFromFile(config::MGE_SPRITE_PATH + bookTextureIntroName))
        { std::cout << "Could not load texture for book texture intro"  << std::endl; return; }
    if (!bookTexture1->loadFromFile(config::MGE_SPRITE_PATH + bookTexture1Name))
        { std::cout << "Could not load texture for book texture 1"  << std::endl; return; }
    if (!bookTexture2->loadFromFile(config::MGE_SPRITE_PATH + bookTexture2Name))
        { std::cout << "Could not load texture for book texture 2"  << std::endl; return; }
    if (!bookTexture3->loadFromFile(config::MGE_SPRITE_PATH + bookTexture3Name))
        { std::cout << "Could not load texture for book texture 3"  << std::endl; return; }
    if (!bookTexture4->loadFromFile(config::MGE_SPRITE_PATH + bookTexture4Name))
        { std::cout << "Could not load texture for book texture 4"  << std::endl; return; }
    if (!bookTexture5->loadFromFile(config::MGE_SPRITE_PATH + bookTexture5Name))
        { std::cout << "Could not load texture for book texture 5"  << std::endl; return; }
    if (!bookTexture6->loadFromFile(config::MGE_SPRITE_PATH + bookTexture6Name))
        { std::cout << "Could not load texture for book texture 6"  << std::endl; return; }
    if (!bookTexture7->loadFromFile(config::MGE_SPRITE_PATH + bookTexture7Name))
        { std::cout << "Could not load texture for book texture 7"  << std::endl; return; }
    if (!bookTexture8->loadFromFile(config::MGE_SPRITE_PATH + bookTexture8Name))
        { std::cout << "Could not load texture for book texture 8"  << std::endl; return; }
    if (!bookTexture9->loadFromFile(config::MGE_SPRITE_PATH + bookTexture9Name))
        { std::cout << "Could not load texture for book texture 9"  << std::endl; return; }
    if (!bookTexture10->loadFromFile(config::MGE_SPRITE_PATH + bookTexture10Name))
        { std::cout << "Could not load texture for book texture 10"  << std::endl; return; }
    if (!bookTexture11->loadFromFile(config::MGE_SPRITE_PATH + bookTexture11Name))
        { std::cout << "Could not load texture for book texture 11"  << std::endl; return; }
    if (!bookTextureFinal->loadFromFile(config::MGE_SPRITE_PATH + bookTextureFinalName))
        { std::cout << "Could not load texture for book texture final"  << std::endl; return; }



    helpButtonTexture->setRepeated(true);
    hintButton1Texture->setRepeated(true);
    hintButton2Texture->setRepeated(true);
    hintButton3Texture->setRepeated(true);
    exitButtonTexture->setRepeated(true);
    resumeButtonTexture->setRepeated(true);
    startButtonTexture->setRepeated(true);
    storyBookButtonTexture->setRepeated(true);
    helpBoxTexture->setRepeated(true);
    riddleBoxTexture->setRepeated(true);
    hintsBoxTexture->setRepeated(true);
    menuBoxTexture->setRepeated(true);
    storyBookTexture->setRepeated(true);
    bookTextureIntro->setSmooth(true);
    bookTexture1->setSmooth(true);
    bookTexture2->setSmooth(true);
    bookTexture3->setSmooth(true);
    bookTexture4->setSmooth(true);
    bookTexture5->setSmooth(true);
    bookTexture6->setSmooth(true);
    bookTexture7->setSmooth(true);
    bookTexture8->setSmooth(true);
    bookTexture9->setSmooth(true);
    bookTexture10->setSmooth(true);
    bookTexture11->setSmooth(true);
    bookTextureFinal->setSmooth(true);
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
bool BaseHud::HelpButton(int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY) {
    int spriteSheetColumns = 2;

    sf::Vector2u spriteSize(helpButtonTexture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX / spriteSheetColumns;
    int scaledSpriteHeight = spriteSize.y * scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);
    int tileWidth = ( spriteSize.x / spriteSheetColumns );                                              // unscaled!

    //create sprite
    helpButtonSprite->setTexture(*helpButtonTexture);
    helpButtonSprite->setScale(scaleX, scaleY);
    if (spriteID == 0) helpButtonSprite->setTextureRect(sf::IntRect(0, 0, tileWidth, spriteSize.y));    // unscaled!
    else helpButtonSprite->setTextureRect(sf::IntRect(tileWidth, 0, tileWidth, spriteSize.y));          // unscaled!

    helpButtonSprite->setPosition(alignedPos);

    _window->draw(*helpButtonSprite);

    return CheckMouseOnButton(alignedPos, scaledSpriteWidth, scaledSpriteHeight); //check for mouseclick
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::HintButton1(int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY) {
    int spriteSheetColumns = 2;

    sf::Vector2u spriteSize(hintButton1Texture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX / spriteSheetColumns;
    int scaledSpriteHeight = spriteSize.y * scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);
    int tileWidth = ( spriteSize.x / spriteSheetColumns );                                              //unscaled!

    //create sprite
    hintButton1Sprite->setTexture(*hintButton1Texture);
    hintButton1Sprite->setScale(scaleX, scaleY);
    if (spriteID == 0) hintButton1Sprite->setTextureRect(sf::IntRect(0, 0, tileWidth, spriteSize.y));   //unscaled!
    else hintButton1Sprite->setTextureRect(sf::IntRect(tileWidth, 0, tileWidth, spriteSize.y));         //unscaled!
    hintButton1Sprite->setPosition(alignedPos);

    _window->draw(*hintButton1Sprite);

    return CheckMouseOnButton(alignedPos, scaledSpriteWidth, scaledSpriteHeight); //check for mouseclick
}


//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::HintButton2(int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY) {
    int spriteSheetColumns = 2;

    sf::Vector2u spriteSize(hintButton2Texture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX / spriteSheetColumns;
    int scaledSpriteHeight = spriteSize.y * scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);
    int tileWidth = ( spriteSize.x / spriteSheetColumns );                                              //unscaled!

    //create sprite
    hintButton2Sprite->setTexture(*hintButton2Texture);
    hintButton2Sprite->setScale(scaleX, scaleY);
    if (spriteID == 0) hintButton2Sprite->setTextureRect(sf::IntRect(0, 0, tileWidth, spriteSize.y));   //unscaled!
    else hintButton2Sprite->setTextureRect(sf::IntRect(tileWidth, 0, tileWidth, spriteSize.y));         //unscaled!
    hintButton2Sprite->setPosition(alignedPos);

    _window->draw(*hintButton2Sprite);

    return CheckMouseOnButton(alignedPos, scaledSpriteWidth, scaledSpriteHeight); //check for mouseclick
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::HintButton3(int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY) {
    int spriteSheetColumns = 2;

    sf::Vector2u spriteSize(hintButton3Texture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX / spriteSheetColumns;
    int scaledSpriteHeight = spriteSize.y * scaleY;

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);
    int tileWidth = ( spriteSize.x / spriteSheetColumns );                                              //unscaled!

    //create sprite
    hintButton3Sprite->setTexture(*hintButton3Texture);
    hintButton3Sprite->setScale(scaleX, scaleY);
    if (spriteID == 0) hintButton3Sprite->setTextureRect(sf::IntRect(0, 0, tileWidth, spriteSize.y));   //unscaled!
    else hintButton3Sprite->setTextureRect(sf::IntRect(tileWidth, 0, tileWidth, spriteSize.y));         //unscaled!
    hintButton3Sprite->setPosition(alignedPos);

    _window->draw(*hintButton3Sprite);

    return CheckMouseOnButton(alignedPos, scaledSpriteWidth, scaledSpriteHeight); //check for mouseclick
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::ExitButton  (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY) {
    int spriteSheetColumns = 2;

    sf::Vector2u spriteSize(exitButtonTexture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX / spriteSheetColumns;
    int scaledSpriteHeight = spriteSize.y * scaleY;
    int tileWidth = ( spriteSize.x / spriteSheetColumns );                               //unscaled!

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);

    //create sprite
    exitButtonSprite->setTexture(*exitButtonTexture);
    exitButtonSprite->setScale(scaleX, scaleY);
    if (spriteID == 0) exitButtonSprite->setTextureRect(sf::IntRect(0,0,tileWidth,spriteSize.y));
    else exitButtonSprite->setTextureRect(sf::IntRect(tileWidth,0,tileWidth,spriteSize.y));
    exitButtonSprite->setPosition(alignedPos);

    _window->draw(*exitButtonSprite);

    return CheckMouseOnButton(alignedPos, scaledSpriteWidth, scaledSpriteHeight); //check for mouseclick
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::ResumeButton(int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY)
{
    int spriteSheetColumns = 2;

    sf::Vector2u spriteSize(resumeButtonTexture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX / spriteSheetColumns;
    int scaledSpriteHeight = spriteSize.y * scaleY;
    int tileWidth = ( spriteSize.x / spriteSheetColumns );                               //unscaled!

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);

    //create sprite
    resumeButtonSprite->setTexture(*resumeButtonTexture);
    resumeButtonSprite->setScale(scaleX, scaleY);
    if (spriteID == 0) resumeButtonSprite->setTextureRect(sf::IntRect(0,0,tileWidth,spriteSize.y));
    else resumeButtonSprite->setTextureRect(sf::IntRect(tileWidth,0,tileWidth,spriteSize.y));
    resumeButtonSprite->setPosition(alignedPos);

    _window->draw(*resumeButtonSprite);

    return CheckMouseOnButton(alignedPos, scaledSpriteWidth, scaledSpriteHeight); //check for mouseclick
}

//----------------------------------------------------------------
// image/sprite SFML button, triggers action upon click
//----------------------------------------------------------------
bool BaseHud::StartButton (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY)
{
    int spriteSheetColumns = 2;

    sf::Vector2u spriteSize(startButtonTexture->getSize());                              // Get the image size
    int scaledSpriteWidth = spriteSize.x * scaleX / spriteSheetColumns;
    int scaledSpriteHeight = spriteSize.y * scaleY;
    int tileWidth = ( spriteSize.x / spriteSheetColumns );                               //unscaled!

    sf::Vector2f alignedPos = fixAlignment(alignment, xOffset, yOffset, scaledSpriteWidth, scaledSpriteHeight);

    //create sprite
    startButtonSprite->setTexture(*startButtonTexture);
    startButtonSprite->setScale(scaleX, scaleY);
    if (spriteID == 0) startButtonSprite->setTextureRect(sf::IntRect(0,0,tileWidth,spriteSize.y));
    else startButtonSprite->setTextureRect(sf::IntRect(tileWidth,0,tileWidth,spriteSize.y));
    startButtonSprite->setPosition(alignedPos);

    _window->draw(*startButtonSprite);

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
    riddleBoxText->setPosition(alignedPos.x + scaledSpriteWidth / 2, alignedPos.y + scaledSpriteHeight / 2 + 20);
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
    hintsBoxText->setPosition(alignedPos.x + scaledSpriteWidth / 2, alignedPos.y + scaledSpriteHeight / 2 + 20);
    hintsBoxText->setString(caption);
    hintsBoxText->setFont(_font);
    hintsBoxText->setCharacterSize(fontSize);
    hintsBoxText->setColor(sf::Color::White);

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
void BaseHud::setHelpButtonTextureName(const std::string name)      { helpButtonTextureName      = name;  }
void BaseHud::setHintButton1TextureName(const std::string name)     { hintButton1TextureName     = name;  }
void BaseHud::setHintButton2TextureName(const std::string name)     { hintButton2TextureName     = name;  }
void BaseHud::setHintButton3TextureName(const std::string name)     { hintButton3TextureName     = name;  }
void BaseHud::setHelpBoxTextureName(const std::string name)         { helpBoxTextureName         = name;  }
void BaseHud::setRiddleBoxTextureName(const std::string name)       { riddleBoxTextureName       = name;  }
void BaseHud::setHintsBoxTextureName(const std::string name)        { hintsBoxTextureName        = name;  }
void BaseHud::setMenuBoxTextureName(const std::string name)         { menuBoxTextureName         = name;  }
void BaseHud::setStoryBookTextureName(const std::string name)       { storyBookTextureName       = name;  }
void BaseHud::setProgressbarTextureName(const std::string name)     { progressBarTextureName     = name;  }
void BaseHud::setDisplayTime(const int value)                       { displayTime                = value; }
void BaseHud::setExitButtonTextureName(const std::string name)      { exitButtonTextureName      = name;  }
void BaseHud::setResumeButtonTextureName(const std::string name)    { resumeButtonTextureName    = name;  }
void BaseHud::setStartButtonTextureName(const std::string name)     { startButtonTextureName     = name;  }
void BaseHud::setStoryBookButtonTextureName(const std::string name) { storyBookButtonTextureName = name;  }

void BaseHud::setBookTextureIntroName(const std::string name)       { bookTextureIntroName       = name;  }
void BaseHud::setBookTexture1Name(const std::string name)           { bookTexture1Name           = name;  }
void BaseHud::setBookTexture2Name(const std::string name)           { bookTexture2Name           = name;  }
void BaseHud::setBookTexture3Name(const std::string name)           { bookTexture4Name           = name;  }
void BaseHud::setBookTexture4Name(const std::string name)           { bookTexture4Name           = name;  }
void BaseHud::setBookTexture5Name(const std::string name)           { bookTexture5Name           = name;  }
void BaseHud::setBookTexture6Name(const std::string name)           { bookTexture6Name           = name;  }
void BaseHud::setBookTexture7Name(const std::string name)           { bookTexture7Name           = name;  }
void BaseHud::setBookTexture8Name(const std::string name)           { bookTexture8Name           = name;  }
void BaseHud::setBookTexture9Name(const std::string name)           { bookTexture9Name           = name;  }
void BaseHud::setBookTexture10Name(const std::string name)          { bookTexture10Name          = name;  }
void BaseHud::setBookTexture11Name(const std::string name)          { bookTexture11Name          = name;  }
void BaseHud::setBookTextureFinalName(const std::string name)       { bookTextureFinalName       = name;  }

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

void BaseHud::setBookTexture(int index)
{
    storyBookTexture = bookTextures[index];
}

void BaseHud::fillBookTexturesVector()
{
    bookTextures.push_back(bookTextureIntro);
    bookTextures.push_back(bookTexture1);
    bookTextures.push_back(bookTexture2);
    bookTextures.push_back(bookTexture3);
    bookTextures.push_back(bookTexture4);
    bookTextures.push_back(bookTexture5);
    bookTextures.push_back(bookTexture6);
    bookTextures.push_back(bookTexture7);
    bookTextures.push_back(bookTexture8);
    bookTextures.push_back(bookTexture9);
    bookTextures.push_back(bookTexture10);
    bookTextures.push_back(bookTexture11);
    bookTextures.push_back(bookTextureFinal);
}
