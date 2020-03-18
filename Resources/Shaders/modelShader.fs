precision mediump float;
varying vec3 v_colour;
varying vec2 v_uv;
varying vec4 fragPos;
uniform float fogSmallRadius;
uniform float fogBigRadius;
uniform vec3 fogColor;
uniform mat4 modelMatrix;
uniform vec3 cameraPos;
uniform sampler2D u_texture;
varying vec3 objectNorm;
uniform vec3 lightAmbientColor;
uniform vec3 lightDiffuseColor;
uniform vec3 lightDirection;
uniform float lightRatio;
uniform vec3 lightSpectralColor;
uniform float lightSpecPower;
void main()
{

	vec4 fogcol=vec4(fogColor,1.0);
	float d=distance(fragPos,vec4(cameraPos,1.0));
	float alpha=(clamp(d,fogSmallRadius,fogBigRadius)-fogSmallRadius)/(fogBigRadius-fogSmallRadius);
    vec4 color=texture2D(u_texture,v_uv);
	 if(color.a < 0.2)
	{
		discard;
	}
	color=alpha*fogcol+(1.0-alpha)*color;

	vec4 comp_amb=color*vec4(lightAmbientColor,1.0);
	vec4 cDiff=color*vec4(lightDiffuseColor,1.0)*max(dot(normalize(objectNorm),-normalize(lightDirection)),0.0);
	vec4 cSpec=vec4(lightSpectralColor,1.0)*pow(max(dot(normalize(reflect(lightDirection,objectNorm)),normalize(cameraPos-fragPos.xyz)),0.0),lightSpecPower);
	vec4 cfin=lightRatio*comp_amb+(1.0-lightRatio)*(cDiff+cSpec);
	cfin.a=color.a;
	
	gl_FragColor = cfin;
}
