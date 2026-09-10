#version 460 core

out vec4 FragColor;

in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_Color = vec3(0.20, 0.55, 0.95);
uniform vec3 u_ViewPos;

struct DirLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float innerCutoff;
    float outerCutoff;
    float constant;
    float linear;
    float quadratic;
};

#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4

uniform DirLight u_DirLight;
uniform int u_NumPointLights;
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];
uniform int u_NumSpotLights;
uniform SpotLight u_SpotLights[MAX_SPOT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 ambient = 0.15 * light.color;
    vec3 diffuse = diff * light.color * light.intensity;
    vec3 specular = spec * light.color * light.intensity;
    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 ambient = 0.15 * light.color * attenuation;
    vec3 diffuse = diff * light.color * light.intensity * attenuation;
    vec3 specular = spec * light.color * light.intensity * attenuation;
    return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutoff - light.outerCutoff;
    float spotIntensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
    vec3 ambient = 0.15 * light.color * attenuation;
    vec3 diffuse = diff * light.color * light.intensity * attenuation * spotIntensity;
    vec3 specular = spec * light.color * light.intensity * attenuation * spotIntensity;
    return ambient + diffuse + specular;
}

void main()
{
    vec3 norm = normalize(v_Normal);
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);

    vec3 result = CalcDirLight(u_DirLight, norm, viewDir);

    for (int i = 0; i < u_NumPointLights; i++)
        result += CalcPointLight(u_PointLights[i], norm, v_FragPos, viewDir);

    for (int i = 0; i < u_NumSpotLights; i++)
        result += CalcSpotLight(u_SpotLights[i], norm, v_FragPos, viewDir);

    FragColor = vec4(result * u_Color, 1.0);
}
