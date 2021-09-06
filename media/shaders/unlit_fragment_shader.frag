#version 330 core

in vec2 outTexCoord;

uniform sampler2D MainTex;
uniform float Scale;
uniform float SineTime;

out vec4 FragColor;

void main()
{
    FragColor = texture(MainTex, outTexCoord);
}