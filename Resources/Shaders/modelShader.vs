precision mediump float;
attribute vec3 a_posL;
attribute vec3 a_colour;
varying vec3 v_colour;
uniform mat4 u_MVP;
varying vec2 v_uv;
varying vec4 fragPos;
uniform mat4 modelMatrix;
attribute vec3 a_norm;
varying vec3 objectNorm;
attribute vec2 a_uv;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
v_colour=a_colour;
fragPos=modelMatrix*posL;
objectNorm=(modelMatrix*vec4(a_norm,0.0)).xyz;
v_uv=a_uv;
posL=u_MVP*posL;
gl_Position = posL;
}
   