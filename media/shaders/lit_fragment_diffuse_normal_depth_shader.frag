#version 330 core
#pragma optionNV unroll all
#include "common.frag"

in VS_OUT
{
    vec3 outWorldPos;
    vec2 outTexCoord;
    vec3 outCameraPos;
    mat3 outTBNMat;
    DirectionalLight directionalLight;
    PointLight pointLight[MAX_LIGHTS];
} fs_in;

uniform sampler2D DiffuseTex;
uniform sampler2D NormalTex;
uniform sampler2D DepthTex;
uniform mat4 NormalMat;
uniform int PointLightCount;
uniform int SpotLightCount;
uniform PointLight pointLight[MAX_LIGHTS];
uniform SpotLight spotLight[MAX_LIGHTS];
uniform Material material;

out vec4 FragColor;

vec3 GetNormal(vec2 texCoord)
{
     vec3 normal = texture(NormalTex, texCoord).rgb;
     normal = normalize(normal * 2.0f - 1.0f);
     normal.y *= -1.0f;
     return mat3(fs_in.outTBNMat) * normal;
}

vec2 ParallaxMapping(vec2 texCoords, vec3 cameraDir)
{
    float height =  texture(DepthTex, texCoords).r;
    vec2 p = -cameraDir.xy / cameraDir.z * (height * PARALLAX_HEIGHT_SCALE);
    return texCoords - p;
}

void ApplyDirectionalLights(vec3 normal, inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    ambientColor += AmbientLight(fs_in.directionalLight.color);
    diffuseColor += DiffuseDirectionalLight(normal, fs_in.directionalLight);
    specularColor += SpecularDirectionalLight(normal, fs_in.outWorldPos, fs_in.outCameraPos, fs_in.directionalLight, material);
}

void ApplyPointLights(vec3 normal, inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    for(int i = 0; i < PointLightCount; i++)
    {
        PointLight light = pointLight[i];
        light.position = fs_in.outTBNMat * light.position;
        ambientColor += AmbientLight(light.color);
        diffuseColor += DiffusePointLight(normal, fs_in.outWorldPos, light);
        specularColor += SpecularPointLight(normal, fs_in.outWorldPos, fs_in.outCameraPos, light, material);
    }
}

void ApplySpotLights(vec3 normal, inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    for(int i = 0; i < SpotLightCount; i++)
    {
        SpotLight light = spotLight[i];
        light.position = fs_in.outTBNMat * light.position;
        light.direction = normalize(fs_in.outTBNMat * light.direction);
        ambientColor += AmbientLight(light.color);
        diffuseColor += DiffuseSpotLight(normal, fs_in.outWorldPos, light);
        specularColor += SpecularSpotLight(normal, fs_in.outWorldPos, fs_in.outCameraPos, light, material);
    }
}

void main()
{
    vec3 ambientColor = vec3(0.0f);
    vec3 diffuseColor = vec3(0.0f);
    vec3 specularColor = vec3(0.0f);
    vec2 texCoord = ParallaxMapping(fs_in.outTexCoord, normalize(fs_in.outCameraPos - fs_in.outWorldPos));
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