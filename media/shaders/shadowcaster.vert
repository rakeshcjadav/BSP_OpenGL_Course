#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 Tangent;
layout (location = 3) in vec3 BiTangent;
layout (location = 4) in vec2 TexCoord;

uniform mat4 TransformMat;
uniform mat4 LightProjectionViewMat;

out VS_OUT
{
    vec2 outTexCoord;
}vs_out;


void main()
{
   gl_Position = LightProjectionViewMat * TransformMat * vec4(Pos.x, Pos.y, Pos.z, 1.0);
   vs_out.outTexCoord = TexCoord;
}