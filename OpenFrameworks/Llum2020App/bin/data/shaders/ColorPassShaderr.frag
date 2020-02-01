#version 120

uniform sampler2DRect tex0;

varying vec2 texCoordVarying;

void main()
{
    vec4 tex = texture2DRect(tex0, texCoordVarying);
    gl_FragColor = vec4(color.rgb, tex.a);
}