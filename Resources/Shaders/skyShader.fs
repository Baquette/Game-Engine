precision mediump float;
varying vec3 v_colour;
varying vec2 v_uv;
varying vec3 v_coord;
uniform samplerCube u_texture;
 
uniform vec3 cameraPos;
void main()
{
 
 
	vec4 culoare=textureCube(u_texture,v_coord);
 
	gl_FragColor=culoare;
}
