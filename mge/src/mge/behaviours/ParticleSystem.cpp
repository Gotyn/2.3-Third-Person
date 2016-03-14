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
}

ParticleSystem::~ParticleSystem()
{
    //dtor
}

void ParticleSystem::update(float step)
{
    // Update the buffers that OpenGL uses for rendering.
    glBindBuffer(GL_ARRAY_BUFFER, _particles_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, _maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning
    // BROKEN
//    glBufferSubData(GL_ARRAY_BUFFER, 0, _particlesCount * sizeof(GLfloat) * 4, _g_particule_position_size_data);

    glBindBuffer(GL_ARRAY_BUFFER, _particles_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, _maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
    // BROKEN
//    glBufferSubData(GL_ARRAY_BUFFER, 0, _particlesCount * sizeof(GLubyte) * 4, _g_particule_color_data);
}

void ParticleSystem::render()
{
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
