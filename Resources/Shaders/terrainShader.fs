precision mediump float;
varying vec3 v_colour;
varying vec2 v_uv;
varying vec2 v_uv2;
uniform sampler2D u_texture;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform sampler2D u_texture4;
uniform sampler2D u_texture5;
varying vec4 fogPos;
uniform float fogSmallRadius;
uniform float fogBigRadius;
uniform vec3 fogColor;
uniform mat4 modelMatrix;
uniform vec3 cameraPos;
void main()
{
	vec4 cblend=texture2D(u_texture4,v_uv);
	vec4 crock=texture2D(u_texture2,v_uv2);
	vec4 cgrass=texture2D(u_texture3,v_uv2);
	vec4 cdirt=texture2D(u_texture,v_uv2);
	vec4 fogcol=vec4(fogColor,1.0);
    vec4 cfin=cblend.r*crock+cblend.g*cgrass+cblend.b*cdirt;
	float d=distance(fogPos,vec4(cameraPos,1.0));
	float alpha=(clamp(d,fogSmallRadius,fogBigRadius)-fogSmallRadius)/(fogBigRadius-fogSmallRadius);
	cfin.a=1.0;
	cfin=alpha*fogcol+(1.0-alpha)*cfin;
	gl_FragColor = cfin;
}
