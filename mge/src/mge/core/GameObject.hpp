#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <iostream>
#include <glm.hpp>
#include <map>
#include <typeindex>

class AbstractCollider;
class AbstractBehaviour;
class World;

/**
 * A GameObject wraps all data required to display an (interactive / dynamic) object, but knows nothing about OpenGL or rendering.
 * GameObject exposes both local and world transform and shows one way of how you can cache the worldtransform.
 * A nice addition for you as a student would be for example to try and add an inversetransform and inverseworldtransform (also cached).
 *
 * You will need to alter this class to add colliders etc.
 */
class GameObject
{
	public:
		GameObject(std::string pName = NULL, glm::vec3 pPosition = glm::vec3( 0.0f, 0.0f, 0.0f ) );
		virtual ~GameObject();

        void setName (std::string pName);
        std::string getName() const;

        //contains local rotation, scale, position
		void setTransform (const glm::mat4& pTransform);
        glm::mat4& getTransform();

        //access just the local position
		void setLocalPosition (glm::vec3 pPosition);
		glm::vec3 getLocalPosition();

        //get world
        World* getWorld();

        //get the objects world position by combining transforms
		glm::vec3 getWorldPosition();
		virtual glm::mat4& getWorldTransform();

        //change local position, rotation, scaling
		void translate(glm::vec3 pTranslation);
		void rotate(float pAngle, glm::vec3 pAxis);
		void scale(glm::vec3 pScale);

		//new multiple behaviours:
		void addBehaviour(AbstractBehaviour* pBehaviour);

        template <typename T> T* getBehaviour()
        {
//            auto it = _behaviours.find(std::type_index(typeid(T)));
//            if (it != _behaviours.end()) {
//                return dynamic_cast<T*>(it->second);
//            }
            return nullptr;
        }

		virtual void update(float pStep, const glm::mat4& pParentTransform);

        //child management

        //shortcut to set the parent of pChild to ourselves
		void add (GameObject* pChild);
		//shortcut to set the parent of pChild to NULL
		void remove (GameObject* pChild);

		virtual void setParent (GameObject* pGameObject);
		GameObject* getParent();

        int getChildCount();
        GameObject* getChildAt (int pIndex);

	protected:
		std::string _name;
		glm::mat4 _transform;
		glm::mat4 _worldTransform;

        GameObject* _parent;
		std::vector<GameObject*> _children;
        std::vector<AbstractBehaviour*> _behaviours;

        std::string _type; //type of GameObject(eg. tree/car)

		World* _world;

        //update children list administration
        void _innerAdd (GameObject* pChild);
		void _innerRemove (GameObject* pChild);
};

#endif // GAMEOBJECT_H
