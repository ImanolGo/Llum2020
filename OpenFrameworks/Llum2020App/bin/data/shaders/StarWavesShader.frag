#version 120

//Based on random tripness by aji: https://www.shadertoy.com/view/lslGRj

uniform vec4 iColor = vec4(1.0,1.0,1.0, 1.0);
uniform vec3 iResolution;
uniform float iGlobalTime;
uniform float parameter = 1.0;
uniform float colorAmount = 0.0;


vec4 hue(float rad)
{
	rad /= 2.0;
	return vec4(abs(cos(rad)), abs(cos(rad+1.05)),
		abs(cos(rad+2.09)), 1.0);
}

vec4 gradient(float f)
{
	f = mod(f, 1.0) * 3.14;
	return vec4(sin(f) * sin(f));
}

float offset(float th)
{
	float mt = mod(iGlobalTime, 4.0);
	float x = sin(iGlobalTime + th) + sin(iGlobalTime + 2.0 * th)
		+ .3 * cos(iGlobalTime + 8.0 * th);
	return x + .2 * sin(10.0 * iGlobalTime + 20.0 * th);
}

vec4 tunnel(float th, float radius)
{
	return gradient(offset(th) + log(6.0 * radius));
}

void main()
{
    vec2 uv = gl_FragCoord.xy / iResolution.x +
    vec2(-.5, -.5 * iResolution.y / iResolution.x);
    // Time varying pixel color
    vec4 col = tunnel(atan(uv.y, uv.x), 2.0 * length(uv));

    // Output to screen
    gl_FragColor = vec4(col.rgb,iColor.a );
}