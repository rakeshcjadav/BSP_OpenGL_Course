#version 330 core

uniform sampler2D DiffuseMap;

in VS_OUT
{
    vec2 outTexCoord;
}fs_in;

void main()
{
    if(texture(DiffuseMap, fs_in.outTexCoord).a < 0.5)
    {
        gl_FragDepth = 1.0;
    }
    else 
    {
        gl_FragDepth = gl_FragCoord.z;
    }

}