#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec2 uv;
out vec3 worldNormal;
out vec3 worldPos;

void main()
{
   uv = aUV;
   worldNormal = normalize(vec3(model * vec4(aNormal, 1.0)));
   worldPos = vec3(model * vec4(aPos, 1.0));
   gl_Position = projection * view * model * vec4(aPos, 1.0);
}