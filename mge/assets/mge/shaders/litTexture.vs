#version 330 core
layout (location = 0) in vec3 position; //d
layout (location = 1) in vec3 normal; //d
layout (location = 2) in vec2 texCoords; //d
<<<<<<< HEAD
=======

out vec2 TexCoords;
>>>>>>> parent of a7e6ec8... close to working

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
<<<<<<< HEAD
<<<<<<< HEAD
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;
=======
    vec4 FragPosLightSpace;
} vs_out;

=======
    vec4 FragPosLightSpace;
} vs_out;

>>>>>>> parent of a7e6ec8... close to working
uniform mat4 projection; //d
uniform mat4 view; //d
uniform mat4 model; //d
uniform mat4 lightSpaceMatrix; //d
<<<<<<< HEAD
>>>>>>> parent of a7e6ec8... close to working
=======
>>>>>>> parent of a7e6ec8... close to working

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    vs_out.FragPos = vec3(model * vec4(position, 1.0));
    vs_out.TexCoords = texCoords;
<<<<<<< HEAD

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);

    mat3 TBN = transpose(mat3(T, B, N));
    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
=======
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
<<<<<<< HEAD
>>>>>>> parent of a7e6ec8... close to working
=======
>>>>>>> parent of a7e6ec8... close to working
}
