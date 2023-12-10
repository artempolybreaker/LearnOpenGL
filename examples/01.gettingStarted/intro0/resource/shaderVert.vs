#version 330 core
uniform vec2 offset;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 color;

void main() {
   color = vec3(aCol);
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) + vec4(offset, 0, 0);
}