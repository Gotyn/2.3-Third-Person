#version 330 // for glsl version (12 is for older versions , say opengl 2.1)

uniform mat4 T_MVP;
in vec3 vertex;

void main( void )
{
	gl_Position = T_MVP * vec4(vertex,1);
}
