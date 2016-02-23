#version 330 core
out vec4 color;
in vec2 TexCoords;

uniform sampler2D shadowMap;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 0.0 - 1.0
    return (2.0 * 1.0 * 7.5) / (7.5 + 1.0 - z * (7.5 - 1.0)); //1.0 - near plane; 7.5 - far plane
}

void main()
{
    bool perspective = true;
    float depthValue = texture(shadowMap, TexCoords).r;
    color = (perspective == true) ? vec4(vec3(LinearizeDepth(depthValue) / 7.5), 1.0) : vec4(vec3(depthValue), 1.0); // perspective vs orthographic
}
