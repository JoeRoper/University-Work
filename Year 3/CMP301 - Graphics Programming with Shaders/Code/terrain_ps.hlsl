// Light pixel shader
// Calculate diffuse lighting for a single directional light (also texturing)

Texture2D texture0 : register(t0);
Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);

cbuffer LightBuffer : register(b0)
{
	float4 diffuseColour;
	float4 ambientColour;
	float3 lightDirection;
	float amplitude;
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateLighting(float3 lightDirection, float3 normal, float4 diffuse, float4 ambient)
{
	float intensity = saturate(dot(normal, lightDirection));
	float4 colour = ambient + saturate(diffuse * intensity);
	return colour;
}

float3 calculateNormals(float2 uv)
{
	//Calculating the normals
	//get the normals into the pixel shader
	//sample texture point and normalise it per pixel
	//cross prosuct between north and south
	//then east and west of the point	

	/*
	Using pixel data
	average 4 cross products
	need to get north east south west
	*/

	//uint texW, texH, numLevels;

	//texture0.GetDimensions(0, texW, texH, numLevels);

	float sidestep = 0.01;

	float2 northTex, eastTex, southTex, westTex;
	westTex = uv + float2(-sidestep, 0);
	eastTex = uv + float2(sidestep, 0);
	southTex = uv + float2(0, sidestep);
	northTex = uv + float2(0, -sidestep);
	
	float northY, eastY, southY, westY;
	westY = texture0.SampleLevel(sampler0, westTex, 0).r;
	eastY = texture0.SampleLevel(sampler0, eastTex, 0).r;
	southY = texture0.SampleLevel(sampler0, southTex, 0).r;
	northY = texture0.SampleLevel(sampler0, northTex, 0).r;

	float3 tang, bitan;
	tang = normalize(float3(2.0f * (sidestep), (eastY - westY), 0.0f));
	bitan = normalize(float3(0.0f, (southY - northY), -2.0f * (sidestep)));

	float3 normalW;
	normalW = cross(tang, bitan);
	return normalW;
	
	
}

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float4 lightColour;

	// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
	textureColour = texture1.Sample(sampler0, input.tex);
	//lightColour = calculateLighting(-lightDirection, input.normal, diffuseColour, ambientColour);

	float3 newNormals = calculateNormals(input.tex);
	//float4 normTotal = float4(newNormals, 1);

	lightColour = calculateLighting(lightDirection, newNormals, diffuseColour, ambientColour);

	//if (normTotal.x == 0)
	//{
	//	float4 red = (1.0f, 0.0f, 0.0f, 1.0f);
	//	return red;
	//}
	//else
	//{
	//	float4 blue = (0.0f, 0.0f, 1.0f, 0.0f);
	//	return blue;
	//}
	//return lightColour * textureColour;

	//if (input.normal.y == 0)
	//{
	//	float4 red = (1.0f, 0.0f, 0.0f, 1.0f);
	//	return red;
	//}
	//else
	//{
	//	float4 blue = (0.0f, 0.0f, 1.0f, 0.0f);
	//	return blue;
	//}

	return lightColour * textureColour;
}



