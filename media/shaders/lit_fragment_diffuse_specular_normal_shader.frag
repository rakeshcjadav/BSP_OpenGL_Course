#version 330 core
#include "common.frag"

in vec3 outWorldPos;
in vec3 outNormal;
in vec2 outTexCoord;
in mat3 outTBNMat;

uniform sampler2D DiffuseTex;
uniform sampler2D SpecularTex;
uniform sampler2D NormalTex;
uniform vec3 CameraPos;
uniform DirectionalLight directionalLight;
uniform int PointLightCount;
uniform PointLight pointLight[MAX_LIGHTS];
uniform int SpotLightCount;
uniform SpotLight spotLight[MAX_LIGHTS];
uniform Material material;

out vec4 FragColor;

vec3 GetNormal()
{
     vec3 normal = texture(NormalTex, outTexCoord).rgb;
     normal = normalize(normal * 2.0f - 1.0f);
     return normalize(outTBNMat * normal);
}

void ApplyDirectionalLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    ambientColor += AmbientLight(directionalLight.color);
    diffuseColor += DiffuseDirectionalLight(GetNormal(), directionalLight);
    specularColor += SpecularDirectionalLight(GetNormal(), outWorldPos, CameraPos, directionalLight, material);
}

void ApplyPointLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    for(int i = 0; i < PointLightCount; i++)
    {
        ambientColor += AmbientLight(pointLight[i].color);
        diffuseColor += DiffusePointLight(GetNormal(), outWorldPos, pointLight[i]);
        specularColor += SpecularPointLight(GetNormal(), outWorldPos, CameraPos, pointLight[i], material);
    }
}

void ApplySpotLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    for(int i = 0; i < SpotLightCount; i++)
    {
        //ambientColor += AmbientLight(spotLight[i].color);
        diffuseColor += DiffuseSpotLight(GetNormal(), outWorldPos, spotLight[i]);
        specularColor += SpecularSpotLight(GetNormal(), outWorldPos, CameraPos, spotLight[i], material);
    }
}

void main()
{
    vec3 ambientColor = vec3(0.0f);
    vec3 diffuseColor = vec3(0.0f);
    vec3 specularColor = vec3(0.0f);
    ApplyDirectionalLights(ambientColor, diffuseColor, specularColor);
    ApplyPointLights(ambientColor, diffuseColor, specularColor);
    ApplySpotLights(ambientColor, diffuseColor, specularColor);

    vec4 diffuseTexColor = texture(DiffuseTex, outTexCoord);
    ambientColor *= diffuseTexColor.rgb;
    diffuseColor *= diffuseTexColor.rgb;

    vec4 specularTexColor = texture(SpecularTex, outTexCoord);
    specularColor *= specularTexColor.rgb;

    ambientColor *= material.uAmbientColor;
    diffuseColor *= material.uDiffuseColor;
    //specularColor *= material.uSpecularColor;

    vec3 final = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(final, 1.0f);
}