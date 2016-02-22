#ifndef LUAGAME_H
#define LUAGAME_H

#include <lua.hpp>
#include <AbstractGame.hpp>

#include "mge/core/Renderer.hpp"
#include "mge/core/BaseHud.hpp"
#include "mge/LuaBridge/LuaBridge.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class LuaGame : public AbstractGame
{
    public:
		LuaGame();
		virtual ~LuaGame();
        virtual void initialize();

	protected:
        virtual void _initializeScene();
	    virtual void _render();
        virtual void _update();
        virtual void _processEvents();

	private:
	    void _initLua();
        void _updateHud();

        lua_State* _L;
        BaseHud* _hud;
};

#endif // LUAGAME_H
