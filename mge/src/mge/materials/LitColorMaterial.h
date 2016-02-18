#ifndef LITCOLORMATERIAL_H
#define LITCOLORMATERIAL_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include <glm.hpp>
#include <iostream>
#include <sstream>
#include <ostream>
#include "BaseLight.h"

#define MAX_LIGHTS_NUM 5
/**
 * Lit color material.
 * This material uses lights.
 */

using namespace std;

class LitColorMaterial : public AbstractMaterial
{
    public:
        LitColorMaterial(glm::vec3 pColor, World* pWorld, Texture* pDiffuseTexture);
        virtual ~LitColorMaterial();
        virtual void render(World* pWorld, GameObject* pGameObject, Mesh* pMesh, Camera* pCamera);

        //in rgb values
        void setDiffuseColor (glm::vec3 pDiffuseColor);
        void setDiffuseTexture (Texture* pDiffuseTexture);

        static string uniName(string propertyName, int lightIndex);

    private:
        //all the static properties are shared between instances of ColorMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static ShaderProgram* _shader;
        static ShaderProgram* _shadowShader;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uModelMatrix;
        static GLint _uViewMatrix;
        static GLint _uPerspectiveMatrix;
        static GLint _uT_MVP;

        static GLint uGlobalAmbientIndex[];
        static GLint uDiffuseColorIndex[];
        static GLint uDirectionalLightColorIndex[];
        static GLint uLightPositionIndex[];
        static GLint uLightDirectionIndex[];
        static GLint uConeAnglesIndex[];

        static GLint uCameraPosIndex;
        static GLint lightsUniforArraySize;
        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

        //this one is unique per instance of material
        glm::vec3 _diffuseColor;
        Texture* _diffuseTexture;
        Texture* _shadowTexture;

        static glm::vec3 ambientColors[];
        static float ambientIntensities[];
        static glm::vec3 lightColors[];
        static glm::vec3 lightPositions[];
        static glm::vec3 lightDirections[];
        static float coneAngles[];

        static int tempSize;
        static World* _myWorld;
};

#endif // LITCOLORMATERIAL_H
