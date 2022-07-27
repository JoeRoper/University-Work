// Light pixel shader
// Calculate diffuse lighting for a single directional light (also texturing)

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

cbuffer LightBuffer : register(b0)
{
	float4 specularColour;
	float4 diffuseColour;
	float4 ambientColour;

	float3 lightDirection;
	float padding;

	float3 lightPosition;
	float cutOff;
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 worldPosition : TEXCOORD1;
};

// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateLighting(float3 lightDirection, float3 normal, float4 diffuse, float4 ambient, float3 lightPosition, float3 worldPosition, float cutOff)
{
	
	// Diffuse
	//float intensity = saturate(dot(normal, lightDirection));
	//float4 lightColour = saturate(diffuse * intensity);
	/*
	//Ambient
	float4 intensity = saturate(dot(normal, lightDirection));
	float4 lightColour = ambientColour + saturate(diffuseColour * intensity);
	return lightColour;
	*/
	/*
	//Point Light
	float4 intensity = saturate(dot(normal, lightDirection));
	float4 colour = ambient + saturate(diffuse * intensity);
	return colour;
	*/


	/////////////////////////////////////////////////////
	//Spotlight
	//Works out the light intesity of every pixel withing the spotlight range
	float3 pixelDirection = normalize(worldPosition - lightDirection);
	float3 unitLightDirection = normalize(lightDirection);
	float3 vectorCosAngle = dot(pixelDirection, unitLightDirection);
	float cosCutOff = cos(((cutOff / 2) * (3.14 / 180)));
	float lightIntensity = clamp(((vectorCosAngle - cosCutOff) / (1 - cosCutOff)), 0, 1);
	return saturate(diffuse * lightIntensity) + ambient;
	/////////////////////////////////////////////////
}

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float4 lightColour;

	// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
	textureColour = texture0.Sample(sampler0, input.tex);
	lightColour = calculateLighting(lightDirection, input.normal, diffuseColour, ambientColour, lightPosition, input.worldPosition, cutOff);
	return lightColour * textureColour;
}

