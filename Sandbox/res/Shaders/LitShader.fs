#version 330 core
out vec4 FragColor;
  
in vec3 Normal;
in vec3 FragPosition;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;


void main()
{
    float ambientLightingStrength = 0.0;
    vec3 ambient = ambientLightingStrength * lightColor;

    vec3 lightDirection = normalize(lightPosition - FragPosition);
    float diffuseStrength = max(dot(normalize(Normal), lightDirection), 0.0);
    vec3 diffuse = diffuseStrength * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}