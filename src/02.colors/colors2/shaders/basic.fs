#version 330 core

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

// interpolated values from VS
in vec2 uv;
in vec3 normalVS;
in vec3 posVS;
in vec3 lightPosVS;
// in vec3 worldViewPos;

// uniform inputs
uniform Material material;
// uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 worldViewPos;

// uniform float ambientStrength;
// uniform float diffuseStrength;
// uniform float specularStrength;
// uniform float specularFactor;


// FS output
out vec4 FragColor;

void main()
{
   // ambient
   vec3 ambient = lightColor * material.ambient;
   
   // diffuse
   vec3 normVS = normalize(normalVS);
   vec3 toLight = normalize(lightPosVS - posVS);
   float diff = max(dot(toLight, normVS), 0.0);
   vec3 diffuse = lightColor * (diff * material.diffuse);

   // specular
   vec3 viewDir = normalize(-posVS);
   vec3 reflectDir = reflect(-toLight, normVS);
   float sp = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 spec = lightColor * (sp * material.specular);

   vec3 result = (ambient + diffuse + spec);
   FragColor = vec4(result, 1.0);
}