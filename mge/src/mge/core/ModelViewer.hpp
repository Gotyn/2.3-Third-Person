#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <iostream>
#include <lua.hpp>
#include <windows.h>

#include "mge/core/GameObject.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/LuaBridge/LuaBridge.h"
#include "mge/lua/LuaManager.hpp"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class ModelViewer
{
    public:
        ModelViewer();
        virtual ~ModelViewer();

        void refresh();
        void changeModelMesh(std::string pFilename);
        void changeModelTexture(std::string pFilename);
        vector<string> getModelNames()
        {
            return _modelNames;
        }
        vector<string> getTextureNames()
        {
            return _textureNames;
        }
        GameObject* getModel()
        {
            return _model;
        }

    protected:

    private:
        void initialize();
        vector<string> findFilesIn(string pFolder);

        lua_State* _L;
        GameObject* _cameraObject;
        GameObject* _model;
        MeshRenderer* _meshRenderer;
        TextureMaterial* _textureMaterial;
        vector<string> _modelNames;
        vector<string> _textureNames;
};

#endif // MODELVIEWER_H
