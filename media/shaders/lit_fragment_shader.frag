#version 330 core

in vec3 outWorldPos;
in vec3 outNormal;
in vec2 outTexCoord;

uniform sampler2D MainTex;
uniform vec4 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPos;
uniform vec3 CameraPos;

struct Material {
    vec3 uAmbientColor;
    vec3 uDiffuseColor;
    vec3 uSpecularColor;
    float uShininess;
}; 
  
uniform Material material;


out vec4 FragColor;

vec3 AmbientLight(vec3 lightColor)
{
    float ambientStrength = 0.1;
    return ambientStrength * lightColor;
}

vec3 DiffuseLight(vec3 normal, vec3 lightPos, vec3 worldPos, vec3 lightColor)
{
    vec3 lightDirection = normalize(lightPos - worldPos);
    float fDiffuse = max(dot(normal, lightDirection), 0.0f);

    vec3 atten = vec3(1.0f, 0.05f, 0.001f);
    float fDist = distance(lightPos, worldPos);

    float fAttenuation = 1.0f/(atten.x + atten.y*fDist + atten.z*fDist*fDist);
    return vec3(fDiffuse) * fAttenuation * lightColor;
}

vec3 SpecularLight(vec3 normal, vec3 lightPos, vec3 worldPos, vec3 cameraPos, vec3 lightColor)
{
    vec3 lightDirection = normalize(lightPos - worldPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    vec3 cameraDirection = normalize(cameraPos - worldPos);
    float fSpectular = pow(max(dot(reflectDirection, cameraDirection), 0.0f), 5);

    return fSpectular * lightColor * material.uShininess;
}

void main()
{
    vec3 ambientColor = AmbientLight(LightColor) * material.uAmbientColor;
    vec3 diffuseColor  = DiffuseLight(outNormal, LightPos, outWorldPos, LightColor) * material.uDiffuseColor;
    vec3 specularColor = SpecularLight(outNormal, LightPos, outWorldPos, CameraPos, LightColor) * material.uSpecularColor;
    vec3 final = ambientColor + diffuseColor + specularColor;

    //vec4 objectColor = vec4(1.0f);//texture(MainTex, outTexCoord);

    FragColor = vec4(final, 1.0f);
}