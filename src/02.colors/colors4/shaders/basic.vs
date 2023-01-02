#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec2 uv;
out vec3 normalVS;
out vec3 posVS;
// out vec3 worldViewPos;

void main()
{
   uv = aUV;
   normalVS = normalize(mat3(transpose(inverse(view * model))) * aNormal);
   posVS = vec3(view * model * vec4(aPos, 1.0));
   gl_Position = projection * view * model * vec4(aPos, 1.0);
}