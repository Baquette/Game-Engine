precision mediump float;
attribute vec3 a_posL;
attribute vec3 a_colour;
varying vec3 v_colour;
uniform mat4 u_MVP;
varying vec2 v_uv;
varying vec4 fogPos;
uniform mat4 modelMatrix;
attribute vec2 a_uv;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
v_colour=a_colour;
fogPos=modelMatrix*posL;
v_uv=a_uv;
posL=u_MVP*posL;
gl_Position = posL;
}
   