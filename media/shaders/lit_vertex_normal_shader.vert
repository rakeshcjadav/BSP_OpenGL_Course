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
    vec2 outTexCoord;
    vec3 outCameraPos;
    mat3 outTBNMat;
    DirectionalLight directionalLight;
    PointLight pointLight[MAX_LIGHTS];
} vs_Out;

void main()
{
    gl_Position = ProjectionMat * CameraMat * TransformMat * vec4(Pos.x, Pos.y, Pos.z, 1.0);
    vec3 T = normalize(mat3(NormalMat) * Tangent);
    vec3 B = normalize(mat3(NormalMat) * BiTangent);
    vec3 N = normalize(mat3(NormalMat) * Normal);

    mat3 TBNMat = mat3(T, B, N);
    vs_Out.outTBNMat = TBNMat;

    mat3 outTBNMat = transpose(TBNMat);

    vs_Out.outWorldPos = outTBNMat * vec3(TransformMat * vec4(Pos, 1.0));
    vs_Out.outCameraPos = outTBNMat * CameraPos;

    vs_Out.directionalLight.direction = outTBNMat * directionalLight.direction;
    vs_Out.directionalLight.color = directionalLight.color;

    /*
    for(int i = 0; i < MAX_LIGHTS;i++)
    {
        vs_Out.pointLight[i] = pointLight[i];
        vs_Out.pointLight[i].position = normalize(outTBNMat * pointLight[i].position);
    }*/

    vs_Out.outTexCoord = TexCoord;
}