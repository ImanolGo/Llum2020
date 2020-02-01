#version 120

uniform sampler2DRect tex0;
uniform sampler2DRect texGradient;

varying vec2 texCoordVarying;

float luma(vec3 color) {
  return dot(color, vec3(0.299, 0.587, 0.114));
}

float luma(vec4 color) {
  return dot(color.rgb, vec3(0.299, 0.587, 0.114));
}

void main()
{
    vec4 tex = texture2DRect(tex0, texCoordVarying);
    float brightness = luma(tex); 

    vec2 coord = vec2(brightness, 0.5);
    vec4 color = texture2DRect(texGradient, coord);

    gl_FragColor = vec4(color.rgb*brightness, tex.a);
}