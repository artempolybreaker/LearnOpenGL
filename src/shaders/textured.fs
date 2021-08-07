#version 330 core
uniform vec4 myColor;
uniform float t;

in vec3 color;
in vec2 uv;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   //FragColor = vec4(color.xyz * myColor.xyz, 1.0f);
   // FragColor = mix(texture(texture1, uv), texture(texture2, uv), t);
   FragColor = mix(texture(texture1, uv), texture(texture2, uv), t);
}