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
        static bool InteractiveButton(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName);
        static void RiddleBox(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName);
        static void HintsBox(int x, int y, int width, int height, int fontSize, std::string caption, std::string imageName);

    protected:

    private:
        static sf::RenderWindow* _window;
        static sf::Font _font;
};

#endif // BASEHUD_H
