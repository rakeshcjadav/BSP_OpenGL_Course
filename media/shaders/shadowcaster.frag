#version 330 core

uniform sampler2D DiffuseMap;

in struct VS_OUT
{
    vec2 outTexCoord;
}fs_in;

void main()
{
    gl_FragDepth = gl_FragCoord.z;// * texture(DiffuseMap, fs_in.outTexCoord).a;
}