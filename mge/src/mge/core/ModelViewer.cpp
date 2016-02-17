#include "ModelViewer.hpp"

ModelViewer::ModelViewer()
{
    initialize();
}

void ModelViewer::initialize()
{
    _cameraObject = new GameObject("camera", glm::vec3(0, 0, 5));
    World::Instance()->add(_cameraObject);

    Camera* cb = new Camera();
    _cameraObject->addBehaviour(cb);
    World::Instance()->setMainCamera(cb);

    // ====== lua =======

    _L = luaL_newstate();
    luaL_openlibs(_L);

    luabridge::getGlobalNamespace(_L)
        .beginNamespace ("game")
            .beginClass <GameObject> ("GameObject")
                .addFunction ("getName", &GameObject::getName)
            .endClass ()
            .addFunction("testFunction", LuaManager::testFunction)
            .addFunction("createProp", LuaManager::createProp)
        .endNamespace();

    // ==================

    refresh();
}

void ModelViewer::refresh()
{
    std::cout << "refresh model viewer" << std::endl;

    if (_model != NULL)
    {
        delete _model;
    }

    luaL_dofile(_L, "testTable.lua");

    luabridge::LuaRef modelTable = luabridge::getGlobal(_L, "model");
    std::string filename = modelTable["filename"].cast<std::string>();

    _model = new GameObject(filename);
    World::Instance()->add(_model);

    AbstractMaterial* am = new ColorMaterial();
    MeshRenderer* mr = new MeshRenderer(filename, am);
    RotatingBehaviour* rb = new RotatingBehaviour();

    _model->addBehaviour(mr);
    _model->addBehaviour(rb);

//    std::cout << filename << std::endl;
}

ModelViewer::~ModelViewer()
{
    //dtor
}
