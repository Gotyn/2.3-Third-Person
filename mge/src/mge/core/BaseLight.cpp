#include "BaseLight.h"

BaseLight::BaseLight(glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pDirectionalLightColor, glm::vec3 pLightDirection,
                     float pConeAngle): AbstractBehaviour(), ambientColor (pAmbientColor), ambientIntensity (pAmbientIntensity),
                     directionalLightColor(pDirectionalLightColor), lightDirection(pLightDirection), coneAngle(pConeAngle), m_shadowInfo(0)
{

}

BaseLight::~BaseLight()
{
    //dtor
}

void BaseLight::update(float pStep)
{

}
