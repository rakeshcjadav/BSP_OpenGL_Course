#version 330 core
#include "common.frag"

in vec2 outTexCoord;

uniform sampler2D MainTex;
uniform Material material;

out vec4 FragColor;

void main()
{
    FragColor = vec4(material.uDiffuseColor, 1.0f) * texture(MainTex, outTexCoord);
}