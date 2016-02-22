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

#include "mge/core/Audio.hpp"


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

    // ==== AUDIO testing =====
    Audio* audio = Audio::Instance();
    //audio->LoadSounds();

    //audio->GetMusic("memory").play();
    //audio->GetMusic("piano").play();

    //audio->GetSound("gate.wav").play();
    //audio->GetSound("door.wav").play();

    Audio::Play("gate.wav");
    // ==== end AUDIO test =====

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
