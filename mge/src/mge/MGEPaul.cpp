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

    //MESHES
    Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH+"plane.obj");
    Mesh* testModelMesh = Mesh::load (config::MGE_MODEL_PATH+"teapot_smooth.obj");
    Mesh* lightBowlMesh = Mesh::load (config::MGE_MODEL_PATH+"sphere_smooth.obj");

    //LIGHTS
    BaseLight* testLight = new BaseLight("spot", glm::vec3(0,3,0), glm::vec3 (1,0,0), 0.5f, glm::vec3(1,1,1), glm::vec3(1,-1,0), 0.92f);
    testLight->setMesh(lightBowlMesh);
    testLight->setMaterial(new ColorMaterial(glm::vec3(1,1,0)));
    testLight->scale(glm::vec3(0.2f,0.2f,0.2f));

    BaseLight* testLight2 = new BaseLight("positional", glm::vec3(-3,3,-3), glm::vec3 (1,0,0), 0.5f, glm::vec3(1,1,1), glm::vec3(0,1,0));
    testLight2->setMesh(lightBowlMesh);
    testLight2->setMaterial(new ColorMaterial(glm::vec3(1,1,0)));
    testLight2->scale(glm::vec3(0.2f,0.2f,0.2f));

    /*BaseLight* testLight3 = new BaseLight("baseLight3", glm::vec3(-3,3,3), glm::vec3 (1,0,0), 0.5f, glm::vec3(0,1,1));
    testLight3->setMesh(lightBowlMesh);
    testLight3->setMaterial(new ColorMaterial(glm::vec3(1,1,0)));
    testLight3->scale(glm::vec3(0.2f,0.2f,0.2f));

    BaseLight* testLight4 = new BaseLight("baseLight4", glm::vec3(-4,3,-5), glm::vec3 (1,0,0), 0.5f, glm::vec3(0,1,1));
    testLight4->setMesh(lightBowlMesh);
    testLight4->setMaterial(new ColorMaterial(glm::vec3(1,1,0)));
    testLight4->scale(glm::vec3(0.2f,0.2f,0.2f));

    BaseLight* testLight5 = new BaseLight("baseLight5", glm::vec3(1,3,2), glm::vec3 (1,0,0), 0.5f, glm::vec3(0,1,1));
    testLight5->setMesh(lightBowlMesh);
    testLight5->setMaterial(new ColorMaterial(glm::vec3(1,1,0)));
    testLight5->scale(glm::vec3(0.2f,0.2f,0.2f));*/

    _world->add(testLight);
    //_world->add(testLight2);
    /*_world->add(testLight3);
    _world->add(testLight4);
    _world->add(testLight5);*/
    _world->addLight(testLight);
    //_world->addLight(testLight2);
    /*_world->addLight(testLight3);
    _world->addLight(testLight4);
    _world->addLight(testLight5);*/

    //MATERIALS
    LitColorMaterial* litColorMaterial = new LitColorMaterial (glm::vec3(0.0f, 1.0f, 0.0f), _world);
    LitColorMaterial* litColorMaterial_2 = new LitColorMaterial (glm::vec3(0.0f, 0.9f, 0.0f), _world);
    //SCENE SETUP
    GameObject* plane = new GameObject ("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(5, 5, 5));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(litColorMaterial_2);
    _world->add(plane);

    GameObject* plane2 = new GameObject ("plane2", glm::vec3(5, 5, 0));
    plane2->rotate(glm::radians(90.0f), glm::vec3(0,0,1));
    plane2->scale(glm::vec3(5, 5, 5));
    plane2->setMesh(planeMeshDefault);
    plane2->setMaterial(litColorMaterial_2);
    _world->add(plane2);

    GameObject* plane3 = new GameObject ("plane3", glm::vec3(-5, 5, 0));
    plane3->rotate(glm::radians(-90.0f), glm::vec3(0,0,1));
    plane3->scale(glm::vec3(5, 5, 5));
    plane3->setMesh(planeMeshDefault);
    plane3->setMaterial(litColorMaterial_2);
    _world->add(plane3);

    GameObject* plane4 = new GameObject ("plane4", glm::vec3(0, 5, -5));
    plane4->rotate(glm::radians(90.0f), glm::vec3(1,0,0));
    plane4->scale(glm::vec3(5, 5, 5));
    plane4->setMesh(planeMeshDefault);
    plane4->setMaterial(litColorMaterial_2);
    _world->add(plane4);

    GameObject* testModel = new GameObject ("testModel", glm::vec3(0, 0.5f, 0));
    testModel->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
    testModel->setMesh (testModelMesh);
    testModel->setMaterial(litColorMaterial);
    testModel->setBehaviour (new KeysBehaviour());
    _world->add(testModel);

    Camera* camera = new Camera ("camera", glm::vec3(0, 4.0f, 5.0f));
    camera->setBehaviour (new OrbitBehaviourPaul(10, 0.20f, 0.99f, testModel, 0.1f, 0.1f, _window));
    _world->add(camera);
    _world->setMainCamera(camera);
}

void MGEPaul::_render() {
    AbstractGame::_render();
    _updateHud();
    _world->renderDebugInfo();
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
