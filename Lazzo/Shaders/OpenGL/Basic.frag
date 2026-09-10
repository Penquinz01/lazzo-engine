#version 460 core

in vec3 v_Normal;

uniform vec3 u_Color = vec3(0.20, 0.55, 0.95);

out vec4 FragColor;

void main()
{
    const vec3 lightDirection = normalize(vec3(0.4, 0.7, 1.0));
    const float ambientLight = 0.2;

    float lighting = max(dot(normalize(v_Normal), lightDirection), ambientLight);
    FragColor = vec4(u_Color * lighting, 1.0);
}
