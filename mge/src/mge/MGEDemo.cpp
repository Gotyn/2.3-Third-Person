#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <lua.hpp>

#include "mge/MGEDemo.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
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

    _loadLuaScene(L);
    loadGameObject(L, "camera");
    loadGameObject(L, "gameObject");
}

void MGEDemo::_loadLuaScene(lua_State* L)
{
    luabridge::LuaRef sceneRef = luabridge::getGlobal(L, "scene");

    for (int i = 0; i < sceneRef.length(); ++i)
    {
        cout << i << " test counter!!!" << endl;
    }
}

GameObject* MGEDemo::loadGameObject(lua_State* L, char* type)
{
    GameObject* go = new GameObject("luaGO", glm::vec3(0,0,0));
    _world->add(go);

    luabridge::LuaRef gameObjectRef = luabridge::getGlobal(L, type);
    for(int i = 0; i < gameObjectRef.length(); ++i)
    {
        luabridge::LuaRef comp = gameObjectRef[i + 1];
        std::string componentName = comp["componentName"].cast<std::string>();

        if (componentName == "Transform")
        {
            float x = comp["x"].cast<float>();
            float y = comp["y"].cast<float>();
            float z = comp["z"].cast<float>();

            go->setLocalPosition(glm::vec3(x,y,z));
        }

        if (componentName == "Camera")
        {
            Camera* camera = new Camera ();
            camera->setOwner(go);
            go->addBehaviour(camera);
            _world->setMainCamera(camera);
        }

        if (componentName == "MeshRenderer")
        {
            std::string modelName = comp["modelname"].cast<std::string>();
//            std::cout << modelName << std::endl;

            MeshRenderer* mr = new MeshRenderer(modelName, new ColorMaterial(glm::vec3(1,1,0)));
            mr->setOwner(go);
            go->addBehaviour(mr);
        }

        if (componentName == "RotatingBehaviour")
        {
            RotatingBehaviour* rb = new RotatingBehaviour();
            rb->setOwner(go);
            go->addBehaviour(rb);
        }

        // log created component
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
