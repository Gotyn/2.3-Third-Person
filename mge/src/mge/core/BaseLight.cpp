#include "BaseLight.h"

BaseLight::BaseLight(glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pDirectionalLightColor, glm::vec3 pLightDirection,
                     float pConeAngle): AbstractBehaviour(), ambientColor (pAmbientColor), ambientIntensity (pAmbientIntensity),
                     directionalLightColor(pDirectionalLightColor), lightDirection(pLightDirection), coneAngle(pConeAngle)
{
    _shadowInfo = new ShadowInfo(glm::perspective(glm::radians(60.0f), 4.0f/3.0f, 0.1f, 1000.0f));
}

BaseLight::~BaseLight()
{
    //dtor
}

void BaseLight::update(float pStep)
{

}

void BaseLight::setShadowInfo(ShadowInfo* pValue)
{
    if(_shadowInfo) delete _shadowInfo;
    _shadowInfo = pValue;
}
