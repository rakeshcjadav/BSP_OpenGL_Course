//? #version 330 core
#define MAX_LIGHTS 8

// Input Struct
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

const float PARALLAX_HEIGHT_SCALE = 0.02f;
float near = 0.1; 
float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

float Depth(float depth)
{
    return LinearizeDepth(depth)/far;
}

// Lighting
vec3 AmbientLight(vec3 lightColor)
{
    float ambientStrength = 0.02f;
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
    vec3 lightDirection = normalize(light.position - worldPos);
    return vec3(DiffuseComponent(normal, lightDirection)) * CalcAttenuation(worldPos, light.position, light.attenuation) * light.color;
}

vec3 DiffuseSpotLight(vec3 normal, vec3 worldPos, SpotLight light)
{
    // Fragment light direction
    vec3 lightDirection = normalize(light.position - worldPos);
    return DiffuseComponent(normal, lightDirection) * CalcAttenuation(worldPos, light.position, light.attenuation) * SpotLightIntensity(lightDirection, light) * light.color;
}

float SpecularComponent(vec3 normal, vec3 lightDirection, vec3 worldPos, vec3 cameraPos, Material material)
{
    vec3 reflectDirection = reflect(-lightDirection, normal);

    vec3 cameraDirection = normalize(cameraPos - worldPos);
    float fSpectular = pow(max(dot(reflectDirection, cameraDirection), 0.0), material.uSpecularStrength);

    return fSpectular * material.uShininess;
}

float SpecularComponentBlinnPong(vec3 normal, vec3 lightDirection, vec3 worldPos, vec3 cameraPos, Material material)
{
    vec3 cameraDirection = normalize(cameraPos - worldPos);
    vec3 halfVector = normalize(lightDirection + cameraDirection);
    float fSpectular = 0.0f;
    if(material.uSpecularStrength > 0.0)
        fSpectular= pow(max(dot(normal, halfVector), 0.0), material.uSpecularStrength);
    return fSpectular * material.uShininess;
}

vec3 SpecularDirectionalLight(vec3 normal, vec3 worldPos, vec3 cameraPos, DirectionalLight light, Material material)
{
    return SpecularComponentBlinnPong(normal, -light.direction, worldPos, cameraPos, material) * light.color;
}

vec3 SpecularPointLight(vec3 normal, vec3 worldPos, vec3 cameraPos, PointLight light, Material material)
{
    vec3 lightDirection = normalize(light.position - worldPos);
    return SpecularComponentBlinnPong(normal, lightDirection, worldPos, cameraPos, material)
        * CalcAttenuation(worldPos, light.position, light.attenuation)
        * material.uSpecularColor
        * light.color;
}

vec3 SpecularSpotLight(vec3 normal, vec3 worldPos, vec3 cameraPos, SpotLight light, Material material)
{
    vec3 lightDirection = normalize(light.position - worldPos);
    return SpecularComponentBlinnPong(normal, lightDirection, worldPos, cameraPos, material)
        * CalcAttenuation(worldPos, light.position, light.attenuation)
        * SpotLightIntensity(lightDirection, light)
        * material.uSpecularColor
        * light.color;
}

float ShadowCalculation(sampler2D shadowTex, vec4 fragPosLightSpace, float fDiffuse)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowTex, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    float bias = max(0.05 * (1.0f - fDiffuse), 0.005);
    // check whether current frag pos is in shadow
    float shadow = currentDepth < (closestDepth + bias) ? 1.0 : 0.0;

    return shadow;
}