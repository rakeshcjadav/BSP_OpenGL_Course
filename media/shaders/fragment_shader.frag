#version 330 core

in float value;
in vec4 outColor;
in vec2 outTexCoord;

uniform sampler2D MainTex;
uniform sampler2D SecondTex;
uniform float Scale;
uniform float SineTime;
uniform mat4 TransformMat;

out vec4 FragColor;

void Unity_PolarCoordinates_float(vec2 UV, vec2 Center,
    float RadialScale, float LengthScale, out vec2 Out) {
    vec2 delta = UV - Center;
    float radius = length(delta) * 2 * RadialScale;
    float angle = atan(delta.x, delta.y) * 1.0 / 6.28 * LengthScale;
    Out = vec2(radius, angle);
}

void main()
{
    vec2 uv = outTexCoord;
    //FragColor = texture(MainTex, uv);
    vec4 colorSecond = texture(SecondTex, uv);
    vec4 colorMain = texture(MainTex, uv);
    //FragColor = colorMain * colorMain.a + colorSecond * (1.0 - colorMain.a);

    float Dist = pow(1.0-distance(uv, vec2(0.5)),2);
    FragColor = vec4(Dist);
    Unity_PolarCoordinates_float(outTexCoord, vec2(0.5), 1.0, 1.0, uv);
    //FragColor = vec4(uv, 0.0f, 1.0f);
    if(uv.y < SineTime)
        FragColor = colorSecond;
    else
        FragColor = colorMain;
    //vec4 transformedUV = TransformMat * vec4(outTexCoord - vec2(0.5), 0.0f, 1.0f);
    //FragColor = texture(MainTex, transformedUV.xy);
    //FragColor = vec4(outTexCoord, 0.0f, 1.0f);
}