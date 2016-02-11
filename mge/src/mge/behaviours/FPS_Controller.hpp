#ifndef FPS_Controller_H
#define FPS_Controller_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * FPS_Controller allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class FPS_Controller : public AbstractBehaviour
{
	public:
		FPS_Controller(float moveSpeed = 5, float sensitivity = 1000);
		virtual ~FPS_Controller();
		virtual void update( float step );

    private:
        float _moveSpeed;
        float _sensitivity;
        float _mouseX, _mouseY;

        glm::vec2 _mouseOld;
        glm::vec2 _mouseDelta;
};

#endif // FPS_Controller_H
