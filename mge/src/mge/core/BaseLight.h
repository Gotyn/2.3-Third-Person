#ifndef BASELIGHT_H
#define BASELIGHT_H +

#include <string>
#include "mge/core/GameObject.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Base is just a GameObject with all basic values for the basic light implementation:
 * ambientColor, ambientIntensity, directionalLightVector, directionalLightColor
 */
class BaseLight : public AbstractBehaviour
{
    public:
        BaseLight(glm::vec3 ambientColor = glm::vec3 (1,0,0), float ambientIntensity = 0.2f,
                  glm::vec3 directionalLightColor = glm::vec3(1,0,0), glm::vec3 pLightDirection = glm::vec3 (0,-1,0),
                  float pConeAngle = 0.0f);
        virtual ~BaseLight();
        glm::vec3 getAmbientColor() { return ambientColor; }
        float getAmbientIntensity() { return ambientIntensity; }
        glm::vec3 getDirectionalLightColor() { return directionalLightColor; }
        glm::vec3 getLightPosition() { return getOwner()->getWorldPosition(); }
        void setLightDirection(glm::vec3 pValue) { lightDirection = pValue; }
        void setLightPosition(glm::vec3 pValue) { lightPosition = pValue; }
        glm::vec3 getLightDirection() { return lightDirection; }
        float getConeAngle() { return coneAngle; }
        void update(float pStep);
    private:
        //values for the uniforms
        glm::vec3 ambientColor;
        float ambientIntensity;
        glm::vec3 directionalLightColor;
        glm::vec3 lightPosition;
        glm::vec3 lightDirection;
        float coneAngle;
};

#endif // BASELIGHT_H
