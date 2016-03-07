#version 330 core
out vec4 color;
in vec2 TexCoords;

<<<<<<< HEAD
uniform sampler2DShadow shadowMap;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 0.0 - 1.0
    return (2.0 * 1.0 * 7.5) / (7.5 + 1.0 - z * (7.5 - 1.0)); //1.0 - near plane; 7.5 - far plane
}
=======
uniform sampler2D depthMap;
>>>>>>> refs/remotes/origin/master

void main()
{
    float depthValue = texture(depthMap, TexCoords).r;
    color = vec4(vec3(depthValue), 1.0);
}
