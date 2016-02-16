#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include <iostream>

#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"

class LuaManager
{
    public:
        LuaManager();
        virtual ~LuaManager();

        static void testFunction(std::string pMessage);

    protected:
    private:

};

#endif // LUAMANAGER_H
