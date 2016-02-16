#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <lua.hpp>

#include "mge/MGEMartijn.h"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
#include "mge/LuaBridge/LuaBridge.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include "Audio.hpp"


using namespace std;

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEMartijn::MGEMartijn():AbstractGame ()
{
}

void MGEMartijn::initialize() {
    //setup the core part
    AbstractGame::initialize();
    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void MGEMartijn::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    // ==== lua testing ====
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "testTable.lua");

    luabridge::LuaRef t = luabridge::getGlobal(L, "window");
    luabridge::LuaRef title = t["title"];

    int width = t["width"].cast<int>();
    int height = t["height"].cast<int>();

    std::string titleString = title.cast<std::string>();

    std::cout << titleString << std::endl;
    std::cout << "width = " << width << std::endl;
    std::cout << "height = " << height << std::endl;

    // ==== end lua test =====


    // ==== AUDIO testing =====
    Audio* audio = Audio::Instance();
    audio->playSound("Gate.wav");
    audio->playSound("Pistol_DryFire.wav");
    // ==== end AUDIO test =====


    // ==== TEST NEW OBJECT CREATION ====

    GameObject* testGO = new GameObject("testGO", glm::vec3(0,0,0));
    _world->add(testGO);

    KeysBehaviour* kb = new KeysBehaviour;
    kb->setOwner(testGO);
//    kb->setFilename("ghost.png");
    testGO->addBehaviour(std::type_index(typeid(KeysBehaviour)), kb);

    RotatingBehaviour* rb = new RotatingBehaviour();
    rb->setOwner(testGO);
//    npcc->setPhrase("I'M A SCARY GHOST!!!");
    testGO->addBehaviour(std::type_index(typeid(RotatingBehaviour)), rb);

    // ==== END TEST NEW OBJECT CREATION ====
}

void MGEMartijn::_render() {
    AbstractGame::_render();
    _updateHud();
}

void MGEMartijn::_update() {
    AbstractGame::_update();
}

void MGEMartijn::_processEvents() {
    AbstractGame::_processEvents();
}

void MGEMartijn::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";
    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEMartijn::~MGEMartijn()
{
    //dtor
}
