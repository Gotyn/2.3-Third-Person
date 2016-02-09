#include "mge/behaviours/FPS_Controller.hpp"
#include "mge/core/GameObject.hpp"

#include <sfml/window/event.hpp>

FPS_Controller::FPS_Controller(float moveSpeed, float turnSpeed): AbstractBehaviour(), _moveSpeed(moveSpeed), _turnSpeed(turnSpeed)
{
}

FPS_Controller::~FPS_Controller()
{

}

void FPS_Controller::update( float pStep )
{
	float moveSpeed = 0.0f; //default if no keys
	float turnSpeed = 0.0f;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moveSpeed = _moveSpeed;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moveSpeed = -_moveSpeed;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		turnSpeed = -_turnSpeed;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		turnSpeed = +_turnSpeed;
	}

	//translate the object in its own local space
	_owner->translate( glm::vec3(0.0f, 0.0f, moveSpeed*pStep ) );

	//we can also translate directly, basically we take the z axis from the matrix
	//which is normalized and multiply it by moveSpeed*step, than we add it to the
	//translation component
	//glm::mat4 transform = _owner->getTransform();
	//transform[3] += transform[2] * moveSpeed*pStep;
	//_owner->setTransform(transform);

	//rotate the object in its own local space
	_owner->rotate( glm::radians(turnSpeed*pStep), glm::vec3(0.0f, 1.0f, 0.0f ) );
}
