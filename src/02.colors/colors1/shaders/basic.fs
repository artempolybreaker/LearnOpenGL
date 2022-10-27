#version 330 core

// interpolated values from VS
in vec2 uv;
in vec3 worldNormal;
in vec3 worldPos;
// in vec3 worldViewPos;

// uniform inputs
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 worldViewPos;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float specularFactor;


// FS output
out vec4 FragColor;

void main()
{
   // ambient
   vec3 ambient = lightColor * ambientStrength;
   
   // diffuse
   vec3 toLight = normalize(lightPos - worldPos);
   float diff = max(dot(toLight, worldNormal), 0.0);
   vec3 diffuse = lightColor * diffuseStrength * diff;

   // specular
   vec3 viewDir = normalize(worldViewPos - worldPos);
   vec3 reflectDir = reflect(-toLight, worldNormal);
   float sp = pow(max(dot(viewDir, reflectDir), 0.0), specularFactor);
   vec3 spec = lightColor * specularStrength * sp;

   vec3 result = (ambient + diffuse + spec) * objectColor;
   FragColor = vec4(result, 1.0);
}