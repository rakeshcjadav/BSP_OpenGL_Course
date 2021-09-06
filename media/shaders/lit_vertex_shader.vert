#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

uniform mat4 TransformMat;
uniform mat4 CameraMat;
uniform mat4 ProjectionMat;

out vec3 outWorldPos;
out vec3 outNormal;
out vec2 outTexCoord;

void main()
{
   gl_Position = ProjectionMat * CameraMat * TransformMat * vec4(Pos.x, Pos.y, Pos.z, 1.0);
   outWorldPos = vec3(TransformMat * vec4(Pos, 1.0));
   vec4 normal = transpose(inverse(TransformMat)) * vec4(Normal, 1.0f);
   outNormal = normalize(normal.xyz);
   outTexCoord = TexCoord;
}