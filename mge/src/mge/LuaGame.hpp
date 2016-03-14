#ifndef LUAGAME_H
#define LUAGAME_H

#include <lua.hpp>
#include <FileWatcher/FileWatcher.h>
#include <AbstractGame.hpp>

#include "mge/core/BaseHud.hpp"
#include "mge/LuaBridge/LuaBridge.h"
#include "mge/sphinx/StoryWall.hpp"
#include "ParticleSystem.hpp"

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
        virtual void reloadHud();

        static int getWindowWidth();
        static GameObject* getCameraObject();
//        static void setTransform(GameObject* pGameObject, luabridge::LuaRef table);

	protected:
        virtual void _initializeScene();
        virtual void _update();
        virtual void _lateUpdate();
        virtual void _processEvents();

	private:
	    void _initLua();
        void _updateGUI();

        lua_State* _L;
        BaseHud* _hud;
        StoryWall* _storyWall;
        FW::FileWatcher _fileWatcher;
        ParticleSystem* _particleSystem;
};

#endif // LUAGAME_H
