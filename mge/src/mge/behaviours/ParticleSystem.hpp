#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <GL/glew.h>
#include <glm.hpp>
#include <AbstractBehaviour.hpp>

struct Particle
{
    glm::vec3 pos, speed;
    unsigned char r,g,b,a; // Color
    float size, angle, weight;
    float life; // Remaining life of the particle. if < 0 : dead and unused.
    float cameradistance; // *Squared* distance to the camera. if dead : -1.0f

    bool operator<(const Particle& that) const
    {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};

class ParticleSystem : public AbstractBehaviour
{
    public:
        ParticleSystem();
        virtual ~ParticleSystem();

        virtual void update( float step );
        void render();
        void addBehaviourToGO(GameObject* pGameObject);

    protected:

    private:
        void sortParticles();
        int findUnusedParticle();
        // The VBO containing the 4 vertices of the particles.
        // Thanks to instancing, they will be shared by all particles.
        static GLfloat _g_vertex_buffer_data[12];
        static const int _maxParticles = 1000;

        GLfloat* _g_particule_position_size_data = new GLfloat[_maxParticles * 4];
        GLubyte* _g_particule_color_data = new GLubyte[_maxParticles * 4];
        int _particlesCount;
        int _lastUsedParticle = 0;
        Particle _particlesContainer[_maxParticles];
        GLuint _billboard_vertex_buffer;
        // The VBO containing the positions and sizes of the particles
        GLuint _particles_position_buffer;
        // The VBO containing the colors of the particles
        GLuint _particles_color_buffer;
};

#endif // PARTICLESYSTEM_H
