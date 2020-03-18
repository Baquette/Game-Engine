precision mediump float;
attribute vec3 a_posL;
attribute vec3 a_colour;
varying vec3 v_colour;
 
uniform mat4 u_MVP;
varying vec3 v_coord;
varying vec2 v_uv;
attribute vec2 a_uv;
void main()
{

vec4 posL = vec4(a_posL, 1.0);
 
v_coord=a_posL; 
 v_uv=a_uv;
posL=u_MVP*posL;
gl_Position = posL;
}
   