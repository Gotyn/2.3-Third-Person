//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1
#define MAX_LIGHTS 5

struct PointLight
{
    vec3 globalAmbient;
    vec3 diffuseColor;
    vec3 directionalLightColor;
    vec3 lightPosition;
    vec3 lightDirection;
    float coneAngles;
};

uniform sampler2D textureDiffuse;
uniform vec3 cameraPos;
uniform int uniformArraySize;
uniform PointLight pointLights[MAX_LIGHTS];

in vec3 wNormal;
in vec3 worldPosition;
out vec4 sColor;
in vec2 texCoord;

void main( void )
{

    vec4 result = vec4(0,0,0,0);

    for(int i = 0; i < uniformArraySize; ++i)
    {
        vec3 L = normalize(pointLights[i].lightPosition - worldPosition); //light direction
        vec3 V = normalize(cameraPos - worldPosition); //view direction
        vec3 color = pointLights[i].globalAmbient;
        float theta = dot(-L, normalize(pointLights[i].lightDirection));

        float LdotN = max(0, dot(L, wNormal));

        float diffuse = 0.4f * LdotN; //material diffuse coeff

        float specular = 0;
        float light = 0;
        vec3 ambientTerm = vec3(0,0,0);
        vec3 diffuseTerm = vec3(0,0,0);

        if(LdotN > 0.0f)
        {
            vec3 R = -normalize(reflect(L, wNormal)); //Reflection
            specular = 0.77f * pow(max(0.0f, dot(R, V)), 128.0f); //material specular coeff and shininess
        }
        //attenuation based on distance
        float d = distance(pointLights[i].lightPosition, worldPosition);
        float att = 1.0f  / (1.0f + (d * 0.00004f) + (d * d * 0.0005f));
        if(pointLights[i].coneAngles > 0)
        {
            if (theta > pointLights[i].coneAngles)
            {
                light = att * diffuse + att * specular;
                ambientTerm = color * pointLights[i].diffuseColor;
                diffuseTerm = light * pointLights[i].directionalLightColor * pointLights[i].diffuseColor;
            }
            else {
                ambientTerm = color * pointLights[i].diffuseColor;
            }
        } else {
            light = att * diffuse + att * specular;
            ambientTerm = color * pointLights[i].diffuseColor;
            diffuseTerm = light * pointLights[i].directionalLightColor * pointLights[i].diffuseColor;
        }

        result += vec4 (ambientTerm + diffuseTerm, 1);
    }
    sColor = texture(textureDiffuse,texCoord) * result;
}
