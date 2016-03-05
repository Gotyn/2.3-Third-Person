#ifndef RENDERPIPELINE_H
#define RENDERPIPELINE_H

class World;
class GameObject;
class Camera;

class RenderPipeline
{
    public:
        RenderPipeline();
        virtual ~RenderPipeline();

        //render whole world
        void render (World* pWorld);

        //render specific game object within the world (using world's light settings etc)
        void render (World* pWorld, GameObject* pGameObject, Camera* pCamera, bool pRecursive);

    protected:
    private:
};

#endif // RENDERPIPELINE_H
