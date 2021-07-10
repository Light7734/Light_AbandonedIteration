#version 440 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

layout(std140, binding = 0) uniform ub_ViewProjection
{
	mat4 viewProjection;
};

out vec4 vso_FragmentColor;

void main()
{
	gl_Position = viewProjection * vec4(a_Position, 1.0);
	vso_FragmentColor = a_Color;
}