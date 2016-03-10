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

GameObject* LuaGame::getCameraObject()
{
    return World::Instance()->getMainCamera()->getOwner();
}

void LuaGame::setTransform(GameObject* pGameObject, luabridge::LuaRef table)
{
    std::cout << "(c++) set transform for: " << pGameObject->getName() << std::endl;

    glm::mat4 newMatrix;

    // --- matrix data ---

//    luabridge::LuaRef c = table[1];
//    int test = table[1].cast<int>();
//
//    std::cout << "<<<<<<<<<<<  " << test << std::endl;

    newMatrix[0][0] = table[1].cast<int>();
    newMatrix[1][0] = table[2].cast<int>();
    newMatrix[2][0] = table[3].cast<int>();
    newMatrix[3][0] = table[4].cast<int>();

    newMatrix[0][1] = table[5].cast<int>();
    newMatrix[1][1] = table[6].cast<int>();
    newMatrix[2][1] = table[7].cast<int>();
    newMatrix[3][1] = table[8].cast<int>();

    newMatrix[0][2] = table[9].cast<int>();
    newMatrix[1][2] = table[10].cast<int>();
    newMatrix[2][2] = table[11].cast<int>();
    newMatrix[3][2] = table[12].cast<int>();

    newMatrix[0][3] = table[13].cast<int>();
    newMatrix[1][3] = table[14].cast<int>();
    newMatrix[2][3] = table[15].cast<int>();
    newMatrix[3][3] = table[16].cast<int>();

    // -------------------

    std::cout << newMatrix << std::endl;

    pGameObject->setTransform(newMatrix);

    for (int i = 1; i < table.length() + 1; ++i)
    {
        luabridge::LuaRef choice = table[i];
        std::cout << "* " << choice << std::endl;
    }
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
    GameCamera* gameCam = new GameCamera(glm::vec3(-4, 3, 10));
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
            .addFunction ("getCameraObject", LuaGame::getCameraObject)
            .addFunction ("setTransform", LuaGame::setTransform)
            //game classes
            .beginClass <GameObject> ("GameObject")
                .addConstructor <void (*) (void)> ()
                .addFunction ("getName", &GameObject::getName)
                .addFunction ("setActive", &GameObject::setActive)
                .addFunction ("printStatus", &GameObject::printStatus)
                .addFunction ("setPosition", &GameObject::setLocalPositionLua)
                .addFunction ("move", &GameObject::move)
                .addFunction ("rotateAroundAxis", &GameObject::rotateAroundAxis)
                .addFunction ("pitch", &GameObject::pitch)
                .addFunction ("roll", &GameObject::roll)
                .addFunction ("yaw", &GameObject::yaw)
                .addFunction ("scale", &GameObject::scaleLua)
                .addFunction ("lookAt", &GameObject::LookAt)
            .endClass ()
            .deriveClass <StoryWall, GameObject> ("StoryWall")
                .addConstructor <void (*) (std::string pModelName, std::string pTextureName, std::string pObjectName)> ()
                .addFunction ("changeTexture", &StoryWall::setTexture)
            .endClass ()
            .deriveClass <PuzzleBlock, GameObject> ("PuzzleBlock")
                .addConstructor <void (*) (std::string pModelName, std::string pTextureName, std::string pObjectName, float x, float y, float z)> ()
                .addFunction ("getProgress", &PuzzleBlock::getProgress)
                .addFunction ("flash", &PuzzleBlock::flash)
            .endClass ()
            .deriveClass <Prop, GameObject> ("Prop")
                .addConstructor <void (*) (std::string pModelName, std::string pTextureName, std::string pObjectName)> ()
            .endClass ()
        .endNamespace()
        .beginNamespace ("Hud")
            .addFunction ("button", BaseHud::Button)
            .addFunction ("textLabel", BaseHud::TextLabel)
            .addFunction ("label", BaseHud::Label)
            .addFunction ("riddleButton", BaseHud::RiddleButton)
            .addFunction ("hintsButton", BaseHud::RiddleButton)
            .addFunction ("riddleBox", BaseHud::RiddleBox)
            .addFunction ("hintsBox", BaseHud::HintsBox)
        .endNamespace()
        .beginNamespace ("Audio")
            //audio functions
            .addFunction ("playSound", Audio::PlayEffect)
            .addFunction ("stopSound", Audio::StopEffect)
            .addFunction ("playMusic", Audio::PlayMusic)
            .addFunction ("pauseMusic", Audio::PauseMusic)
            .addFunction ("stopMusic", Audio::StopMusic)
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
}

void LuaGame::_lateUpdate()
{
    AbstractGame::_lateUpdate();

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

    glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();
    luaUpdateGUI();
    _window->popGLStates();
}
