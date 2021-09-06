#version 330 core

in vec3 outWorldPos;
in vec3 outNormal;
in vec2 outTexCoord;

uniform sampler2D MainTex;
uniform vec4 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPos;
uniform vec3 CameraPos;

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
    return fDiffuse * fAttenuation * lightColor;
}

vec3 SpecularLight(vec3 normal, vec3 lightPos, vec3 worldPos, vec3 cameraPos, vec3 lightColor)
{
    vec3 lightDirection = normalize(lightPos - worldPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    vec3 cameraDirection = normalize(cameraPos - worldPos);
    float fSpectular = pow(max(dot(reflectDirection, cameraDirection), 0.0f), 32);

    return fSpectular * lightColor;
}

void main()
{
    vec3 ambientColor = AmbientLight(LightColor);
    vec3 diffuseColor  = DiffuseLight(outNormal, LightPos, outWorldPos, LightColor);
    vec3 specularColor = SpecularLight(outNormal, LightPos, outWorldPos, CameraPos, LightColor);
    vec3 final = ambientColor + diffuseColor + specularColor;

    vec4 objectColor = texture(MainTex, outTexCoord);

    FragColor = objectColor * vec4(final, 1.0f);
}