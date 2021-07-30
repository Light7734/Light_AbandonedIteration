struct VertexOut
{
	float4 Color : COLOR;
	float4 Position : SV_Position;
};

cbuffer cv_ViewProjection : register(b0)
{
	row_major matrix viewProjection;
}

VertexOut main(float4 InPosition : POSITION, float4 InColor : COLOR)
{
	VertexOut vso;
	vso.Position = mul(InPosition, viewProjection);
	vso.Color = InColor;

	return vso;
}