#version 120

// based on shader by Bloksgaard/2014: https://www.shadertoy.com/view/4sS3Dc

#define PI 3.14159265358979

uniform vec4 iColor = vec4(1.0,1.0,1.0, 1.0);
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform float parameter = 1.0;
uniform float colorAmount = 0.0;



// Convert HSL colorspace to RGB. http://en.wikipedia.org/wiki/HSL_and_HSV
vec3 HSLtoRGB(in vec3 c)
{
	vec3 rgb = clamp(abs(mod(c.x+vec3(0.,4.,2.),6.)-3.)-1.,0.,1.);
	return c.z+c.y*(rgb-0.5)*(1.-abs(2.*c.z-1.));
}

vec3 HSL2RGB_CubicSmooth(in vec3 c)
{
    vec3 rgb = clamp(abs(mod(c.x+vec3(0.,4.,2.),6.)-3.)-1.,0.,1.);
    rgb = rgb*rgb*(3.0-2.0*rgb); // iq's cubic smoothing.
    return c.z+ c.y*(rgb-0.5)*(1.-abs(2.*c.z-1.));
}

void main()
{
	vec2 uv = (-1.+2.*gl_FragCoord.xy/iResolution.xy);
   

    float fAngle = iGlobalTime*0.4;
	float h = atan(uv.x,uv.y) - fAngle;
	float x = length(uv);
	float a = -(0.6+0.2*sin(iGlobalTime*3.1+sin((iGlobalTime*0.8+h*2.0)*3.0))*sin(iGlobalTime+h));
	float b = -(0.8+0.3*sin(iGlobalTime*1.7+sin((iGlobalTime+h*4.0))));
	float c = 1.25+sin((iGlobalTime+sin((iGlobalTime+h)*3.0))*1.3)*0.15;
	float l = a*x*x + b*x + c;
	vec3 col = HSLtoRGB(vec3(h*3./PI,1.,l));

    // Output to screen
    gl_FragColor = vec4(col.rgb,iColor.a );
}