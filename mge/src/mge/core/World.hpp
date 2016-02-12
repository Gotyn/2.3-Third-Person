#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "mge/core/GameObject.hpp"
#include "mge/core/BaseLight.h"

class Light;
class Camera;

class World : public GameObject
{
	public:
        World();

		void setMainCamera (Camera* pCamera);
		Camera* getMainCamera();

        void renderDebugInfo();
        void addLight(BaseLight* light);
        std::vector<BaseLight*> getLights() { return _lights; }

	private:
	    Camera* _mainCamera;
	    std::vector<BaseLight*> _lights;
};


#endif // WORLD_H
