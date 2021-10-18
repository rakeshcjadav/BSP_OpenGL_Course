#version 330 core
#pragma optionNV unroll all
#include "common.frag"

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 Tangent;
layout (location = 3) in vec3 BiTangent;
layout (location = 4) in vec2 TexCoord;

uniform mat4 TransformMat;
uniform mat4 NormalMat;
uniform mat4 CameraMat;
uniform mat4 ProjectionMat;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight[MAX_LIGHTS];
uniform SpotLight spotLight[MAX_LIGHTS];

uniform vec3 CameraPos;

out VS_OUT
{
    vec3 outWorldPos;
    vec3 outNormal;
    vec2 outTexCoord;
    mat3 outTBNMat;
} vs_out;

void main()
{
    gl_Position = ProjectionMat * CameraMat * TransformMat * vec4(Pos.x, Pos.y, Pos.z, 1.0);
    vec3 T = normalize(mat3(TransformMat) * Tangent);
    vec3 B = normalize(mat3(TransformMat) * BiTangent);
    vec3 N = normalize(mat3(TransformMat) * Normal);
    vs_out.outTBNMat = mat3(T, B, N);
    vs_out.outWorldPos = vec3(TransformMat * vec4(Pos, 1.0));
    vs_out.outTexCoord = TexCoord;
}