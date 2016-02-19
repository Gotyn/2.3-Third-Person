#include "ModelViewer.hpp"
#include "mge/sphinx/PuzzleBlock.hpp"

ModelViewer::ModelViewer() : GameObject("Model Viewer")
{
    initialize();
}

void ModelViewer::initialize()
{
    _cameraObject = new GameObject("camera", glm::vec3(0, 0, 5));
//    World::Instance()->add(_cameraObject);

    Camera* cb = new Camera();
    _cameraObject->addBehaviour(cb);
    World::Instance()->setMainCamera(cb);

    // ====== lua =======

    _L = luaL_newstate();
    luaL_openlibs(_L);

    luabridge::getGlobalNamespace(_L)
        .beginNamespace ("game")
            .beginClass <GameObject> ("GameObject")
//                .addFunction ("getName", &GameObject::getName)
            .endClass ()
            .deriveClass <PuzzleBlock, GameObject> ("PuzzleBlock")
                .addConstructor <void (*) (void)> ()
                .addFunction ("getName", &GameObject::getName)
                .addFunction ("setPosition", &GameObject::setLocalPositionLua)
                .addFunction ("getProgress", &PuzzleBlock::getProgress)
            .endClass ()
        .endNamespace();

    luaL_dofile(_L, "level.lua");

    // ==================

    refresh();
}

void ModelViewer::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);

    luabridge::LuaRef luaUpdate = luabridge::getGlobal (_L, "update");
    luaUpdate();
}

void ModelViewer::refresh()
{
    std::cout << "refresh model viewer" << std::endl;

    if (_model != NULL)
    {
        delete _model;
    }

    _modelNames = findFilesIn("mge/models/");
    _textureNames = findFilesIn("mge/textures/");

    _model = new GameObject(_modelNames[0]);

    _textureMaterial = new TextureMaterial(Texture::load("mge/textures/" + _textureNames[0]));
    _meshRenderer = new MeshRenderer(_modelNames[0], _textureMaterial);
    RotatingBehaviour* rb = new RotatingBehaviour();

    _model->addBehaviour(_meshRenderer);
    _model->addBehaviour(rb);

}

void ModelViewer::changeModelMesh(std::string pFilename)
{
    if (_meshRenderer == NULL)
        return;

    _meshRenderer->setMesh(pFilename);
}

void ModelViewer::changeModelTexture(std::string pFilename)
{
    if (_meshRenderer == NULL)
        return;

    _textureMaterial->changeDiffuseTexture(pFilename);
}

vector<string> ModelViewer::findFilesIn(string pFolder)
{
    vector<string> names;
    char search_path[200];
    sprintf(search_path, "%s/*.*", pFolder.c_str());
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path, &fd);
    if(hFind != INVALID_HANDLE_VALUE) {
        do {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                names.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
}

ModelViewer::~ModelViewer()
{
    //dtor
}
