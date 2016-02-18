#version 330 // for glsl version (12 is for older versions , say opengl 2.1

void main( void )
{
    gl_FragColor = vec4(gl_FragCoord.z);
}
