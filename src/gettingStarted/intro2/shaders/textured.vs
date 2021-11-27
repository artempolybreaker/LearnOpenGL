#version 330 core
uniform vec2 offset;
uniform mat4 transform;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;

out vec3 color;
out vec2 uv;

void main()
{
   color = aCol;
   uv = aUV;
   gl_Position = transform * vec4(aPos, 1);// + vec4(offset, 0, 0);
}