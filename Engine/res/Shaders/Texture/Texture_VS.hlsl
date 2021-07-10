struct VertexOut
{
	float2 TexChoord : TEXCOORD;
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