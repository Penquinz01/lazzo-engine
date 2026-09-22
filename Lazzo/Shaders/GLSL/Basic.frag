#version 460 core

out vec4 FragColor;

in vec3 v_Normal;
in vec3 v_FragPos;
in vec2 v_TexCoord;

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

// Texture maps. Each *_Enabled flag is the "is not null" check:
// GLSL has no way to query whether a sampler is bound, so the CPU
// sets the flag to true only after uploading the matching texture.
// Maps are simply skipped when the flag is false.
uniform bool u_UseAlbedoMap;
uniform sampler2D u_AlbedoMap;

uniform bool u_UseNormalMap;
uniform sampler2D u_NormalMap;

uniform bool u_UseSpecularMap;
uniform sampler2D u_SpecularMap;

uniform bool u_UseRoughnessMap;
uniform sampler2D u_RoughnessMap;

uniform bool u_UseAOMap;
uniform sampler2D u_AOMap;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 baseColor, float specStrength, float shininess, float ao)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfDir), 0.0), shininess);
    vec3 ambient = 0.15 * light.color * ao;
    vec3 diffuse = diff * light.color * light.intensity;
    vec3 specular = spec * light.color * light.intensity * specStrength;
    return (ambient + diffuse + specular) * baseColor;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 baseColor, float specStrength, float shininess, float ao)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfDir), 0.0), shininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 ambient = 0.15 * light.color * ao * attenuation;
    vec3 diffuse = diff * light.color * light.intensity * attenuation;
    vec3 specular = spec * light.color * light.intensity * attenuation * specStrength;
    return (ambient + diffuse + specular) * baseColor;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 baseColor, float specStrength, float shininess, float ao)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfDir), 0.0), shininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutoff - light.outerCutoff;
    float spotIntensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
    vec3 ambient = 0.15 * light.color * ao * attenuation;
    vec3 diffuse = diff * light.color * light.intensity * attenuation * spotIntensity;
    vec3 specular = spec * light.color * light.intensity * attenuation * spotIntensity * specStrength;
    return (ambient + diffuse + specular) * baseColor;
}

void main()
{
    vec3 norm = normalize(v_Normal);

    if (u_UseNormalMap)
    {
        vec3 tangentNormal = texture(u_NormalMap, v_TexCoord).rgb * 2.0 - 1.0;

        vec3 dp1 = dFdx(v_FragPos);
        vec3 dp2 = dFdy(v_FragPos);
        vec2 duv1 = dFdx(v_TexCoord);
        vec2 duv2 = dFdy(v_TexCoord);

        float r = 1.0 / (duv1.x * duv2.y - duv2.x * duv1.y);
        vec3 T = (dp1 * duv2.y - dp2 * duv1.y) * r;
        vec3 B = (dp2 * duv1.x - dp1 * duv2.x) * r;

        T = normalize(T - dot(T, norm) * norm);
        B = normalize(B - dot(B, norm) * norm - dot(B, T) * T);

        norm = normalize(mat3(T, B, norm) * tangentNormal);
    }

    vec3 baseColor = u_Color;
    if (u_UseAlbedoMap)
        baseColor *= texture(u_AlbedoMap, v_TexCoord).rgb;

    float specStrength = 1.0;
    if (u_UseSpecularMap)
        specStrength = texture(u_SpecularMap, v_TexCoord).r;

    float shininess = 32.0;
    if (u_UseRoughnessMap)
        shininess = mix(256.0, 1.0, clamp(texture(u_RoughnessMap, v_TexCoord).r, 0.0, 1.0));

    float ao = 1.0;
    if (u_UseAOMap)
        ao = texture(u_AOMap, v_TexCoord).r;

    vec3 viewDir = normalize(u_ViewPos - v_FragPos);

    vec3 result = CalcDirLight(u_DirLight, norm, viewDir, baseColor, specStrength, shininess, ao);

    for (int i = 0; i < u_NumPointLights; i++)
        result += CalcPointLight(u_PointLights[i], norm, v_FragPos, viewDir, baseColor, specStrength, shininess, ao);

    for (int i = 0; i < u_NumSpotLights; i++)
        result += CalcSpotLight(u_SpotLights[i], norm, v_FragPos, viewDir, baseColor, specStrength, shininess, ao);

    FragColor = vec4(result, 1.0);
}