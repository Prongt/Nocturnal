#version 330 core
out vec4 FragColor;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;


struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
    
  
in vec3 Normal;
in vec3 FragPosition;

uniform vec3 viewPosition;


void main()
{
    vec3 ambient = light.ambient * material.ambient;

    vec3 lightDirection = normalize(light.position - FragPosition);
    float diffuseStrength = max(dot(normalize(Normal), lightDirection), 0.0);
    vec3 diffuse = (diffuseStrength * material.diffuse) * light.diffuse;

    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normalize(Normal));
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = (material.specular * spec) * light.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}