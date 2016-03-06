#include "LuaGame.hpp"
#include "mge/core/Timer.hpp"
#include "mge/core/Input.hpp"
#include "mge/core/Audio.hpp"
#include "mge/core/ModelViewer.hpp"
#include "mge/util/UpdateListener.hpp"
#include "mge/sphinx/PuzzleBlock.hpp"
#include "mge/sphinx/Prop.hpp"
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
//	hudStaticRef = _hud; // TODO: needs a better way to access the hud statically for lua
	cout << "HUD initialized." << endl << endl;

	// add a watch to the system
    FW::WatchID watchID = _fileWatcher.addWatch("./mge/lua", new UpdateListener(this));
}

void LuaGame::reloadHud()
{
    std::cout << "reload hud call from c++" << std::endl;

    luabridge::LuaRef luaRefreshHud = luabridge::getGlobal (_L, "refreshHud");
    luaRefreshHud();
}

//build the game _world
void LuaGame::_initializeScene()
{
    GameCamera* gameCam = new GameCamera(glm::vec3(0, 0, 10));
    luaL_dofile(_L, "mge/lua/main.lua");
}

void LuaGame::_initLua()
{
    _L = luaL_newstate();
    luaL_openlibs(_L);

    luabridge::getGlobalNamespace(_L)
        .beginNamespace ("Game")
            //game functions
            .addFunction ("time", Timer::now)
            .addFunction ("deltaTime", Timer::deltaTime)
            .addFunction ("getKeyDown", Input::getKeyDown)
            .addFunction ("getKey", Input::getKey)
            //game classes
            .beginClass <GameObject> ("GameObject")
                .addConstructor <void (*) (void)> ()
                .addFunction ("getName", &GameObject::getName)
                .addFunction ("setPosition", &GameObject::setLocalPositionLua)
                .addFunction ("move", &GameObject::move)
                .addFunction ("pitch", &GameObject::pitch)
                .addFunction ("roll", &GameObject::roll)
                .addFunction ("yaw", &GameObject::yaw)
                .addFunction ("scale", &GameObject::scaleLua)
                .addFunction ("lookAt", &GameObject::LookAt)
            .endClass ()
            .deriveClass <PuzzleBlock, GameObject> ("PuzzleBlock")
                .addConstructor <void (*) (std::string pModelName, std::string pTextureName, std::string pObjectName)> ()
                .addFunction ("getProgress", &PuzzleBlock::getProgress)
                .addFunction ("printStatus", &PuzzleBlock::printStatus)
            .endClass ()
            .deriveClass <Prop, GameObject> ("Prop")
                .addConstructor <void (*) (std::string pModelName, std::string pTextureName, std::string pObjectName)> ()
            .endClass ()
        .endNamespace()
        .beginNamespace ("Hud")
            .addFunction ("button", BaseHud::Button)
            .addFunction ("label", BaseHud::Label)
        .endNamespace()
        .beginNamespace ("Audio")
            //audio functions
            .addFunction ("playSound", Audio::PlayEffect)
        .endNamespace();
}

void LuaGame::_update()
{
    AbstractGame::_update();

    //call lua update function
    luabridge::LuaRef luaUpdate = luabridge::getGlobal (_L, "update");
    luaUpdate();

    //update folder watcher
    _fileWatcher.update();

    //update GUI
    _updateGUI();
}

void LuaGame::_processEvents()
{
    AbstractGame::_processEvents();
}

void LuaGame::_updateGUI()
{
    luabridge::LuaRef luaUpdateGUI = luabridge::getGlobal (_L, "updateGUI");
    luaUpdateGUI();
}
