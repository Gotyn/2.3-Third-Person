#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <lua.hpp>

#include "mge/MGEPaul.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

using namespace std;
class ShadowInfo;

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEPaul::MGEPaul():AbstractGame ()
{
}

void MGEPaul::initialize() {
    //setup the core part
    AbstractGame::initialize();
    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void MGEPaul::_initializeScene()
{
    _renderer->setClearColor(0,0,0);


    //ADD LIGHTS
    GameObject* spotLightGO = new GameObject("spot", glm::vec3(0,2.0f,0));
    spotLightGO->scale(glm::vec3(0.2f, 0.2f, 0.2f));
    spotLightGO->rotate(glm::radians(-90.0f), glm::vec3(0,1.0f,0));
    World::Instance()->add(spotLightGO);
    BaseLight* testLight = new BaseLight(glm::vec3 (1,1,1), 0.5f, glm::vec3(1,1,1), glm::vec3(1,0,0), 0.95f);
    spotLightGO->addBehaviour(testLight);
    testLight->setLightPosition(testLight->getOwner()->getWorldPosition());
    World::Instance()->addLight(testLight);
    MeshRenderer* spotLightMesh = new MeshRenderer("sphere_smooth.obj", new ColorMaterial(glm::vec3(1,1,0)));
    spotLightGO->addBehaviour(spotLightMesh);
    KeysBehaviour* kb = new KeysBehaviour();
    spotLightGO->addBehaviour(kb);

    /*
    GameObject* spotLightGO2 = new GameObject("positional", glm::vec3(-3,3,-3));
    spotLightGO2->scale(glm::vec3(0.2f, 0.2f, 0.2f));
    World::Instance()->add(spotLightGO2);
    BaseLight* testLight2 = new BaseLight(glm::vec3 (1,1,1), 0.5f, glm::vec3(1,1,1), glm::vec3(1,-1,0));
    spotLightGO2->addBehaviour(testLight2);
    testLight2->setLightPosition(testLight2->getOwner()->getWorldPosition());
    World::Instance()->addLight(testLight2);
    MeshRenderer* spotLightMesh2 = new MeshRenderer("sphere_smooth.obj", new ColorMaterial(glm::vec3(1,1,0)));
    spotLightGO2->addBehaviour(spotLightMesh2);
    */

    //ADD PLANE GO, MESH AND MATERIAL
    GameObject* teapot = new GameObject ("ceiling", glm::vec3(3.5f, 2, 0));
    teapot->rotate(glm::radians(0.0f), glm::vec3(1,0,0));
    teapot->scale(glm::vec3(0.5f, 0.5f, 0.5f));
    World::Instance()->add(teapot);
    MeshRenderer* teapotMesh = new MeshRenderer("teapot_smooth.obj",
           new LitColorMaterial(glm::vec3(1,1,1), Texture::load (config::MGE_TEXTURE_PATH+"bricks.jpg")));
    teapot->addBehaviour(teapotMesh);
    RotatingBehaviour* rb = new RotatingBehaviour();
    teapot->addBehaviour(rb);

    GameObject* plane = new GameObject ("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(5, 5, 5));
    World::Instance()->add(plane);
    MeshRenderer* planeMesh = new MeshRenderer("plane.obj",
           new LitColorMaterial(glm::vec3(1,1,1), Texture::load (config::MGE_TEXTURE_PATH+"land.jpg")));
    plane->addBehaviour(planeMesh);

    GameObject* plane2 = new GameObject ("wall left", glm::vec3(5, 2, 0));
    plane2->rotate(glm::radians(90.0f), glm::vec3(0,0,1));
    plane2->scale(glm::vec3(2, 1, 5));
    World::Instance()->add(plane2);
    MeshRenderer* planeMesh2 = new MeshRenderer("plane.obj",
           new LitColorMaterial(glm::vec3(1,1,1), Texture::load (config::MGE_TEXTURE_PATH+"land.jpg")));
    plane2->addBehaviour(planeMesh2);

    GameObject* plane3 = new GameObject ("wall right", glm::vec3(-5, 2, 0));
    plane3->rotate(glm::radians(-90.0f), glm::vec3(0,0,1));
    plane3->scale(glm::vec3(2, 1, 5));
    World::Instance()->add(plane3);
    MeshRenderer* planeMesh3 = new MeshRenderer("plane.obj",
           new LitColorMaterial(glm::vec3(1,1,1), Texture::load (config::MGE_TEXTURE_PATH+"land.jpg")));
    plane3->addBehaviour(planeMesh3);

    GameObject* plane4 = new GameObject ("wall front", glm::vec3(0, 2, -5));
    plane4->rotate(glm::radians(90.0f), glm::vec3(1,0,0));
    plane4->scale(glm::vec3(5, 1, 2));
    World::Instance()->add(plane4);
    MeshRenderer* planeMesh4 = new MeshRenderer("plane.obj",
           new LitColorMaterial(glm::vec3(1,1,1), Texture::load (config::MGE_TEXTURE_PATH+"land.jpg")));
    plane4->addBehaviour(planeMesh4);

    GameObject* plane5 = new GameObject ("ceiling", glm::vec3(0, 4, 0));
    plane5->rotate(glm::radians(180.0f), glm::vec3(1,0,0));
    plane5->scale(glm::vec3(5, 5, 5));
    World::Instance()->add(plane5);
    MeshRenderer* planeMesh5 = new MeshRenderer("plane.obj",
           new LitColorMaterial(glm::vec3(1,1,1), Texture::load (config::MGE_TEXTURE_PATH+"land.jpg")));
    plane5->addBehaviour(planeMesh5);

    //ADD CAMERA GO, CAMERA COMPONENT AND BEHAVIOUR
    GameObject* cameraGO = new GameObject("camera", glm::vec3(0, 2.0f, 5.0f));
    cameraGO->rotate(glm::radians(-45.0f),glm::vec3(0,1,0));
    World::Instance()->add(cameraGO);
    Camera* camera = new Camera ();
    camera->setOwner(cameraGO);
    World::Instance()->setMainCamera(camera);
    //OrbitBehaviourPaul* orbit = new OrbitBehaviourPaul(10, 0.20f, 0.99f, plane, 0.1f, 0.1f, _window);
    //cameraGO->addBehaviour(orbit);
}

void MGEPaul::_render() {
    AbstractGame::_render();
    _updateHud();
    //World::Instance()->renderDebugInfo();
}

void MGEPaul::_update() {
    AbstractGame::_update();
}

void MGEPaul::_processEvents() {
    AbstractGame::_processEvents();
}

void MGEPaul::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";
    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEPaul::~MGEPaul()
{
    //dtor
}
