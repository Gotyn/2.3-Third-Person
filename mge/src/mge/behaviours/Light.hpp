#ifndef LIGHT_H
#define LIGHT_H

#include <AbstractBehaviour.hpp>


class Light : public AbstractBehaviour
{
    public:
        Light(GameObject* pOwner);
        virtual ~Light();

        virtual void update(float step);
        void addBehaviourToGO(GameObject* pGameObject);
        float getInnerCone() const;
        float getOuterCone() const;

    protected:
    private:
        float _innerCone;
        float _outerCone;
};

#endif // LIGHT_H
