#include "BaseLight.h"
class ShadowInfo;

BaseLight::BaseLight(glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pConeDirection,
                     float pConeAngle, GameObject* pOwner): AbstractBehaviour()
{
    shadowInfo = nullptr;
    addBehaviourToGO(pOwner);
    ambientColor = pAmbientColor;
    ambientIntensity = pAmbientIntensity;
    coneDirection = pConeDirection;
    coneAngle = pConeAngle;
    World::Instance()->addLight(this);
}

BaseLight::~BaseLight() {
    if(shadowInfo) delete shadowInfo;
}

void BaseLight::addBehaviourToGO(GameObject* pGameObject) {
    pGameObject->addBehaviour(this);
}

void BaseLight::update(float pStep) {
}

void BaseLight::setShadowInfo(ShadowInfo* pValue)
{
    if(shadowInfo) delete shadowInfo;
    shadowInfo = pValue;
}
