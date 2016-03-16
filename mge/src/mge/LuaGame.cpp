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

MainLight* LuaGame::mainLight = 0;

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

MainLight* LuaGame::getMainLight()
{
    return mainLight;
}

//void LuaGame::setTransform(GameObject* pGameObject, luabridge::LuaRef table)
//{
//    std::cout << "(c++) set transform for: " << pGameObject->getName() << std::endl;
//
//    glm::mat4 newMatrix;
//
//    // --- matrix data ---
//
//    newMatrix[0][0] = table[1].cast<int>();
//    newMatrix[1][0] = table[2].cast<int>();
//    newMatrix[2][0] = table[3].cast<int>();
//    newMatrix[3][0] = table[4].cast<int>();
//
//    newMatrix[0][1] = table[5].cast<int>();
//    newMatrix[1][1] = table[6].cast<int>();
//    newMatrix[2][1] = table[7].cast<int>();
//    newMatrix[3][1] = table[8].cast<int>();
//
//    newMatrix[0][2] = table[9].cast<int>();
//    newMatrix[1][2] = table[10].cast<int>();
//    newMatrix[2][2] = table[11].cast<int>();
//    newMatrix[3][2] = table[12].cast<int>();
//
//    newMatrix[0][3] = table[13].cast<int>();
//    newMatrix[1][3] = table[14].cast<int>();
//    newMatrix[2][3] = table[15].cast<int>();
//    newMatrix[3][3] = table[16].cast<int>();
//
//    // -------------------
//
//    std::cout << newMatrix << std::endl;
//
//    pGameObject->setTransform(newMatrix);
//}

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
    //camera
    GameCamera* gameCam = new GameCamera(glm::vec3(-4, 3, 10));

    //main spotlight
//    GameObject* lightGO = new GameObject("main light", glm::vec3(-1.6, 2.4, 13.4)); //old -> -3, 3, 10
//    new Light(lightGO);
//    lightGO->rotate(glm::radians(-10.0f), glm::vec3(0, 1, 0));
    mainLight = new MainLight("main light", glm::vec3(-1.6, 2.4, 13.4));
    mainLight->rotate(glm::radians(-10.0f), glm::vec3(0, 1, 0));

    luaL_dofile(_L, "mge/lua/main.lua");
}

void LuaGame::_initLua()
{
    _L = luaL_newstate();
    luaL_openlibs(_L);

    luabridge::getGlobalNamespace(_L)
        .beginNamespace ("Game")
            //game functions
            .addFunction ("getWidth", LuaGame::getWindowWidth)
            .addFunction ("time", Timer::now)
            .addFunction ("deltaTime", Timer::deltaTime)
            .addFunction ("getKeyDown", Input::getKeyDown)
            .addFunction ("getKey", Input::getKey)
            .addFunction ("getCameraObject", LuaGame::getCameraObject)
            .addFunction ("getSpotlight", LuaGame::getMainLight)
            .addFunction ("ambientLight", LuaGame::setWorldAmbient)
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
            .deriveClass <MainLight, GameObject> ("MainLight")
                .addFunction ("getIntensity", &MainLight::getIntensity)
                .addFunction ("setIntensity", &MainLight::setIntensity)
                .addFunction ("getInnerCone", &MainLight::getInnerCone)
                .addFunction ("setInnerCone", &MainLight::setInnerCone)
                .addFunction ("getOuterCone", &MainLight::getOuterCone)
                .addFunction ("setOuterCone", &MainLight::setOuterCone)
                .addFunction ("setColor", &MainLight::setColor)
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
            .addFunction ("progressBar", BaseHud::ProgressBar)
            .addFunction ("helpButton", BaseHud::HelpButton)
            .addFunction ("hintButton1", BaseHud::HintButton1)
            .addFunction ("hintButton2", BaseHud::HintButton2)
            .addFunction ("hintButton3", BaseHud::HintButton3)
            .addFunction ("helpBox", BaseHud::HelpBox)
            .addFunction ("riddleBox", BaseHud::RiddleBox)
            .addFunction ("hintsBox", BaseHud::HintsBox)
            .addFunction ("menuBox", BaseHud::MenuBox)
            .addFunction ("displayRiddleAtStart", BaseHud::DisplayRiddleAtStart)
        .endNamespace()
        .beginNamespace ("Audio")
            //audio functions
            .addFunction ("playSound", Audio::PlayEffect)
            .addFunction ("stopSound", Audio::StopEffect)
            .addFunction ("playMusic", Audio::PlayMusic)
            .addFunction ("pauseMusic", Audio::PauseMusic)
            .addFunction ("stopMusic", Audio::StopMusic)
        .endNamespace();
//        .beginNamespace ("Light")
//            //light functions
//            .addFunction ("playSound", LuaGame::PlayEffect)
//        .endNamespace();
}

void LuaGame::setWorldAmbient(float r, float g, float b)
{
    World::Instance()->ambient = glm::vec3(r, g, b);
}

PuzzleBlock* LuaGame::getActiveBlock()
{
    luabridge::LuaRef getActiveBlock = luabridge::getGlobal(_L, "getActiveBlock");

    PuzzleBlock* b = getActiveBlock();
    return b;
}

int LuaGame::getWindowWidth()
{
    return static_cast<int>(_window->getSize().x);
}

void LuaGame::_update()
{
    AbstractGame::_update();

    //call lua update function
    luabridge::LuaRef luaUpdate = luabridge::getGlobal (_L, "update");
    luaUpdate();

    // test: spotlight update target (LookAt not working) //
//    PuzzleBlock* block = getActiveBlock();
//
//    if (block != NULL)
//    {
//        mainSpotlight->getOwner()->LookAt(block);
//    }
    // end test //

    if (!BaseHud::texturesSet)
    {
        setTextureNames();
        BaseHud::texturesSet = true;
    }

    //update folder watcher
    _fileWatcher.update();
}

void LuaGame::setTextureNames()
{
    luabridge::LuaRef displayTime = luabridge::getGlobal (_L, "display_riddle_at_start");
    BaseHud::setDisplayTime(displayTime.cast<int>());

    luabridge::LuaRef help_button_texture = luabridge::getGlobal (_L, "help_button_texture");
    BaseHud::setHelpButtonTextureName(help_button_texture.cast<std::string>());

    luabridge::LuaRef hint_button1_texture = luabridge::getGlobal (_L, "hint_button1_texture");
    BaseHud::setHintButton1TextureName(hint_button1_texture.cast<std::string>());

    luabridge::LuaRef hint_button2_texture = luabridge::getGlobal (_L, "hint_button2_texture");
    BaseHud::setHintButton2TextureName(hint_button2_texture.cast<std::string>());

    luabridge::LuaRef hint_button3_texture = luabridge::getGlobal (_L, "hint_button3_texture");
    BaseHud::setHintButton3TextureName(hint_button3_texture.cast<std::string>());

    luabridge::LuaRef help_box_texture = luabridge::getGlobal (_L, "help_box_texture");
    BaseHud::setHelpBoxTextureName(help_box_texture.cast<std::string>());

    luabridge::LuaRef riddle_box_texture = luabridge::getGlobal (_L, "riddle_box_texture");
    BaseHud::setRiddleBoxTextureName(riddle_box_texture.cast<std::string>());

    luabridge::LuaRef hints_box_texture = luabridge::getGlobal (_L, "hints_box_texture");
    BaseHud::setHintsBoxTextureName(hints_box_texture.cast<std::string>());

    luabridge::LuaRef menu_box_texture = luabridge::getGlobal (_L, "menu_box_texture");
    BaseHud::setMenuBoxTextureName(menu_box_texture.cast<std::string>());

    BaseHud::loadTextures();
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

