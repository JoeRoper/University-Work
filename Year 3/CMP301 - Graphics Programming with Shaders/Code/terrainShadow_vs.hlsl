// Light vertex shader
// Standard issue vertex shader, apply matrices, pass info to pixel shader
Texture2D textureHeightMap : register(t0);
SamplerState sampler0 : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix lightViewMatrix;
	matrix lightProjectionMatrix;
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
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float4 lightViewPos : TEXCOORD1;
};


OutputType main(InputType input)
{
	OutputType output;
	
	//Heightmap Code
	//float amplitudeHeight = 40.0f;
	//float amplitudeHeight = 0.0f;
	float4 textureColour;
	textureColour = textureHeightMap.SampleLevel(sampler0, input.tex, 0);
	input.position.y += amplitude * textureColour;
	
	

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only and normalise.
	output.normal = mul(input.normal, (float3x3) worldMatrix);
	output.normal = normalize(output.normal);
	
	// Calculate the position of the vertice as viewed by the light source.
	output.lightViewPos = mul(input.position, worldMatrix);
	output.lightViewPos = mul(output.lightViewPos, lightViewMatrix);
	output.lightViewPos = mul(output.lightViewPos, lightProjectionMatrix);

	return output;
}


