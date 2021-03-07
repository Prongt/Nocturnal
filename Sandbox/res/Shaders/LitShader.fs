#version 330 core
out vec4 FragColor;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
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
in vec2 TexCoords;

uniform vec3 viewPosition;


void main()
{
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    vec3 lightDirection = normalize(light.position - FragPosition);
    float diffuseStrength = max(dot(normalize(Normal), lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diffuseStrength * texture(material.diffuse, TexCoords).rgb;

    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normalize(Normal));
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular =  light.specular * spec * texture(material.specular, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}