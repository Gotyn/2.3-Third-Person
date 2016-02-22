#version 330 core
out vec4 color;
in vec2 TexCoords;

uniform sampler2D depthMap;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * 1.0 * 7.5) / (7.5 + 1.0 - z * (7.5 - 1.0));
}

void main()
{
    float depthValue = texture(depthMap, TexCoords).r;
    color = vec4(vec3(LinearizeDepth(depthValue) / 7.5), 1.0); // perspective
    // color = vec4(vec3(depthValue), 1.0); // orthographic
}
