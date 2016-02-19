#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
//#include <lua.hpp>

#include "mge/MGEDemo.hpp"
#include "mge/sphinx/PuzzleBlock.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
//#include "mge/LuaBridge/LuaBridge.h"

//extern "C" {
//# include "lua.h"
//# include "lauxlib.h"
//# include "lualib.h"
//}

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
	_hud = new BaseHud(_window);
	cout << "HUD initialized." << endl << endl;

//	//lua setup
//	_L = luaL_newstate();
//    luaL_openlibs(_L);
//
////    LuaRef luaUpdate = getGlobal (_L, "same");
}

void MGEDemo::testFunc(int i) {
    cout << i;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);
    _modelViewer = new ModelViewer();
}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();
}

void MGEDemo::_update() {
    AbstractGame::_update();

    if (getKeyDown(sf::Keyboard::F1))
        _modelViewer->refresh();
}

void MGEDemo::_processEvents() {
    AbstractGame::_processEvents();
}

void MGEDemo::_updateHud() {
    // show list of all available models
    vector<string> modelnames = _modelViewer->getModelNames();
    for (size_t i=0; i < modelnames.size(); i++)
    {
        if(_hud->Button(0, i * 25, modelnames[i]) == true)
        {
            _modelViewer->changeModelMesh(modelnames[i]);
        }
    }

    // show list of all available textures
    vector<string> texturenames = _modelViewer->getTextureNames();
    for (size_t i=0; i < texturenames.size(); i++)
    {
        if(_hud->Button(195, i * 25, texturenames[i]) == true)
        {
            _modelViewer->changeModelTexture(texturenames[i]);
        }
    }
}

MGEDemo::~MGEDemo()
{
    //dtor
}
