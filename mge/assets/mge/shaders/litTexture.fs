#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
<<<<<<< HEAD
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
=======
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;
>>>>>>> parent of a7e6ec8... close to working

void main()
{
<<<<<<< HEAD
    // Obtain normal from normal map in range [0,1]
    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
    // Transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space

    // Get diffuse color
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;
=======
    vec3 lightDir = normalize(light.position - fs_in.FragPos);

//    // Check if lighting is inside the spotlight cone
//    float theta = dot(lightDir, normalize(-light.direction));

    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb * diffuseColor;
    vec3 normal = normalize(fs_in.Normal);
>>>>>>> parent of a7e6ec8... close to working
    // Ambient
    vec3 ambient = 0.1 * color;
    // Diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // Specular
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0f);
}
