#version 120

uniform vec4 iColor = vec4(1.0,1.0,1.0, 1.0);
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform float parameter = 1.0;
uniform float colorAmount = 0.0;


void main()
{
     // Normalized pixel coordinates (from 0 to 1)
	vec2 uv= gl_FragCoord.xy/iResolution.xy;
    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(sin(iGlobalTime/2.)+uv.xyx+vec3(0,2,41));

    // Output to screen
    gl_FragColor = vec4(col,iColor.a );
}