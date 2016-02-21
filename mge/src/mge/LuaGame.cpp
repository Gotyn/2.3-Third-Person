#include "LuaGame.hpp"
#include "mge/core/Audio.hpp"
#include "mge/core/ModelViewer.hpp"
#include "mge/sphinx/PuzzleBlock.hpp"
#include "mge/sphinx/GameCamera.hpp"

using namespace std;

LuaGame::LuaGame()
{
    _initLua();
}

LuaGame::~LuaGame()
{

}

void LuaGame::initialize()
{
    //setup the core part
    AbstractGame::initialize();
    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new BaseHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void LuaGame::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    GameCamera* gameCam = new GameCamera();

    luaL_dofile(_L, "level.lua");
}

void LuaGame::_initLua()
{
    _L = luaL_newstate();
    luaL_openlibs(_L);

    luabridge::getGlobalNamespace(_L)
        .beginNamespace ("game")
            .addFunction ("preloadSounds", Audio::PreloadAudio)
            .addFunction ("playSound", Audio::Play)
            .beginClass <GameObject> ("GameObject")
                .addConstructor <void (*) (void)> ()
                .addFunction ("getName", &GameObject::getName)
                .addFunction ("setPosition", &GameObject::setLocalPositionLua)
            .endClass ()
            .deriveClass <PuzzleBlock, GameObject> ("PuzzleBlock")
                .addConstructor <void (*) (std::string pModelName, std::string pTextureName)> ()
                .addFunction ("getProgress", &PuzzleBlock::getProgress)
            .endClass ()
            .deriveClass <ModelViewer, GameObject> ("ModelViewer")
                .addConstructor <void (*) (void)> ()
            .endClass ()

        .endNamespace();
}

void LuaGame::_render()
{
    AbstractGame::_render();
    _updateHud();
}

void LuaGame::_update()
{
    AbstractGame::_update();

    //call lua update function
    luabridge::LuaRef luaUpdate = luabridge::getGlobal (_L, "update");
    luaUpdate();
}

void LuaGame::_processEvents()
{
    AbstractGame::_processEvents();
}

void LuaGame::_updateHud()
{

}
