#version 330 core
out vec4 FragColor;
  
in vec3 Normal;
in vec3 FragPosition;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;


void main()
{
    float ambientLightingStrength = 0.1;
    vec3 ambient = ambientLightingStrength * lightColor;

    vec3 lightDirection = normalize(lightPosition - FragPosition);
    float diffuseStrength = max(dot(normalize(Normal), lightDirection), 0.0);
    vec3 diffuse = diffuseStrength * lightColor;

    float specularStrength = 0.5;
    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normalize(Normal));
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}