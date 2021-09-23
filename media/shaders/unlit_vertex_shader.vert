#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

uniform mat4 TransformMat;
uniform mat4 CameraMat;
uniform mat4 ProjectionMat;

out vec2 outTexCoord;

/*
out struct VS_OUT
{
    vec3 outWorldPos;
    vec4 outColor;
    vec3 outNormal;
    vec2 outTexCoord;
}vs_out;
*/

void main()
{
;
   gl_Position = ProjectionMat * CameraMat * TransformMat * vec4(Pos.x, Pos.y, Pos.z, 1.0);
   outTexCoord = TexCoord;
}