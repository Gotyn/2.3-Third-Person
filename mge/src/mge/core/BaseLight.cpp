#include "BaseLight.h"

BaseLight::BaseLight(std::string pName, glm::vec3 pPosition, glm::vec3 pAmbientColor, float pAmbientIntensity,
                     glm::vec3 pDirectionalLightColor, glm::vec3 pLightDirection, float pConeAngle): GameObject(pName, pPosition), ambientColor (pAmbientColor),
                     ambientIntensity (pAmbientIntensity), directionalLightColor(pDirectionalLightColor), lightDirection(pLightDirection), coneAngle(pConeAngle)
{
    lightPosition = pPosition;
}

BaseLight::~BaseLight()
{
    //dtor
}
