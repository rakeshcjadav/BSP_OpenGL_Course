#version 330 core

struct Material {
    vec3 uAmbientColor;
    vec3 uDiffuseColor;
    vec3 uSpecularColor;
    float uShininess;
}; 

in vec2 outTexCoord;

uniform sampler2D MainTex;
uniform float Scale;
uniform float SineTime;
uniform Material material;

out vec4 FragColor;

void main()
{
    FragColor = vec4(material.uDiffuseColor, 1.0f) * texture(MainTex, outTexCoord);
}