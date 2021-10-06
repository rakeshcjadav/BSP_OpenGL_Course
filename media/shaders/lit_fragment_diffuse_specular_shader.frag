#version 330 core
#include "common.frag"

in vec3 outWorldPos;
in vec3 outNormal;
in vec2 outTexCoord;

uniform sampler2D DiffuseTex;
uniform sampler2D SpecularTex;
uniform vec3 CameraPos;
uniform DirectionalLight directionalLight;
uniform int PointLightCount;
uniform PointLight pointLight[MAX_LIGHTS];
uniform int SpotLightCount;
uniform SpotLight spotLight[MAX_LIGHTS];
uniform Material material;

out vec4 FragColor;

void ApplyDirectionalLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    ambientColor += AmbientLight(directionalLight.color);
    diffuseColor += DiffuseDirectionalLight(outNormal, directionalLight);
    specularColor += SpecularDirectionalLight(outNormal, outWorldPos, CameraPos, directionalLight, material);
}

void ApplyPointLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    for(int i = 0; i < PointLightCount; i++)
    {
        ambientColor += AmbientLight(pointLight[i].color);
        diffuseColor += DiffusePointLight(outNormal, outWorldPos, pointLight[i]);
        specularColor += SpecularPointLight(outNormal, outWorldPos, CameraPos, pointLight[i], material);
    }
}

void ApplySpotLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    for(int i = 0; i < SpotLightCount; i++)
    {
        //ambientColor += AmbientLight(spotLight[i].color);
        diffuseColor += DiffuseSpotLight(outNormal, outWorldPos, spotLight[i]);
        specularColor += SpecularSpotLight(outNormal, outWorldPos, CameraPos, spotLight[i], material);
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