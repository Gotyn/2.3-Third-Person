#ifndef BASEHUD_H
#define BASEHUD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "mge/core/Timer.hpp"

using namespace std;

class BaseHud
{
    public:
        BaseHud(sf::RenderWindow* aWindow);
        virtual ~BaseHud();

        //SFML stuff (buttons, boxes, labels
        static bool Button          (int xOffset, int yOffset, std::string caption);
        static void TextLabel       (int xOffset, int yOffset, std::string caption);  //Adds a label that fits around given text.
        static void ProgressBar     (int xOffset, int yOffset, int row, int alignment, float scaleX, float scaleY);
        static bool HelpButton      (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY);
        static bool HintButton1     (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY);
        static bool HintButton2     (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY);
        static bool HintButton3     (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY);
        static bool ExitButton      (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY);
        static bool ResumeButton    (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY);
        static bool StartButton     (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY);
        static bool StoryBookButton (int xOffset, int yOffset, int spriteID, int alignment, float scaleX, float scaleY);
        static void HelpBox         (int xOffset, int yOffset, int alignment, float scaleX, float scaleY);
        static void RiddleBox       (int xOffset, int yOffset, int fontSize, std::string caption, int alignment, float scaleX, float scaleY);
        static void HintsBox        (int xOffset, int yOffset, int fontSize, std::string caption, int alignment, float scaleX, float scaleY);
        static void MenuBox         (int xOffset, int yOffset, int alignment, float scaleX, float scaleY);
        static void StoryBook       (int xOffset, int yOffset, int alignment, float scaleX, float scaleY);

        static sf::Vector2f fixAlignment(int alignment, int xOffset, int yOffset, int widht = 1, int height = 1);

        static void loadTextures();
        //setters for book texture names
        static void setBookTextureIntroName(const std::string name);
        static void setBookTexture1Name(const std::string name);
        static void setBookTexture2Name(const std::string name);
        static void setBookTexture3Name(const std::string name);
        static void setBookTexture4Name(const std::string name);
        static void setBookTexture5Name(const std::string name);
        static void setBookTexture6Name(const std::string name);
        static void setBookTexture7Name(const std::string name);
        static void setBookTexture8Name(const std::string name);
        static void setBookTexture9Name(const std::string name);
        static void setBookTexture10Name(const std::string name);
        static void setBookTexture11Name(const std::string name);
        static void setBookTextureFinalName(const std::string name);

        //setters
        static void setHelpButtonTextureName(const std::string name);
        static void setHintButton1TextureName(const std::string name);
        static void setHintButton2TextureName(const std::string name);
        static void setHintButton3TextureName(const std::string name);
        static void setExitButtonTextureName(const std::string name);
        static void setResumeButtonTextureName(const std::string name);
        static void setStartButtonTextureName(const std::string name);
        static void setStoryBookButtonTextureName(const std::string name);
        static void setHelpBoxTextureName(const std::string name);
        static void setRiddleBoxTextureName(const std::string name);
        static void setHintsBoxTextureName(const std::string name);
        static void setMenuBoxTextureName(const std::string name);
        static void setStoryBookTextureName(const std::string name);
        static void setProgressbarTextureName(const std::string name);
        static void setDisplayTime(const int value);
        static bool lmbPressedLastFrame; //store if LeftMouseButton was pressed.
        static bool DisplayRiddleAtStart();
        static bool texturesSet;
        static void handleExit();
        void setBookTexture(int index);

    protected:

    private:
        static sf::RenderWindow* _window;
        static sf::Font _font;

        static float startedRiddleDisplay;
        static float displayTime;

        //story book textures
        static sf::Texture* bookTextureIntro;
        static sf::Texture* bookTexture1;
        static sf::Texture* bookTexture2;
        static sf::Texture* bookTexture3;
        static sf::Texture* bookTexture4;
        static sf::Texture* bookTexture5;
        static sf::Texture* bookTexture6;
        static sf::Texture* bookTexture7;
        static sf::Texture* bookTexture8;
        static sf::Texture* bookTexture9;
        static sf::Texture* bookTexture10;
        static sf::Texture* bookTexture11;
        static sf::Texture* bookTextureFinal;
        static std::vector<sf::Texture*> bookTextures;

        //hud textures
        static sf::Texture* helpButtonTexture;
        static sf::Texture* hintButton1Texture;
        static sf::Texture* hintButton2Texture;
        static sf::Texture* hintButton3Texture;
        static sf::Texture* exitButtonTexture;
        static sf::Texture* resumeButtonTexture;
        static sf::Texture* startButtonTexture;
        static sf::Texture* storyBookButtonTexture;
        static sf::Texture* helpBoxTexture;
        static sf::Texture* riddleBoxTexture;
        static sf::Texture* hintsBoxTexture;
        static sf::Texture* progressBarTexture;
        static sf::Texture* menuBoxTexture;
        static sf::Texture* storyBookTexture;
        //hud sprites
        static sf::Sprite* helpButtonSprite;
        static sf::Sprite* hintButton1Sprite;
        static sf::Sprite* hintButton2Sprite;
        static sf::Sprite* hintButton3Sprite;
        static sf::Sprite* exitButtonSprite;
        static sf::Sprite* resumeButtonSprite;
        static sf::Sprite* startButtonSprite;
        static sf::Sprite* storyBookButtonSprite;
        static sf::Sprite* helpBoxSprite;
        static sf::Sprite* riddleBoxSprite;
        static sf::Sprite* hintsBoxSprite;
        static sf::Sprite* progressBarSprite;
        static sf::Sprite* menuBoxSprite;
        static sf::Sprite* storyBookSprite;
        //hud texts
        static sf::Text* riddleBoxText;
        static sf::Text* hintsBoxText;
        //hud names
        static std::string helpButtonTextureName;
        static std::string hintButton1TextureName;
        static std::string hintButton2TextureName;
        static std::string hintButton3TextureName;
        static std::string exitButtonTextureName;
        static std::string resumeButtonTextureName;
        static std::string startButtonTextureName;
        static std::string storyBookButtonTextureName;
        static std::string helpBoxTextureName;
        static std::string riddleBoxTextureName;
        static std::string hintsBoxTextureName;
        static std::string progressBarTextureName;
        static std::string menuBoxTextureName;
        static std::string storyBookTextureName;

        //book texture names
        static std::string bookTextureIntroName;
        static std::string bookTexture1Name;
        static std::string bookTexture2Name;
        static std::string bookTexture3Name;
        static std::string bookTexture4Name;
        static std::string bookTexture5Name;
        static std::string bookTexture6Name;
        static std::string bookTexture7Name;
        static std::string bookTexture8Name;
        static std::string bookTexture9Name;
        static std::string bookTexture10Name;
        static std::string bookTexture11Name;
        static std::string bookTextureFinalName;

        static bool CheckMouseOnButton(sf::Vector2f position, int width, int height);

        // Alignment
        static sf::Vector2u wSize;
        // Alignment on X
        static int Align_X_Left   (int xOffset);
        static int Align_X_Center (int width, int xOffset);
        static int Align_X_Right  (int width, int xOffset);
        // Alignment on Y
        static int Align_Y_Top    (int yOffset);
        static int Align_Y_Center (int height, int yOffset);
        static int Align_Y_Bottom (int height, int yOffset);
        void fillBookTexturesVector();
};

#endif // BASEHUD_H
