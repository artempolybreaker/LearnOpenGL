#version 330 core
uniform vec2 offset;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;

out vec3 color;
out vec2 uv;

void main() 
{
   color = aCol;
   uv = aUV;
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);// + vec4(offset, 0, 0);
}