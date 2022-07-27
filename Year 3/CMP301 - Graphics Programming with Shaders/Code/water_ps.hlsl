// Light pixel shader
// Calculate diffuse lighting for a single directional light (also texturing)

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

cbuffer LightBuffer : register(b0)
{	
	float4 diffuseColour;
	float4 ambientColour;
	float4 lightDirection;
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateLighting(float4 lightDirection, float3 normal, float4 diffuseColour, float4 ambientColour)
{	
	float intensity = 0;
	float4 colour = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float3 newLightDirection = { lightDirection.x, lightDirection.y, lightDirection.z };
		
	intensity += saturate(dot(normal, -newLightDirection));
	colour += ambientColour + saturate(diffuseColour * intensity);
	return colour;

}

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float4 lightColour;


	// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
	textureColour = texture0.Sample(sampler0, input.tex);
	lightColour = calculateLighting(lightDirection, input.normal, diffuseColour, ambientColour);

	return lightColour * textureColour;
}



