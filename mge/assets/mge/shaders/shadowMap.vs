#version 330 // for glsl version (12 is for older versions , say opengl 2.1)

uniform mat4 T_MVP;
in vec3 vertex;

out vec4 LightVertexPos;

void main( void )
{
	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * vec4(vertex,1);
    LightVertexPos = T_MVP * vec4(vertex,1);
}
