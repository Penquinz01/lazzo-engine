#version 460 core

// All primitives and imported meshes using this shader provide position at
// location 0 and a normal at location 1.
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Normal;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
    v_Normal = mat3(u_Model) * a_Normal;
}
