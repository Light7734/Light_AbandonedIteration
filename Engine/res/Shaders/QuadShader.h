#define LT_ENGINE_RESOURCES_QUAD_SHADER_VS \
R"(
+GLSL
#version 440 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

out vec4 vso_FragmentColor;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	vso_FragmentColor = a_Color;
}
-GLSL


+HLSL
struct VertexOut
{
	float4 Color : COLOR;
	float4 Position : SV_Position;
};

VertexOut main(float3 InPosition : POSITION, float4 InColor : COLOR)
{
	VertexOut vso;
	vso.Position = float4(InPosition.x, InPosition.y, InPosition.z, 1.0);
	vso.Color = InColor;

	return vso;
}
-HLSL)"

#define LT_ENGINE_RESOURCES_QUAD_SHADER_PS \
R"(
+GLSL
#version 440 core

in vec4 vso_FragmentColor;

out vec4 fso_FragmentColor;

void main()
{
	fso_FragmentColor = vso_FragmentColor;
}
-GLSL


+HLSL
float4 main(float4 Color : COLOR) : SV_Target
{
	return Color;
}
-HLSL
)"