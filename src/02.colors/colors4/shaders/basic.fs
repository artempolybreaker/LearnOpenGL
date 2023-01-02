#version 330 core

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   sampler2D emission;
   float shininess;
};

struct Light {
   vec3 positionVS;
   vec3 dirVS;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   vec3 pointLightConsts; // r = constant, g = linear, b = quadratic
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
   vec3 diffuseTexColor = vec3(texture(material.diffuse, uv));
   vec3 specularTexColor = vec3(texture(material.specular, uv));
   vec3 emissionTexColor = vec3(texture(material.emission, uv));

   // ambient
   vec3 ambient = light.ambient * diffuseTexColor;
   
   // diffuse
   // vec3 toLight = normalize(-light.dirVS);
   vec3 toLight = normalize(light.positionVS - posVS);
   vec3 normVS = normalize(normalVS);
   float diff = max(dot(toLight, normVS), 0.0);
   vec3 diffuse = light.diffuse * (diff * diffuseTexColor);

   // specular
   vec3 viewDir = normalize(-posVS);
   vec3 reflectDir = reflect(-toLight, normVS);
   float sp = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 spec = light.specular * (sp * specularTexColor);

   // emission
   vec3 emission = vec3(0.0);//emissionTexColor * floor(1 - specularTexColor);

   // attenuation
   float distToLight = length(light.positionVS - posVS);
   float att = 1.0 / (light.pointLightConsts.r + light.pointLightConsts.g * distToLight + light.pointLightConsts.b * (distToLight * distToLight));
   ambient *= att;
   diffuse *= att;
   spec *= att;

   vec3 result = (ambient + diffuse + spec + emission);
   FragColor = vec4(result, 1.0);
}