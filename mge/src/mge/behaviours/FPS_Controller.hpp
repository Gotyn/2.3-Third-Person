#ifndef FPS_Controller_H
#define FPS_Controller_H

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * FPS_Controller allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class FPS_Controller : public AbstractBehaviour
{
	public:
		FPS_Controller(float moveSpeed = 5, float turnSpeed = 45);
		virtual ~FPS_Controller();
		virtual void update( float step );

    private:
        float _moveSpeed;
        float _turnSpeed;
};

#endif // FPS_Controller_H
