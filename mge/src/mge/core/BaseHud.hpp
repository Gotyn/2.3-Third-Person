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

        //SFML stuff (buttons, boxes, labels
        static bool Button      (int xOffset, int yOffset, std::string caption);
        static void TextLabel   (int xOffset, int yOffset, std::string caption);  //Adds a label that fits around given text.
        static void ProgressBar (int xOffset, int yOffset, int width, int height, int spriteSheetRow, int alignment);
        static bool HelpButton  (int xOffset, int yOffset, int width, int height, int alignment);
        static bool HintButton1 (int xOffset, int yOffset, int width, int height, int alignment);
        static bool HintButton2 (int xOffset, int yOffset, int width, int height, int alignment);
        static bool HintButton3 (int xOffset, int yOffset, int width, int height, int alignment);
        static void HelpBox     (int xOffset, int yOffset, int width, int height, int alignment);
        static void RiddleBox   (int xOffset, int yOffset, int width, int height, int fontSize, std::string caption, int alignment);
        static void HintsBox    (int xOffset, int yOffset, int width, int height, int fontSize, std::string caption, int alignment);
        static void TutorialBox (int xOffset, int yOffset, int width, int height, int fontSize, std::string caption, int alignment);

        static sf::Vector2f fixAlignment(int alignment, int xOffset, int yOffset, int widht = 1, int height = 1);

        static void loadTextures();
        //setters
        static void setHelpButtonTextureName(const std::string name);
        static void setHintButton1TextureName(const std::string name);
        static void setHintButton2TextureName(const std::string name);
        static void setHintButton3TextureName(const std::string name);
        static void setHelpBoxTextureName(const std::string name);
        static void setRiddleBoxTextureName(const std::string name);
        static void setHintsBoxTextureName(const std::string name);
        static void setTutorialBoxTextureName(const std::string name);
        static void setDisplayTime(const int value);
        static bool lmbPressedLastFrame; //store if LeftMouseButton was pressed.
        static bool DisplayRiddleAtStart();
        static bool texturesSet;

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
        static sf::Texture* tutorialBoxTexture;
        //hud sprites
        static sf::Sprite* helpButtonSprite;
        static sf::Sprite* hintButton1Sprite;
        static sf::Sprite* hintButton2Sprite;
        static sf::Sprite* hintButton3Sprite;
        static sf::Sprite* helpBoxSprite;
        static sf::Sprite* riddleBoxSprite;
        static sf::Sprite* hintsBoxSprite;
        static sf::Sprite* progressBarSprite;
        static sf::Sprite* tutorialBoxSprite;
        //hud texts
        static sf::Text* helpButtonText;
        static sf::Text* hintButton1Text;
        static sf::Text* hintButton2Text;
        static sf::Text* hintButton3Text;
        static sf::Text* helpBoxText;
        static sf::Text* riddleBoxText;
        static sf::Text* hintsBoxText;
        static sf::Text* progressBarText;
        static sf::Text* tutorialBoxText;
        //hud names
        static std::string helpButtonTextureName;
        static std::string hintButton1TextureName;
        static std::string hintButton2TextureName;
        static std::string hintButton3TextureName;
        static std::string helpBoxTextureName;
        static std::string riddleBoxTextureName;
        static std::string hintsBoxTextureName;
        static std::string progressBarTextureName;
        static std::string tutorialBoxTextureName;

        static bool CheckMouseOnButton(sf::Vector2f position, int width, int height);

        // Alignment
        static sf::Vector2u wSize;
        // Alignment on X
        static int Align_X_Left   (int xOffset);
        static int Align_X_Center (int width);
        static int Align_X_Right  (int width, int xOffset);
        // Alignment on Y
        static int Align_Y_Top    (int yOffset);
        static int Align_Y_Center (int height);
        static int Align_Y_Bottom (int height, int yOffset);
};

#endif // BASEHUD_H
