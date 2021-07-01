#define LT_ENGINE_RESOURCES_TEXTURE_SHADER_VS \
R"(
+GLSL
#version 440 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 vso_TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	vso_TexCoord = a_TexCoord;
}
-GLSL


+HLSL
struct VertexOut
{
	float2 TexChoord : TEXCHOORD;
	float4 Position : SV_Position;
};

VertexOut main(float3 InPosition : POSITION, float2 InTexChoord : TEXCHOORD) 
{
	VertexOut vso;
	vso.Position = float4(InPosition, 1.0);
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