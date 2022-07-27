// Light vertex shader
// Standard issue vertex shader, apply matrices, pass info to pixel shader
Texture2D textureHeightMap : register(t0);
SamplerState sampler0 : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer TerrainBuffer : register(b1)
{
	float amplitude;
	float3 padding;
}

struct InputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct OutputType
{
	float4 position : SV_POSITION;
	float4 depthPosition : TEXCOORD0;
	float3 normal : NORMAL;
};


OutputType main(InputType input)
{
	OutputType output;
	
	//Heightmap Code
	float4 textureColour;
	textureColour = textureHeightMap.SampleLevel(sampler0, input.tex, 0);
	input.position.y += amplitude * textureColour;
	
	

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

    // Store the position value in a second input value for depth value calculations.
	output.depthPosition = output.position;

	// Calculate the normal vector against the world matrix only and normalise.
	output.normal = mul(input.normal, (float3x3) worldMatrix);
	output.normal = normalize(output.normal);

	return output;
}


