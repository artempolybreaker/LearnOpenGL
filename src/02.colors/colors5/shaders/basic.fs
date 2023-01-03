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
   float cutoff; // for spotlight
   float outerCutoff; // for spotlight
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

   vec3 diffuse = vec3(0.0);
   vec3 spec = vec3(0.0);
   vec3 emission = vec3(0.0);
   
   // ambient
   vec3 ambient = light.ambient * diffuseTexColor;
   
   // spotlight
   vec3 toLight = normalize(light.positionVS - posVS);
   float theta = dot(toLight, normalize(-light.dirVS));
   float epsilon = light.cutoff - light.outerCutoff;
   float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
   
   // diffuse
   vec3 normVS = normalize(normalVS);
   float diff = max(dot(toLight, normVS), 0.0);
   diffuse = light.diffuse * (diff * diffuseTexColor);

   // specular
   vec3 viewDir = normalize(-posVS);
   vec3 reflectDir = reflect(-toLight, normVS);
   float sp = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   spec = light.specular * (sp * specularTexColor);

   // emission
   emission = vec3(0.0);//emissionTexColor * floor(1 - specularTexColor);

   // attenuation
   float distToLight = length(light.positionVS - posVS);
   float att = 1.0 / (light.pointLightConsts.r + light.pointLightConsts.g * distToLight + light.pointLightConsts.b * (distToLight * distToLight));
   ambient *= att;
   diffuse *= att * intensity;
   spec *= att * intensity;

   vec3 result = (ambient + diffuse + spec + emission);
   FragColor = vec4(result, 1.0);
}