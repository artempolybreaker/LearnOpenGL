#version 330 core

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

struct Light {
   vec3 positionVS;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

// interpolated values from VS
in vec2 uv;
in vec3 normalVS;
in vec3 posVS;

// uniform inputs
uniform Material material;
uniform Light light;

// FS output
out vec4 FragColor;

void main()
{
   // ambient
   vec3 ambient = light.ambient * material.ambient;
   
   // diffuse
   vec3 normVS = normalize(normalVS);
   vec3 toLight = normalize(light.positionVS - posVS);
   float diff = max(dot(toLight, normVS), 0.0);
   vec3 diffuse = light.diffuse * (diff * material.diffuse);

   // specular
   vec3 viewDir = normalize(-posVS);
   vec3 reflectDir = reflect(-toLight, normVS);
   float sp = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 spec = light.specular * (sp * material.specular);

   vec3 result = (ambient + diffuse + spec);
   FragColor = vec4(result, 1.0);
}