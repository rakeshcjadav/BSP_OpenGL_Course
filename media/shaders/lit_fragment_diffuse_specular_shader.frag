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

struct SpotLight
{
    vec3 position;
    vec3 direction;
    vec3 color;
    vec3 attenuation;
    float innerAngle;
    float outerAngle;
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

uniform sampler2D DiffuseTex;
uniform sampler2D SpecularTex;
uniform vec3 CameraPos;
uniform PointLight pointLight;
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;
uniform Material material;

out vec4 FragColor;

vec3 AmbientLight(vec3 lightColor)
{
    float ambientStrength = 0.1;
    return ambientStrength * lightColor;
}

float CalcAttenuation(vec3 worldPos, vec3 lightPos, vec3 atten)
{
    float fDist = distance(lightPos, worldPos);
    return 1.0f/(atten.x + atten.y*fDist + atten.z*fDist*fDist);
}

float SpotLightIntensity(vec3 fragmentlightDirection, SpotLight light)
{
    float angle = dot(fragmentlightDirection, -light.direction);
    if(angle < light.outerAngle)
    {
        return 0.0f;
    }
    float diff = light.innerAngle - light.outerAngle;
    float intensity = clamp((angle - light.outerAngle)/diff, 0.0f, 1.0f);
    return intensity;
}

float DiffuseComponent(vec3 normal, vec3 lightDirection)
{
    return max(dot(normal, lightDirection), 0.0f);
}

vec3 DiffuseDirectionalLight(vec3 normal, DirectionalLight light)
{
    return DiffuseComponent(normal, -light.direction) * light.color;
}

vec3 DiffusePointLight(vec3 normal, vec3 worldPos, PointLight light)
{
    vec3 lightDirection = normalize(light.position- worldPos);
    return DiffuseComponent(normal, lightDirection) * CalcAttenuation(worldPos, light.position, light.attenuation) * light.color;
}

vec3 DiffuseSpotLight(vec3 normal, vec3 worldPos, SpotLight light)
{
    // Fragment light direction
    vec3 lightDirection = normalize(light.position - worldPos);
    return CalcAttenuation(worldPos, light.position, light.attenuation) * SpotLightIntensity(lightDirection, light) * light.color;
}

float SpecularComponent(vec3 normal, vec3 lightDirection, vec3 worldPos, vec3 cameraPos)
{
    vec3 reflectDirection = reflect(-lightDirection, normal);

    vec3 cameraDirection = normalize(cameraPos - worldPos);
    float fSpectular = pow(max(dot(reflectDirection, cameraDirection), 0.0f), material.uSpecularStrength);

    return fSpectular * material.uShininess;
}

vec3 SpecularDirectionalLight(vec3 normal, vec3 worldPos, vec3 cameraPos, DirectionalLight light)
{
    return SpecularComponent(normal, -light.direction, worldPos, cameraPos) * light.color;
}

vec3 SpecularPointLight(vec3 normal, vec3 worldPos, vec3 cameraPos, PointLight light)
{
    vec3 lightDirection = normalize(light.position - worldPos);
    return SpecularComponent(normal, lightDirection, worldPos, cameraPos)
        * CalcAttenuation(worldPos, light.position, light.attenuation)
        * light.color;
}

vec3 SpecularSpotLight(vec3 normal, vec3 worldPos, vec3 cameraPos, SpotLight light)
{
    vec3 lightDirection = normalize(light.position - worldPos);
    return SpecularComponent(normal, lightDirection, worldPos, cameraPos)
        * CalcAttenuation(worldPos, light.position, light.attenuation)
        * SpotLightIntensity(lightDirection, light)
        * light.color;
}

void ApplyPointLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
     ambientColor += AmbientLight(pointLight.color);
     diffuseColor += DiffusePointLight(outNormal, outWorldPos, pointLight);
     specularColor += SpecularPointLight(outNormal, outWorldPos, CameraPos, pointLight);
}

void ApplyDirectionalLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    ambientColor += AmbientLight(directionalLight.color);
    diffuseColor += DiffuseDirectionalLight(outNormal, directionalLight);
    specularColor += SpecularDirectionalLight(outNormal, outWorldPos, CameraPos, directionalLight);
}

void ApplySpotLights(inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    ambientColor += AmbientLight(spotLight.color);
    diffuseColor += DiffuseSpotLight(outNormal, outWorldPos, spotLight);
    specularColor += SpecularSpotLight(outNormal, outWorldPos, CameraPos, spotLight);
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

    vec3 final = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(final, 1.0f);
}