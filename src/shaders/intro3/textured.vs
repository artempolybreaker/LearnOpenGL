#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;

out vec3 color;
out vec2 uv;

void main()
{
   color = aCol;
   uv = aUV;
   gl_Position = projection * view * model * vec4(aPos, 1.0);
}