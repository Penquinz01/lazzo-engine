#version 460 core

in vec3 v_Normal;

out vec4 FragColor;

void main()
{
    const vec3 lightDirection = normalize(vec3(0.4, 0.7, 1.0));
    const vec3 baseColor = vec3(0.20, 0.55, 0.95);
    const float ambientLight = 0.2;

    float lighting = max(dot(normalize(v_Normal), lightDirection), ambientLight);
    FragColor = vec4(baseColor * lighting, 1.0);
}
