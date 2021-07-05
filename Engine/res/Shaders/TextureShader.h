#define LT_ENGINE_RESOURCES_TEXTURE_SHADER_VS \
R"(
+GLSL
#version 440 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

layout(std140, binding = 0) uniform ub_ViewProjection
{
	mat4 u_ViewProjection;
};

out vec2 vso_TexCoord;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
	vso_TexCoord = a_TexCoord;
}
-GLSL


+HLSL
struct VertexOut
{
	float2 TexChoord : TEXCHOORD;
	float4 Position : SV_Position;
};

cbuffer cb_ViewProjection : register(b0)
{
	row_major matrix  viewProjection;
}


VertexOut main(float3 InPosition : POSITION, float2 InTexChoord : TEXCOORD)
{
	VertexOut vso;
	vso.Position = mul(float4(InPosition, 1.0), viewProjection);
	vso.TexChoord = InTexChoord;
	
	return vso;
}
-HLSL
)"

#define LT_ENGINE_RESOURCES_TEXTURE_SHADER_PS \
R"(
+GLSL
#version 440 core

in vec2 vso_TexCoord;

uniform sampler2D u_Texture;

out vec4 fso_FragmentColor;

void main()
{
	fso_FragmentColor = texture(u_Texture, vso_TexCoord);
}
-GLSL


+HLSL
sampler samplerState : register(s0);
Texture2D<float4> myTexture : register(t0);

float4 main(float2 InTexChoord : TEXCHOORD) : SV_Target
{
	return myTexture.Sample(samplerState, InTexChoord);
}

-HLSL
)"