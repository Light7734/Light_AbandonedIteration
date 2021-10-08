struct VertexOut
{
	float2 TexChoord : TEXCOORD;
	float4 Tint : TINT;
	float4 Position : SV_Position;
};

cbuffer cb_ViewProjection : register(b0)
{
	row_major matrix  viewProjection;
}

VertexOut main(float4 InPosition : POSITION, float4 InTint : TINT, float2 InTexChoord : TEXCOORD)
{
	VertexOut vso;
	vso.Position = mul(float4(InPosition), viewProjection);
	vso.Tint = InTint;
	vso.TexChoord = InTexChoord;

	return vso;
}