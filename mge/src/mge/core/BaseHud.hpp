#ifndef BASEHUD_H
#define BASEHUD_H

#include <SFML/Graphics.hpp>
#include <iostream>

class BaseHud
{
    public:
        BaseHud(sf::RenderWindow* aWindow);
        virtual ~BaseHud();

        virtual void draw();
        static bool Button(int x, int y, std::string caption);
        static void TextLabel(int x, int y, std::string caption);  //Adds a label that fits around given text.
        static void Label(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName = "");
        static bool RiddleButton(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName);
        static bool HintsButton(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName);
        static void RiddleBox(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName);
        static void HintsBox(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName);
        static void loadTextures();
        static bool lmbPressedLastFrame; //store if LeftMouseButton was pressed.
    protected:

    private:
        static sf::RenderWindow* _window;
        static sf::Font _font;
        //hud textures
        static sf::Texture* riddleButtonTexture;
        static sf::Texture* hintsButtonTexture;
        static sf::Texture* riddleBoxTexture;
        static sf::Texture* hintsBoxTexture;
        //hud sprites
        static sf::Sprite* riddleButtonSprite;
        static sf::Sprite* hintsButtonSprite;
        static sf::Sprite* riddleBoxSprite;
        static sf::Sprite* hintsBoxSprite;
        //hud texts
        static sf::Text* riddleButtonText;
        static sf::Text* hintsButtonText;
        static sf::Text* riddleBoxText;
        static sf::Text* hintsBoxText;
        //hud names
        static std::string riddleButtonTextureName;
        static std::string hintsButtonTextureName;
        static std::string riddleBoxTextureName;
        static std::string hintsBoxTextureName;


        static bool CheckMouseOnButton(int x, int y, int width, int height);
};

#endif // BASEHUD_H
