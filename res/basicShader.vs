#version 120

attribute vec4 position;
attribute vec4 color;

varying vec4 pcolor;

void main()
{
  gl_Position = gl_ModelViewProjectionMatrix * position;
  //pcolor=vec4(1,0,0,1);
}