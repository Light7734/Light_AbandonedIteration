#define LT_ENGINE_RESOURCES_TEXTURE_SHADER_VS \
R"(
+GLSL
#version 440 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 texCoords;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	texCoords = a_TexCoords;
}
-GLSL
+HLSL
struct VertexOut
{
	float2 uv : UV;
	float4 position : SV_Position;
};

VertexOut main(float3 InPosition : POSITION, float2 InUV : UV) 
{
	VertexOut vso;
	vso.position = float4(InPosition, 1.0);
	vso.uv = InUV;
	
	return vso;
}
-HLSL
)"

#define LT_ENGINE_RESOURCES_TEXTURE_SHADER_PS \
R"(
+GLSL
#version 440 core

in vec2 texCoords;

uniform sampler2D u_Texture;

out vec4 FragmentColor;

void main()
{
	FragmentColor = texture(u_Texture, texCoords);
}
-GLSL
+HLSL
sampler samplerState : register(s0);
Texture2D<float4> myTexture : register(t0);

float4 main(float2 InUV : UV) : SV_Target
{
	return myTexture.Sample(samplerState, InUV);
}

-HLSL
)"