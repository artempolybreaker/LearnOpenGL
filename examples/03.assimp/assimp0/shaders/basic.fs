#version 330 core

in vec2 uv;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
// uniform sampler2D texture1;

void main()
{
   FragColor = vec4(1.0, 0.0, 0.0, 1.0);
   // FragColor = mix(texture(texture1, uv), texture(texture2, uv), t);
   // FragColor = texture(texture1, uv);
}