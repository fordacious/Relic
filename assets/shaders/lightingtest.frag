uniform vec3 lightCol;
uniform vec3 lightPos;
uniform float lightIntensity;

uniform vec3 ambient;
uniform vec3 falloff;

uniform sampler2D diffuseTexture;
uniform sampler2D heightTexture;
uniform sampler2D normalTexture;

uniform vec2 resolution;

void main(void)
{

	vec2 fc = gl_FragCoord.xy;
	vec2 coord      = ( fc.xy / resolution.xy );
	//vec3 position3D = vec3(coord, 0.90);
	vec3 position3D = vec3(coord, (texture2D(heightTexture, coord).r - 1.0));

    vec4 color     = texture2D(diffuseTexture, coord);
    vec4 normalTex = texture2D(normalTexture, coord);
    vec3 normalVec = normalTex.rgb;

    vec3 lp = lightPos;

    vec3 LightDir = lp - position3D;
    float D = length(LightDir);
   
    //normalize our vectors
    vec3 N = normalize(normalTex.rgb * 2.0 - 1.0);
    vec3 L = normalize(LightDir);
   
    //Pre-multiply light color with intensity
    //Then perform "N dot L" to determine our diffuse term
    vec3 Diffuse = (lightCol.rgb * lightIntensity) * max(dot(N, L), 0.0);

    //pre-multiply ambient color with intensity
   
    //calculate attenuation
    float Attenuation = lightIntensity / ( falloff.x + (falloff.y*D) + (falloff.z*D*D) );
    //float Attenuation = lightIntensity / (D*D);
   
    //the calculation which brings it all together
    vec3 Intensity = ambient + Diffuse * Attenuation;
    vec3 FinalColor = color.rgb * Intensity;
    gl_FragColor = vec4(FinalColor, color.a);
}

