#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include <lua.hpp>
#include "mge/MGEDemo.hpp"
#include "mge/core/LuaLevelManager.h"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame ()
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();
    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

int say(lua_State * _lua)
{
    cout << "hello from c++ func from lua\n" << endl;
    return 0;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);
    _initializeSceneFromLua();
}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();
}

void MGEDemo::_update() {
    AbstractGame::_update();
    LuaLevelManager::detectCollision(LuaLevelManager::_lua);
    LuaLevelManager::setGameTimeToLua(LuaLevelManager::_lua);
    LuaLevelManager::luaUpdateLoop(LuaLevelManager::_lua);
}

void MGEDemo::_processEvents() {
    AbstractGame::_processEvents();
}

void MGEDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";
    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}
//takes data provided by lua script and initializes scene
void MGEDemo::_initializeSceneFromLua()
{
    LuaLevelManager::fillInArrays(LuaLevelManager::_lua);
    std::vector<GameObject*> myGO = LuaLevelManager::makeObjectsForLevel();
    for(int i = 0; i < myGO.size(); ++i) _world->add(myGO[i]);
    Camera* camera = LuaLevelManager::_camera();
    camera->setBehaviour(new LookAt(myGO[0]));
    _world->add(camera);
    _world->setMainCamera(camera);
}

MGEDemo::~MGEDemo()
{
    //dtor
}
