#version 330 core
uniform vec4 myColor;

in vec3 color;
out vec4 FragColor;

void main()
{
//   FragColor = vec4(myColor.xyz, 1.0f);
   FragColor = vec4(color.xyz * myColor.xyz, 1.0f);
}