#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 Tangent;
layout (location = 3) in vec3 BiTangent;
layout (location = 4) in vec2 TexCoord;

uniform mat4 TransformMat;
uniform mat4 NormalMat;
uniform mat4 CameraMat;
uniform mat4 ProjectionMat;
uniform mat4 LightProjectionViewMat;

out vec3 outWorldPos;
out vec3 outNormal;
out vec2 outTexCoord;
out mat3 outTBNMat;
out vec4 outLightSpaceFragPos;

void main()
{
   gl_Position = ProjectionMat * CameraMat * TransformMat * vec4(Pos.x, Pos.y, Pos.z, 1.0);
   outWorldPos = vec3(TransformMat * vec4(Pos, 1.0));
   outNormal = normalize(mat3(TransformMat) * Normal);
   vec3 T = normalize(mat3(TransformMat) * Tangent);
   vec3 B = normalize(mat3(TransformMat) * BiTangent);
   outTBNMat = mat3(T, B, outNormal);
   outTexCoord = TexCoord;
   outLightSpaceFragPos = LightProjectionViewMat * TransformMat * vec4(Pos, 1.0);
}