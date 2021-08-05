sampler samplerState : register(s0);
Texture2D<float4> myTexture : register(t0);

float4 main(float2 InTexChoord : TEXCOORD, float4 InTint : TINT) : SV_Target
{
	return myTexture.Sample(samplerState, InTexChoord) * InTint;
}