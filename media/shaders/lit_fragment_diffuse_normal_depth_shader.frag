#version 330 core
#pragma optionNV unroll all
#include "common.frag"

in VS_OUT
{
    vec3 outWorldPos;
    vec3 outNormal;
    vec2 outTexCoord;
    mat3 outTBNMat;
} fs_in;

uniform sampler2D DiffuseTex;
uniform sampler2D NormalTex;
uniform sampler2D DepthTex;
uniform vec3 CameraPos;
uniform DirectionalLight directionalLight;
uniform int PointLightCount;
uniform PointLight pointLight[MAX_LIGHTS];
uniform int SpotLightCount;
uniform SpotLight spotLight[MAX_LIGHTS];
uniform Material material;

out vec4 FragColor;

vec3 GetNormal(vec2 texCoord)
{
     vec3 normal = texture(NormalTex, texCoord).rgb;
     normal = normalize(normal * 2.0f - 1.0f);
     return normalize(fs_in.outTBNMat * normal);
}

vec2 ParallaxMapping(vec2 texCoords, vec3 cameraDir)
{
    float height =  texture(DepthTex, texCoords).r;
    vec2 p = cameraDir.xy / cameraDir.z * (height * PARALLAX_HEIGHT_SCALE);
    return texCoords - p;
}

void ApplyDirectionalLights(vec3 normal, inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    DirectionalLight light = directionalLight;
    vec3 cameraPos = CameraPos;
    vec3 worldPos = fs_in.outWorldPos;
    ambientColor += AmbientLight(light.color);
    diffuseColor += DiffuseDirectionalLight(normal, light);
    specularColor += SpecularDirectionalLight(normal, fs_in.outWorldPos, cameraPos, light, material);
}

void ApplyPointLights(vec3 normal, inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    for(int i = 0; i < PointLightCount; i++)
    {
        PointLight light = pointLight[i];
        ambientColor += AmbientLight(light.color);
        diffuseColor += DiffusePointLight(normal, fs_in.outWorldPos, light);
        specularColor += SpecularPointLight(normal, fs_in.outWorldPos, CameraPos, light, material);
    }
}

void ApplySpotLights(vec3 normal, inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    for(int i = 0; i < SpotLightCount; i++)
    {
        SpotLight light = spotLight[i];
        ambientColor += AmbientLight(light.color);
        diffuseColor += DiffuseSpotLight(normal, fs_in.outWorldPos, light);
        specularColor += SpecularSpotLight(normal, fs_in.outWorldPos, CameraPos, light, material);
    }
}

void main()
{
    vec3 ambientColor = vec3(0.0f);
    vec3 diffuseColor = vec3(0.0f);
    vec3 specularColor = vec3(0.0f);
    vec3 cameraPos = fs_in.outTBNMat * CameraPos;
    vec3 worldPos = fs_in.outTBNMat * fs_in.outWorldPos;
    vec2 texCoord = ParallaxMapping(fs_in.outTexCoord, normalize(cameraPos - worldPos));
    vec3 normal = GetNormal(texCoord);

    ApplyDirectionalLights(normal, ambientColor, diffuseColor, specularColor);
    ApplyPointLights(normal, ambientColor, diffuseColor, specularColor);
    ApplySpotLights(normal, ambientColor, diffuseColor, specularColor);

    vec4 diffuseTexColor = texture(DiffuseTex, texCoord);
    ambientColor *= diffuseTexColor.rgb;
    diffuseColor *= diffuseTexColor.rgb;

    ambientColor *= material.uAmbientColor;
    diffuseColor *= material.uDiffuseColor;
    specularColor *= material.uSpecularColor;

    vec3 final = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(final, 1.0f);
}