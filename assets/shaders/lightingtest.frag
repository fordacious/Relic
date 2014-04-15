#define NUM_LIGHTS 10

// Could probably optimise all these so less lookups 
uniform vec3  lightColours[NUM_LIGHTS];
uniform vec3  lightPositions[NUM_LIGHTS];
uniform float lightIntensities[NUM_LIGHTS];

uniform vec3 ambient;
uniform vec3 lightFalloffs[NUM_LIGHTS];

uniform sampler2D diffuseTexture;
uniform sampler2D heightTexture;
uniform sampler2D normalTexture;

uniform vec2 resolution;

uniform int numLights;

void main(void)
{

	gl_FragColor = vec4(0.0,0.0,0.0,0.0);
	vec4 color;

	int i;
	for (i=0;i<numLights;i++) {	
		vec2 fc = gl_FragCoord.xy;
		vec2 coord      = ( fc.xy / resolution.xy );
		//vec3 position3D = vec3(coord, 0.90);
		vec3 position3D = vec3(coord, ((texture2D(heightTexture, coord).r - 1.0) / 10.0 ));

	    color     = texture2D(diffuseTexture, coord);
	    vec4 normalTex = texture2D(normalTexture, coord);
	    vec3 normalVec = normalTex.rgb;

	    vec3 lp = lightPositions[i];

	    vec3 LightDir = lp - position3D;
	    float D = length(LightDir);
	   
	    //normalize our vectors
	    vec3 N = normalize(normalTex.rgb * 2.0 - 1.0);
	    vec3 L = normalize(LightDir);
	   
	    //Pre-multiply light color with intensity
	    //Then perform "N dot L" to determine our diffuse term
	    vec3 Diffuse = (lightColours[i].rgb * lightIntensities[i]) * max(dot(N, L), 0.0);

	    //pre-multiply ambient color with intensity
	   
	    //calculate attenuation
	    float Attenuation = lightIntensities[i] / ( lightFalloffs[i].x + (lightFalloffs[i].y*D) + (lightFalloffs[i].z*D*D) );
	    //float Attenuation = lightIntensities[i] / (D*D);

	    Attenuation = min(1.0, Attenuation);
	   
	    //the calculation which brings it all together
	    vec3 Intensity = ambient + Diffuse * Attenuation;
	    vec3 FinalColor = color.rgb * Intensity;

	    gl_FragColor.r += max(gl_FragColor.r, FinalColor.r);
	    gl_FragColor.g += max(gl_FragColor.g, FinalColor.g);
	    gl_FragColor.b += max(gl_FragColor.b, FinalColor.b);
    }
    gl_FragColor.rgb = min(vec3(1.0,1.0,1.0), gl_FragColor.rgb);
    gl_FragColor.a = color.a;
}

