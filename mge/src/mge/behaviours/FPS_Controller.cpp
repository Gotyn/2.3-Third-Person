#include "mge/behaviours/FPS_Controller.hpp"
#include "mge/core/GameObject.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sfml/window/event.hpp>

using namespace std;

FPS_Controller::FPS_Controller(float moveSpeed, float sensitivity)
    : AbstractBehaviour(), _moveSpeed(moveSpeed), _sensitivity(sensitivity)
{
    _mouseX = sf::Mouse::getPosition().x;
    _mouseY = sf::Mouse::getPosition().y;
    _mouseOld = glm::vec2(_mouseX, _mouseY);
    _mouseDelta = glm::vec2(_mouseX - _mouseOld.x, _mouseY - _mouseOld.y);
}

FPS_Controller::~FPS_Controller(){

}

void FPS_Controller::update( float pStep )
{
	float sensitivity = 0.0f;

	//KeysBehaviour
	float moveSpeed = 0.0f; //default if no keys

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moveSpeed = -_moveSpeed;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moveSpeed = _moveSpeed;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

	}

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space)) {
        cout << _mouseX << "\n\n\n\n";
	}

	//translate the object in its own local space
    _owner->translate( glm::vec3(0.0f, 0.0f, moveSpeed*pStep ) );


	//----------------------------------------

	//mouse movement
    //_mouseOld = glm::vec2(_mouseX, _mouseY);
    _mouseOld = glm::vec2(200.0f,200.0f);

    _mouseX = sf::Mouse::getPosition().x;
    _mouseY = sf::Mouse::getPosition().y;

    _mouseDelta = glm::vec2(_mouseX - _mouseOld.x, _mouseY - _mouseOld.y);

    _owner->rotate(-_mouseDelta.x / _sensitivity, glm::vec3(0,1,0));
    _owner->rotate(-_mouseDelta.y / _sensitivity, glm::vec3(1,0,0));

    _mouseDelta = glm::vec2(0.0f,0.0f);
    sf::Mouse::setPosition(sf::Vector2i(200.0f,200.0f));
}
