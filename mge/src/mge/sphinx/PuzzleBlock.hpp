#ifndef PUZZLEBLOCK_HPP
#define PUZZLEBLOCK_HPP

#include <GameObject.hpp>
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/materials/TextureMaterial.hpp"

class PuzzleBlock : public GameObject
{
    public:
        PuzzleBlock(std::string pModelName, std::string pTextureName);
        virtual ~PuzzleBlock();

        virtual void update(float pStep, const glm::mat4& pParentTransform);
        float getProgress();
        float pitch(float pAmount);
        float roll(float pAmount);
        float yaw(float pAmount);
    protected:

    private:
        RotatingBehaviour* _rotatingBehavour;
        MeshRenderer* _meshRenderer;
        AbstractMaterial* _material;
        glm::vec3 _targetForward;
};

#endif // PUZZLEBLOCK_HPP
