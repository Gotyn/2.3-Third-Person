#include "BaseLight.h"

BaseLight::BaseLight(std::string pName, glm::vec3 pPosition, glm::vec3 pAmbientColor, float pAmbientIntensity,
                     glm::vec3 pDirectionalLightColor, glm::vec3 pLightDirection): GameObject(pName, pPosition), ambientColor (pAmbientColor),
                     ambientIntensity (pAmbientIntensity), directionalLightColor(pDirectionalLightColor), lightDirection(pLightDirection)
{
    lightPosition = pPosition;
}

BaseLight::~BaseLight()
{
    //dtor
}
