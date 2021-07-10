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