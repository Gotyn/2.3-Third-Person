#ifndef PUZZLEBLOCK_HPP
#define PUZZLEBLOCK_HPP

#include <GameObject.hpp>
#include "mge/behaviours/RotatingBehaviour.hpp"

class PuzzleBlock : public GameObject
{
    public:
        PuzzleBlock();
        virtual ~PuzzleBlock();

        virtual void update(float pStep, const glm::mat4& pParentTransform);
        float getProgress();
    protected:

    private:
        RotatingBehaviour* _rotatingBehavour;
        glm::vec3 _targetForward;
};

#endif // PUZZLEBLOCK_HPP
