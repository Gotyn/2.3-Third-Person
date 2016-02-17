#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <iostream>
#include <lua.hpp>

#include "mge/core/GameObject.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/materials/ColorMaterial.hpp"
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

    protected:

    private:
        void initialize();

        lua_State* _L;
        GameObject* _cameraObject;
        GameObject* _model;

};

#endif // MODELVIEWER_H
