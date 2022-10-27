#version 330 core

// interpolated values from VS
in vec2 uv;
in vec3 worldNormal;
in vec3 worldPos;
in vec3 worldViewPos;

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
   float diffuseStrength = 1.0;
   vec3 toLight = normalize(lightPos - worldPos);
   float diff = max(dot(toLight, worldNormal), 0.0);
   vec3 diffuse = lightColor * diffuseStrength * diff;

   // specular
   float specularStrength = 0.5;
   vec3 toView = normalize(worldViewPos - worldPos);
   vec3 halfway = normalize(toLight + toView);
   float sp = pow(max(dot(worldNormal, halfway), 0.0), 512);
   vec3 spec = lightColor * specularStrength * sp;

   vec3 result = objectColor * (ambient + diffuse + spec);
   FragColor = vec4(result, 1.0);
}