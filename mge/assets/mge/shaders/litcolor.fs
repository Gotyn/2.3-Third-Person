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

uniform sampler2D shadowMap;
uniform sampler2D textureDiffuse;
uniform vec3 cameraPos;
uniform int uniformArraySize;
uniform PointLight pointLights[MAX_LIGHTS];
vec3 L;

in vec3 wNormal;
in vec3 worldPosition;
in vec2 texCoord;
in vec4 lightVertexPos;

out vec4 sColor;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Check whether current frag pos is in shadow
    // PCF or percentage-closer filtering
    float bias = max(0.05 * (1.0 - dot(wNormal, L)), 0.005); // slight shift
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if(projCoords.z > 1.0) shadow = 0.0;
    return shadow;
}

void main( void )
{
    vec4 result = vec4(0,0,0,0);

    for(int i = 0; i < uniformArraySize; ++i)
    {
        /*/------------------- FIRST IMPLEMENTATION START ----------------//
        vec3 color = texture(textureDiffuse, texCoord).rgb;
        vec3 normal = normalize(wNormal);
        vec3 lightColor = pointLights[i].globalAmbient;
        // Ambient
        vec3 ambient = 0.2 * color;
        // Diffuse
        vec3 lightDir = normalize(pointLights[i].lightPosition - worldPosition);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = diff * lightColor;
        // Specular
        vec3 viewDir = normalize(cameraPos - worldPosition);
        float spec = 0.0;
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
        vec3 specular = spec * lightColor;
        // Calculate shadow
        float shadow = ShadowCalculation(lightVertexPos);
        vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

        result = vec4(lighting, 1.0f);
        //------------------- FIRST IMPLEMENTATION END --------------/*/

        //------------------- SECOND IMPLEMENTATION START ----------------//
        L = normalize(pointLights[i].lightPosition - worldPosition); //light direction
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
        float shadow = ShadowCalculation(lightVertexPos);
        if(pointLights[i].coneAngles > 0)
        {
            if (theta > pointLights[i].coneAngles)
            {
                light = att * diffuse + att * specular;
                ambientTerm = color * pointLights[i].diffuseColor;
                diffuseTerm = light * pointLights[i].directionalLightColor * pointLights[i].diffuseColor * shadow;
            }
            else {
                ambientTerm = color * pointLights[i].diffuseColor;
            }
        } else {
            light = att * diffuse + att * specular;
            ambientTerm = color * pointLights[i].diffuseColor;
            diffuseTerm = light * pointLights[i].directionalLightColor * pointLights[i].diffuseColor * shadow;
        }

        result += vec4 (ambientTerm + diffuseTerm, 1);
        //------------------- SECOND IMPLEMENTATION END ----------------//
    }
    sColor = texture(textureDiffuse,texCoord) * result;
    //sColor = result;
}
