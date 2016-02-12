#ifndef LITCOLORMATERIAL_H
#define LITCOLORMATERIAL_H

#include "mge/materials/AbstractMaterial.hpp"
#include <glm.hpp>
#include "BaseLight.h"

/**
 * Lit color material.
 * This material uses lights.
 */
class LitColorMaterial : public AbstractMaterial
{
    public:
        LitColorMaterial(glm::vec3 pColor, BaseLight* pLights[]);
        virtual ~LitColorMaterial();
        virtual void render(World* pWorld, GameObject* pGameObject, Camera* pCamera);

        //in rgb values
        void setDiffuseColor (glm::vec3 pDiffuseColor);
        BaseLight* myLights[];

    private:
        //all the static properties are shared between instances of ColorMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uModelMatrix;
        static GLint _uViewMatrix;
        static GLint _uPerspectiveMatrix;

        static GLint uGlobalAmbientIndex[];
        static GLint uDiffuseColorIndex[];
        static GLint uDirectionalLightColorIndex[];
        static GLint uLightPositionIndex[];
        static GLint uLightDirectionIndex[];

        static GLint uCameraPosIndex;
        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

        //this one is unique per instance of color material
        glm::vec3 _diffuseColor;

        glm::vec3 ambientColorArr[3] = { glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0) };
        float ambientIntensityArr[3] = { 0, 0, 0 };
        glm::vec3 lightColorArr[3] = { glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0) };
        glm::vec3 lightPositionArr[3] = { glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0) };
        glm::vec3 lightDirectionArr[3] = { glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0) };
};

#endif // LITCOLORMATERIAL_H
