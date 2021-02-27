#version 330 core
out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D myTexture;
    
void main()
{
    FragColor = texture(myTexture, v_TexCoord) * v_Color;
}