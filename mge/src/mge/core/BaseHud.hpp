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
        bool Button(int x, int y, std::string caption);

    protected:

    private:
        sf::RenderWindow* _window;
        sf::Font _font;
};

#endif // BASEHUD_H
