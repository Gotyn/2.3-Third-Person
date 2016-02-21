#version 330 // for glsl version (12 is for older versions , say opengl 2.1
uniform sampler2DShadow shadowMap;
verying vec4 LightVertexPos;

void main( void )
{
    float shadowValue = shadow2DProj(shadowMap, LightVertexPos).r;
    gl_FragColor = vec4(shadowValue, shadowValue, shadowValue, 1.0);
}
