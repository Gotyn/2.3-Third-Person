#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <iostream>
#include <glm.hpp>
#include <unordered_map>
#include <typeindex>

class AbstractCollider;
class AbstractBehaviour;
class World;

class GameObject
{
	public:
		GameObject(std::string pName = NULL, glm::vec3 pPosition = glm::vec3( 0.0f, 0.0f, 0.0f ), bool pAddToWorld = true );
		virtual ~GameObject();

        void setName (std::string pName);
        std::string getName() const;

        //contains local rotation, scale, position
		void setTransform (const glm::mat4& pTransform);
        glm::mat4& getTransform();

        glm::vec3 getForward();
        glm::vec3 getUp();

        float pitch(float pAmount);
        float roll(float pAmount);
        float yaw(float pAmount);

        //access just the local position
        void setLocalPositionLua (float x, float y, float z);
		void setLocalPosition (glm::vec3 pPosition);
		glm::vec3 getLocalPosition();

        //get the objects world position by combining transforms
		glm::vec3 getWorldPosition();
		virtual glm::mat4& getWorldTransform();

        //change local position, rotation, scaling
		void translate(glm::vec3 pTranslation);
		void move(float x, float y, float z);
		void rotate(float pAngle, glm::vec3 pAxis);
		void scale(glm::vec3 pScale);
		void scaleLua(float x, float y, float z);

		void LookAt(GameObject* pTarget);

		//new multiple behaviours:
		void addBehaviour(AbstractBehaviour* pBehaviour);

        template <typename T>
        T* getBehaviour() {
            if(_behaviours.count(&typeid(T))!=0) {
                return static_cast<T*>(_behaviours[&typeid(T)]);
            }
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
        std::unordered_map<const std::type_info* , AbstractBehaviour *> _behaviours;

        //update children list administration
        void _innerAdd (GameObject* pChild);
		void _innerRemove (GameObject* pChild);
};

#endif // GAMEOBJECT_H
