#include <algorithm>

#include "ParticleSystem.hpp"
#include "GameObject.hpp"

GLfloat ParticleSystem::_g_vertex_buffer_data[] = {};

ParticleSystem::ParticleSystem()
{
    _g_vertex_buffer_data[0] = -0.5f;
    _g_vertex_buffer_data[1] = -0.5f;
    _g_vertex_buffer_data[2] = 0.0f;

    _g_vertex_buffer_data[3] = 0.5f;
    _g_vertex_buffer_data[4] = -0.5f;
    _g_vertex_buffer_data[5] = -0.0f;

    _g_vertex_buffer_data[6] = -0.5f;
    _g_vertex_buffer_data[7] = 0.5f;
    _g_vertex_buffer_data[8] = 0.0f;

    _g_vertex_buffer_data[9] = 0.5f;
    _g_vertex_buffer_data[10] = 0.5f;
    _g_vertex_buffer_data[11] = 0.0f;

    glGenBuffers(1, &_billboard_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _billboard_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_g_vertex_buffer_data), _g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &_particles_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _particles_position_buffer);
    // Initialize with empty (NULL) buffer : it will be updated later, each frame.
    glBufferData(GL_ARRAY_BUFFER, _maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

    glGenBuffers(1, &_particles_color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _particles_color_buffer);
    // Initialize with empty (NULL) buffer : it will be updated later, each frame.
    glBufferData(GL_ARRAY_BUFFER, _maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

    for(int i=0; i<_maxParticles; i++)
    {
		_particlesContainer[i].life = -1.0f;
		_particlesContainer[i].cameradistance = -1.0f;
	}
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::sortParticles()
{
    std::sort(&_particlesContainer[0], &_particlesContainer[_maxParticles]);
}

void ParticleSystem::update(float step)
{
    // Generate 10 new particule each millisecond,
    // but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
    // newparticles will be huge and the next frame even longer.
    int newparticles = (int)(step*10000.0);
    if (newparticles > (int)(0.016f*10000.0))
        newparticles = (int)(0.016f*10000.0);

    for(int i=0; i<newparticles; i++)
    {
        int particleIndex = findUnusedParticle();
        _particlesContainer[particleIndex].life = 5.0f; // This particle will live 5 seconds.
        _particlesContainer[particleIndex].pos = glm::vec3(0,0,-20.0f);

        float spread = 1.5f;
        glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f);
        // Very bad way to generate a random direction;
        // See for instance http://stackoverflow.com/questions/5408276/python-uniform-spherical-distribution instead,
        // combined with some user-controlled parameters (main direction, spread, etc)
        glm::vec3 randomdir = glm::vec3(
            (rand()%2000 - 1000.0f)/1000.0f,
            (rand()%2000 - 1000.0f)/1000.0f,
            (rand()%2000 - 1000.0f)/1000.0f
        );

        _particlesContainer[particleIndex].speed = maindir + randomdir*spread;

        // Very bad way to generate a random color
        _particlesContainer[particleIndex].r = rand() % 256;
        _particlesContainer[particleIndex].g = rand() % 256;
        _particlesContainer[particleIndex].b = rand() % 256;
        _particlesContainer[particleIndex].a = (rand() % 256) / 3;

        _particlesContainer[particleIndex].size = (rand()%1000)/2000.0f + 0.1f;
    }

    // Simulate all particles
    int particlesCount = 0;
    for(int i=0; i<_maxParticles; i++)
    {
//        std::cout << i << std::endl;

        Particle& p = _particlesContainer[i]; // shortcut

//        if(p.life > 0.0f)
//        {
//            // Decrease life
//            p.life -= step;
//            if (p.life > 0.0f)
//            {
//                // Simulate simple physics : gravity only, no collisions
//                p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)step * 0.5f;
//                p.pos += p.speed * (float)step;
////                p.cameradistance = glm::length2( p.pos - CameraPosition );
//                //ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;
//
//                // Fill the GPU buffer
//                _g_particule_position_size_data[4*_particlesCount+0] = p.pos.x;
//                _g_particule_position_size_data[4*_particlesCount+1] = p.pos.y;
//                _g_particule_position_size_data[4*_particlesCount+2] = p.pos.z;
//
//                _g_particule_position_size_data[4*_particlesCount+3] = p.size;
//
//                _g_particule_color_data[4*_particlesCount+0] = p.r;
//                _g_particule_color_data[4*_particlesCount+1] = p.g;
//                _g_particule_color_data[4*_particlesCount+2] = p.b;
//                _g_particule_color_data[4*_particlesCount+3] = p.a;
//            }
//            else
//            {
//                // Particles that just died will be put at the end of the buffer in SortParticles();
//                p.cameradistance = -1.0f;
//            }
//
//            _particlesCount++;
//        }
    }

    sortParticles();
}

void ParticleSystem::render()
{
    // Update the buffers that OpenGL uses for rendering.
    glBindBuffer(GL_ARRAY_BUFFER, _particles_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, _maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning
    glBufferSubData(GL_ARRAY_BUFFER, 0, _particlesCount * sizeof(GLfloat) * 4, _g_particule_position_size_data);

    glBindBuffer(GL_ARRAY_BUFFER, _particles_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, _maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _particlesCount * sizeof(GLubyte) * 4, _g_particule_color_data);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _billboard_vertex_buffer);
    glVertexAttribPointer(
        0, // attribute. No particular reason for 0, but must match the layout in the shader.
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        (void*)0 // array buffer offset
    );

    // 2nd attribute buffer : positions of particles' centers
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _particles_position_buffer);
    glVertexAttribPointer(
        1, // attribute. No particular reason for 1, but must match the layout in the shader.
        4, // size : x + y + z + size => 4
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        (void*)0 // array buffer offset
    );

    // 3rd attribute buffer : particles' colors
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, _particles_color_buffer);
    glVertexAttribPointer(
        2, // attribute. No particular reason for 1, but must match the layout in the shader.
        4, // size : r + g + b + a => 4
        GL_UNSIGNED_BYTE, // type
        GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
        0, // stride
        (void*)0 // array buffer offset
    );

    // These functions are specific to glDrawArrays*Instanced*.
    // The first parameter is the attribute buffer we're talking about.
    // The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
    // http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
    glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
    glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
    glVertexAttribDivisor(2, 1); // color : one per quad -> 1

    // Draw the particules!
    // This draws many times a small triangle_strip (which looks like a quad).
    // This is equivalent to :
    // for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
    // but faster.
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, _particlesCount);
}

int ParticleSystem::findUnusedParticle()
{
    for(int i=_lastUsedParticle; i<_maxParticles; i++)
    {
        if (_particlesContainer[i].life < 0)
        {
            _lastUsedParticle = i;
            return i;
        }
    }

    for(int i=0; i<_lastUsedParticle; i++)
    {
        if (_particlesContainer[i].life < 0)
        {
            _lastUsedParticle = i;
            return i;
        }
    }

    return 0; // All particles are taken, override the first one
}

void ParticleSystem::addBehaviourToGO(GameObject* pGameObject)
{
    pGameObject->addBehaviour(this);
}
