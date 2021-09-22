#version 330 core

//
struct PointLight
{
    vec3 position;
    vec3 color;
    vec3 attenuation;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 color;
};

struct Material {
    vec3 uAmbientColor;
    vec3 uDiffuseColor;
    vec3 uSpecularColor;
    float uSpecularStrength;
    float uShininess;
}; 
//

in vec3 outWorldPos;
in vec3 outNormal;
in vec2 outTexCoord;

uniform sampler2D MainTex;
uniform vec3 CameraPos;
uniform PointLight pointLight;
uniform DirectionalLight directionalLight;
uniform Material material;

out vec4 FragColor;

vec3 AmbientLight(vec3 lightColor)
{
    float ambientStrength = 0.05;
    return ambientStrength * lightColor;
}

vec3 DiffuseDirectionalLight(vec3 normal, vec3 lightDirection, vec3 lightColor)
{
    float fDiffuse = max(dot(normal, lightDirection), 0.0f);
    return vec3(fDiffuse) * lightColor;
}

vec3 DiffuseLight(vec3 normal, vec3 lightPos, vec3 worldPos, vec3 lightColor, vec3 atten)
{
    vec3 lightDirection = normalize(lightPos - worldPos);
    vec3 diffuseColor = DiffuseDirectionalLight(normal, lightDirection, lightColor);

    float fDist = distance(lightPos, worldPos);
    float fAttenuation = 1.0f/(atten.x + atten.y*fDist + atten.z*fDist*fDist);
    return diffuseColor * fAttenuation;
}

vec3 SpecularDirectionalLight(vec3 normal, vec3 lightDirection, vec3 worldPos, vec3 cameraPos, vec3 lightColor)
{
    vec3 reflectDirection = reflect(-lightDirection, normal);

    vec3 cameraDirection = normalize(cameraPos - worldPos);
    float fSpectular = pow(max(dot(reflectDirection, cameraDirection), 0.0f), material.uSpecularStrength);

    return fSpectular * lightColor * material.uShininess;
}

vec3 SpecularLight(vec3 normal, vec3 lightPos, vec3 worldPos, vec3 cameraPos, vec3 lightColor)
{
    vec3 lightDirection = normalize(lightPos - worldPos);
    return SpecularDirectionalLight(normal, lightDirection, worldPos, cameraPos, lightColor);
}

void ApplyPointLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
     ambientColor += AmbientLight(pointLight.color);
     diffuseColor += DiffuseLight(outNormal, pointLight.position, outWorldPos, pointLight.color, pointLight.attenuation);
     specularColor += SpecularLight(outNormal, pointLight.position, outWorldPos, CameraPos, pointLight.color);
}

void ApplyDirectionalLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    ambientColor += AmbientLight(directionalLight.color);
    diffuseColor += DiffuseDirectionalLight(outNormal, -directionalLight.direction, directionalLight.color);
    specularColor += SpecularDirectionalLight(outNormal, -directionalLight.direction, outWorldPos, CameraPos, directionalLight.color);
}


void main()
{
    vec3 ambientColor = vec3(0.0f);
    vec3 diffuseColor = vec3(0.0f);
    vec3 specularColor = vec3(0.0f);
    ApplyDirectionalLights(ambientColor, diffuseColor, specularColor);
    ApplyPointLights(ambientColor, diffuseColor, specularColor);

    ambientColor *= material.uAmbientColor;
    diffuseColor *= material.uDiffuseColor;
    specularColor *= material.uSpecularColor;

    vec3 final = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(final, 1.0f);
}