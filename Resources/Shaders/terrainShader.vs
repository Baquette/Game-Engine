precision mediump float;
attribute vec3 a_posL;
attribute vec3 a_colour;
varying vec3 v_colour;
uniform mat4 u_MVP;
varying vec2 v_uv;
varying vec4 fogPos;
uniform mat4 modelMatrix;
attribute vec2 a_uv;
attribute vec2 a_uv2;
varying vec2 v_uv2;
uniform vec3 u_high;
uniform sampler2D u_texture4;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
fogPos=modelMatrix*posL;
vec4 cblend=texture2D(u_texture4,a_uv);
vec4 finalPos= posL;
finalPos.y=cblend.r*u_high.r+cblend.g*u_high.g+cblend.b*u_high.b;
v_uv=a_uv;
v_uv2=a_uv2;
posL=u_MVP*finalPos;
gl_Position = posL;
}
   