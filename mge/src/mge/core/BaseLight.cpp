#include "BaseLight.h"

BaseLight::BaseLight(glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pConeDirection, float pConeAngle):
     AbstractBehaviour(), ambientColor (pAmbientColor), ambientIntensity (pAmbientIntensity), coneDirection(pConeDirection), coneAngle(pConeAngle)
{
}

BaseLight::~BaseLight()
{
    //dtor
}

void BaseLight::update(float pStep)
{

}
