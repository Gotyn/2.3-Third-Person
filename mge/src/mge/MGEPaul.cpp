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

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH+"plane.obj");
    //Mesh* testModelMesh = Mesh::load (config::MGE_MODEL_PATH+"car.obj");
    Mesh* testModelMesh = Mesh::load (config::MGE_MODEL_PATH+"teapot_smooth.obj");
    Mesh* testModelMesh2 = Mesh::load (config::MGE_MODEL_PATH+"sphere_smooth.obj");

    //LIGHTS
    BaseLight* testLight = new BaseLight("baseLight", glm::vec3(3,3,3), glm::vec3 (1,0,0), 0.5f, glm::vec3(0,1,1));
    testLight->setMesh(testModelMesh2);
    testLight->setMaterial(new ColorMaterial(glm::vec3(1,1,0)));
    testLight->scale(glm::vec3(0.2f,0.2f,0.2f));

    BaseLight* testLight2 = new BaseLight("baseLight2", glm::vec3(-3,3,-3), glm::vec3 (1,0,0), 0.5f, glm::vec3(0,1,1));
    testLight2->setMesh(testModelMesh2);
    testLight2->setMaterial(new ColorMaterial(glm::vec3(1,1,0)));
    testLight2->scale(glm::vec3(0.2f,0.2f,0.2f));

    BaseLight* testLight3 = new BaseLight("baseLight3", glm::vec3(-3,3,3), glm::vec3 (1,0,0), 0.5f, glm::vec3(0,1,1));
    testLight3->setMesh(testModelMesh2);
    testLight3->setMaterial(new ColorMaterial(glm::vec3(1,1,0)));
    testLight3->scale(glm::vec3(0.2f,0.2f,0.2f));

    BaseLight* tempLights[3];
    tempLights[0] = testLight;
    tempLights[1] = testLight2;
    tempLights[2] = testLight3;

    //MATERIALS
    AbstractMaterial* textureMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"land.jpg"));
    LitColorMaterial* litColorMaterial = new LitColorMaterial (glm::vec3(0.0f, 1.0f, 0.0f), tempLights);
    LitColorMaterial* litColorMaterial3 = new LitColorMaterial (glm::vec3(1.0f, 1.0f, 0.5f), tempLights);
    //SCENE SETUP
    GameObject* plane = new GameObject ("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(5, 5, 5));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(litColorMaterial3);
    _world->add(plane);

    GameObject* testModel = new GameObject ("testModel", glm::vec3(0, 1, 0));
    testModel->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
    testModel->setMesh (testModelMesh);
    testModel->setMaterial(litColorMaterial);
    testModel->setBehaviour (new KeysBehaviour());
    _world->add(testModel);

    Camera* camera = new Camera ("camera", glm::vec3(0, 4.0f, 5.0f));
    camera->setBehaviour (new OrbitBehaviourPaul(10, 0.20f, 0.99f, testModel, 0.1f, 0.1f, _window));
    _world->add(camera);
    _world->setMainCamera(camera);

    glm::vec3 tempDir = glm::normalize(testLight->getWorldPosition() - testModel->getWorldPosition());
    glm::vec3 tempDir2 = glm::normalize(testLight2->getWorldPosition() - testModel->getWorldPosition());
    glm::vec3 tempDir3 = glm::normalize(testLight3->getWorldPosition() - testModel->getWorldPosition());
    testLight->setLightDirection(tempDir);
    testLight2->setLightDirection(tempDir2);
    testLight3->setLightDirection(tempDir3);
    _world->add(testLight);
    _world->add(testLight2);
    _world->add(testLight3);
    _world->addLight(testLight);
    _world->addLight(testLight2);
    _world->addLight(testLight3);

}

void MGEPaul::_render() {
    AbstractGame::_render();
    _updateHud();
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
