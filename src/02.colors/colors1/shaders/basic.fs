#version 330 core

// interpolated values from VS
in vec2 uv;
in vec3 worldNormal;
in vec3 worldPos;

// uniform inputs
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

// FS output
out vec4 FragColor;

void main()
{
   // ambient
   float ambientStrength = 0.1;
   vec3 ambient = lightColor * ambientStrength;
   
   // diffuse
   vec3 toLight = normalize(lightPos - worldPos);
   float diffuseStrength = 1.0;
   float diff = max(dot(toLight, worldNormal), 0.0);
   vec3 diffuse = lightColor * diff;

   vec3 result = objectColor * (ambient + diffuse);
   FragColor = vec4(result, 1.0);
}