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
        static void Label(int x, int y, std::string caption);

    protected:

    private:
        static sf::RenderWindow* _window;
        static sf::Font _font;

        //all previously loaded sprites;
		static std::map<std::string, sf::Sprite*> _sprites;
};

#endif // BASEHUD_H
