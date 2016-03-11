#ifndef BASEHUD_H
#define BASEHUD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "mge/core/Timer.hpp"

class BaseHud
{
    public:
        BaseHud(sf::RenderWindow* aWindow);
        virtual ~BaseHud();

        static bool Button(int x, int y, std::string caption);
        static void TextLabel(int x, int y, std::string caption);  //Adds a label that fits around given text.
        static void ProgressBar(int x, int y, int width, int height, int spriteSheetRow, int fontSize, std::string caption, int alignment);
        static bool HelpButton(int x, int y, int width, int height, int fontSize, std::string caption, int alignment);
        static bool HintButton1(int x, int y, int width, int height, int fontSize, std::string caption, int alignment);
        static bool HintButton2(int x, int y, int width, int height, int fontSize, std::string caption, int alignment);
        static bool HintButton3(int x, int y, int width, int height, int fontSize, std::string caption, int alignment);
        static void HelpBox(int x, int y, int width, int height, int fontSize, std::string caption, int alignment);
        static void RiddleBox(int x, int y, int width, int height, int fontSize, std::string caption, int alignment);
        static void HintsBox(int x, int y, int width, int height, int fontSize, std::string caption, int alignment);

        static void loadTextures();
        static void setHelpButtonTextureName(const std::string name);
        static void setHintButton1TextureName(const std::string name);
        static void setHintButton2TextureName(const std::string name);
        static void setHintButton3TextureName(const std::string name);
        static void setHelpBoxTextureName(const std::string name);
        static void setRiddleBoxTextureName(const std::string name);
        static void setHintsBoxTextureName(const std::string name);
        static bool lmbPressedLastFrame; //store if LeftMouseButton was pressed.
        static bool DisplayRiddleAtStart();
        static sf::Vector2f fixAlignment(int alignment, int xOffset, int yOffset);

    protected:

    private:
        static sf::RenderWindow* _window;
        static sf::Font _font;

        static float startedRiddleDisplay;
        static float displayTime;

        //hud textures
        static sf::Texture* helpButtonTexture;
        static sf::Texture* hintButton1Texture;
        static sf::Texture* hintButton2Texture;
        static sf::Texture* hintButton3Texture;
        static sf::Texture* helpBoxTexture;
        static sf::Texture* riddleBoxTexture;
        static sf::Texture* hintsBoxTexture;
        static sf::Texture* progressBarTexture;
        //hud sprites
        static sf::Sprite* helpButtonSprite;
        static sf::Sprite* hintButton1Sprite;
        static sf::Sprite* hintButton2Sprite;
        static sf::Sprite* hintButton3Sprite;
        static sf::Sprite* helpBoxSprite;
        static sf::Sprite* riddleBoxSprite;
        static sf::Sprite* hintsBoxSprite;
        static sf::Sprite* progressBarSprite;
        //hud texts
        static sf::Text* helpButtonText;
        static sf::Text* hintButton1Text;
        static sf::Text* hintButton2Text;
        static sf::Text* hintButton3Text;
        static sf::Text* helpBoxText;
        static sf::Text* riddleBoxText;
        static sf::Text* hintsBoxText;
        static sf::Text* progressBarText;
        //hud names
        static std::string helpButtonTextureName;
        static std::string hintButton1TextureName;
        static std::string hintButton2TextureName;
        static std::string hintButton3TextureName;
        static std::string helpBoxTextureName;
        static std::string riddleBoxTextureName;
        static std::string hintsBoxTextureName;
        static std::string progressBarTextureName;

        static bool CheckMouseOnButton(int x, int y, int width, int height);
};

#endif // BASEHUD_H
