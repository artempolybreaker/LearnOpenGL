#version 330 core
#define POINT_LIGHTS 4

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   sampler2D emission;
   float shininess;
};

struct DirLight {
   vec3 dirVS;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct PointLight {
   vec3 posVS;

   vec3 pointLightConsts; // r = constant, g = linear, b = quadratic

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct SpotLight {
   vec3 positionVS;
   vec3 dirVS;

   vec3 pointLightConsts; // r = constant, g = linear, b = quadratic

   float cutoff; // for spotlight
   float outerCutoff; // for spotlight

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
uniform DirLight dirLight;
uniform PointLight pointLights[POINT_LIGHTS];
uniform SpotLight spotLight;


// FS output
out vec4 FragColor;

vec3 calcDirLight(DirLight light, vec3 normalVS, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normalVS, vec3 fragPosVS, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normalVS, vec3 fragPosVS, vec3 viewDir);

void main()
{
   // properties
   vec3 normalVS = normalize(normalVS);
   vec3 viewDir = normalize(-posVS);

   // dir light
   vec3 result = calcDirLight(dirLight, normalVS, viewDir);
   // point lights
   for (int i = 0; i < POINT_LIGHTS; i++) {
      // lazy init
      vec3 pos = pointLights[i].posVS;
      vec3 pointLightConsts = pointLights[0].pointLightConsts;
      vec3 ambient = pointLights[0].ambient;
      vec3 diffuse = pointLights[0].diffuse;
      vec3 specular = pointLights[0].specular;

      PointLight pl = PointLight(pos, pointLightConsts, ambient, diffuse, specular);

      result += calcPointLight(pl, normalVS, posVS, viewDir);
   }
   // spot light
   result += calcSpotLight(spotLight, normalVS, posVS, viewDir);
   result = clamp(result, 0.0, 1.0);

   FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normalVS, vec3 viewDir) {
   vec3 toLight = normalize(-light.dirVS);

   // diffuse
   float diff = max(dot(toLight, normalVS), 0.0);

   // specular
   vec3 reflectDir = reflect(-toLight, normalVS);
   float sp = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   
   // combine
   vec3 diffuseTexColor = vec3(texture(material.diffuse, uv));
   vec3 specularTexColor = vec3(texture(material.specular, uv));
   vec3 emissionTexColor = vec3(texture(material.emission, uv));

   vec3 ambient = light.ambient * diffuseTexColor;
   vec3 diffuse = light.diffuse * (diff * diffuseTexColor);
   vec3 spec = light.specular   * (sp * specularTexColor);

   return ambient + diffuse + spec;
}

vec3 calcPointLight(PointLight light, vec3 normalVS, vec3 fragPosVS, vec3 viewDir) {
   vec3 toLight = normalize(light.posVS - fragPosVS);

   // diffuse
   float diff = max(dot(toLight, normalVS), 0.0);

   // specular
   vec3 reflectDir = reflect(-toLight, normalVS);
   float sp = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);   

   // attenuation
   float distToLight = length(light.posVS - fragPosVS);
   float att = 1.0 / (light.pointLightConsts.r + light.pointLightConsts.g * distToLight + light.pointLightConsts.b * (distToLight * distToLight));

   // combine
   vec3 diffuseTexColor  = vec3(texture(material.diffuse, uv));
   vec3 specularTexColor = vec3(texture(material.specular, uv));
   vec3 emissionTexColor = vec3(texture(material.emission, uv));

   vec3 ambient = light.ambient  * diffuseTexColor;
   vec3 diffuse = light.diffuse  * (diff * diffuseTexColor);
   vec3 spec    = light.specular * (sp * specularTexColor);

   ambient *= att;
   diffuse *= att;
   spec    *= att;

   return ambient + diffuse + spec;
}

vec3 calcSpotLight(SpotLight light, vec3 normalVS, vec3 fragPosVS, vec3 viewDir) {
   vec3 toLight = normalize(light.positionVS - fragPosVS);
   float theta = dot(toLight, normalize(-light.dirVS));
   float epsilon = light.cutoff - light.outerCutoff;
   float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

   // diffuse
   float diff = max(dot(toLight, normalVS), 0.0);

   // specular
   vec3 reflectDir = reflect(-toLight, normalVS);
   float sp = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);   

   // attenuation
   float distToLight = length(light.positionVS - fragPosVS);
   float att = 1.0 / (light.pointLightConsts.r + light.pointLightConsts.g * distToLight + light.pointLightConsts.b * (distToLight * distToLight));

   // combine
   vec3 diffuseTexColor  = vec3(texture(material.diffuse, uv));
   vec3 specularTexColor = vec3(texture(material.specular, uv));
   vec3 emissionTexColor = vec3(texture(material.emission, uv));

   vec3 ambient = light.ambient  * diffuseTexColor;
   vec3 diffuse = light.diffuse  * (diff * diffuseTexColor);
   vec3 spec    = light.specular * (sp * specularTexColor);

   ambient *= att;
   diffuse *= att * intensity;
   spec    *= att * intensity;

   return ambient + diffuse + spec;
}