#version 330 core

in vec2 uv;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
   float ambientStrength = 0.1f;
   vec3 ambient = lightColor * ambientStrength;

   vec3 result = objectColor * ambient;
   FragColor = vec4(result, 1.0);
}