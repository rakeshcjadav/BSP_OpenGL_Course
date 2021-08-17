#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 TexCoord;

uniform vec4 Color;
uniform float Scale;
uniform mat4 TransformMat;
uniform mat4 CameraMat;
uniform mat4 ProjectionMat;

out float value;
out vec4 outColor;
out vec2 outTexCoord;

void main()
{
   gl_Position = ProjectionMat * CameraMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   value = aPos.x;
   outColor = Color * vec4(1.0f, aPos.y+0.5f, 1.0f, 1.0);
   outTexCoord = TexCoord;
}