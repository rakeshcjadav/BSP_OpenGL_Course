#version 330 core
#include "common.frag"

in vec3 outWorldPos;
in vec3 outNormal;
in vec2 outTexCoord;

uniform sampler2D MainTex;
uniform sampler2D SecondTex;
uniform vec3 CameraPos;
uniform PointLight pointLight;
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;
uniform Material material;

out vec4 FragColor;

void ApplyPointLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
     ambientColor += AmbientLight(pointLight.color);
     diffuseColor += DiffusePointLight(outNormal, outWorldPos, pointLight);
     specularColor += SpecularPointLight(outNormal, outWorldPos, CameraPos, pointLight, material);
}

void ApplyDirectionalLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    ambientColor += AmbientLight(directionalLight.color);
    diffuseColor += DiffuseDirectionalLight(outNormal, directionalLight);
    specularColor += SpecularDirectionalLight(outNormal, outWorldPos, CameraPos, directionalLight, material);
}

void ApplySpotLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    ambientColor += AmbientLight(spotLight.color);
    diffuseColor += DiffuseSpotLight(outNormal, outWorldPos, spotLight);
    specularColor += SpecularSpotLight(outNormal, outWorldPos, CameraPos, spotLight, material);
}

void main()
{
    vec3 ambientColor = vec3(0.0f);
    vec3 diffuseColor = vec3(0.0f);
    vec3 specularColor = vec3(0.0f);
    ApplyDirectionalLights(ambientColor, diffuseColor, specularColor);
    ApplyPointLights(ambientColor, diffuseColor, specularColor);
    ApplySpotLights(ambientColor, diffuseColor, specularColor);

    ambientColor *= material.uAmbientColor;
    diffuseColor *= material.uDiffuseColor;
    specularColor *= material.uSpecularColor;

    vec3 final = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(final, 1.0f);
}