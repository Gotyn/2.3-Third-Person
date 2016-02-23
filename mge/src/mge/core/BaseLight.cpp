#include "BaseLight.h"

BaseLight::BaseLight(glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pConeDirection,
                     float pConeAngle, GameObject* pOwner): AbstractBehaviour(pOwner)
{
    ambientColor = pAmbientColor;
    ambientIntensity = pAmbientIntensity;
    coneDirection = pConeDirection;
    coneAngle = pConeAngle;
    World::Instance()->addLight(this);
}

BaseLight::~BaseLight()
{
    //dtor
}

void BaseLight::update(float pStep)
{

}
