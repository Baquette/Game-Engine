precision mediump float;
varying vec3 v_colour;
varying vec2 v_uv;
varying vec4 fogPos;
uniform float fogSmallRadius;
uniform float fogBigRadius;
uniform vec3 fogColor;
uniform mat4 modelMatrix;
uniform vec3 cameraPos;
uniform sampler2D u_texture;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform float fireDispMax;
uniform float fireTime;
void main()
{
	 
	vec4 fogcol=vec4(fogColor,1.0);
	float d=distance(fogPos,vec4(cameraPos,1.0));
	float alpha=(clamp(d,fogSmallRadius,fogBigRadius)-fogSmallRadius)/(fogBigRadius-fogSmallRadius);


	vec2 disp=texture2D(u_texture,vec2(v_uv.x,v_uv.y+fireTime)).rg;
	vec2 offset=(disp*2.0-1.0)*fireDispMax;
	vec2 v_uv_displaced=v_uv+offset;
	vec4 c_fire=texture2D(u_texture2,v_uv_displaced);
	vec4 c_fire_mask=texture2D(u_texture3,v_uv); 
	
	c_fire.a=c_fire.a*c_fire_mask.r;
	vec4 cfin=c_fire;
	if(c_fire.a < 0.2)
	{
		discard;
	}
	cfin=alpha*fogcol+(1.0-alpha)*cfin;
	gl_FragColor =cfin;

}
