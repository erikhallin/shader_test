#version 120

varying vec4 pcolor;

void main()
{
  gl_FragColor = pcolor;
  //gl_FragColor = vec4(1,0,0,1);
}