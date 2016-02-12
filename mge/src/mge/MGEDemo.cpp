#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <lua.hpp>

#include "mge/MGEDemo.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
#include "mge/LuaBridge/LuaBridge.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

using namespace std;

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

//build the game _world
void MGEDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    // ==== lua testing ====
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "testTable.lua");

    loadGameObject(L, "shadowCaster1");

//
//    luabridge::LuaRef t = luabridge::getGlobal(L, "window");
//    luabridge::LuaRef title = t["title"];
//
//    int width = t["width"].cast<int>();
//    int height = t["height"].cast<int>();
//
//    std::string titleString = title.cast<std::string>();
//
//    std::cout << titleString << std::endl;
//    std::cout << "width = " << width << std::endl;
//    std::cout << "height = " << height << std::endl;

    // ==== end lua test =====

    // ==== TEST NEW OBJECT CREATION ====

//    GameObject* testGO = new GameObject("testGO", glm::vec3(0,0,0));
//    _world->add(testGO);
//
//    KeysBehaviour* kb = new KeysBehaviour;
//    kb->setOwner(testGO);
////    kb->setFilename("ghost.png");
//    testGO->addBehaviour(std::type_index(typeid(KeysBehaviour)), kb);
//
//    RotatingBehaviour* rb = new RotatingBehaviour();
//    rb->setOwner(testGO);
////    npcc->setPhrase("I'M A SCARY GHOST!!!");
//    testGO->addBehaviour(std::type_index(typeid(RotatingBehaviour)), rb);

    // ==== END TEST NEW OBJECT CREATION ====
}

GameObject* MGEDemo::loadGameObject(lua_State* L, const std::string& type)
{
    GameObject* go = new GameObject("luaGO", glm::vec3(0,0,0));
    _world->add(go);

    luabridge::LuaRef shadowCasterRef = luabridge::getGlobal(L, "shadowCaster");
    for(int i = 0; i < shadowCasterRef.length(); ++i)
    {
//        std::string componentName = shadowCasterRef[i + 1]["componentName"].cast<std::string>();

        luabridge::LuaRef comp = shadowCasterRef[i + 1];
        std::string componentName = comp["componentName"].cast<std::string>();

        go->addBehaviour(componentName);

//        if (componentName == "RotatingBehaviour")
//        {
//            go->addBehaviour(std::type_index(typeid(RotatingBehaviour)));
//        }
//        else if (componentName == "NpcComponent")
//        {
//                addComponent<NpcComponent>(e);
//        }

        // create a component
        std::cout << componentName << " added to " << go->getName() << std::endl;
    }

    return go;
}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();
}

void MGEDemo::_update() {
    AbstractGame::_update();
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

MGEDemo::~MGEDemo()
{
    //dtor
}
