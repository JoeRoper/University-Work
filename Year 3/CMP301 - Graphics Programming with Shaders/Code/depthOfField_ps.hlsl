

Texture2D normalSceneTexture : register(t0);
Texture2D blurSceneTexture : register(t1);
Texture2D depthSceneTexture : register(t2);
SamplerState SampleType : register(s0);

cbuffer DepthBuffer : register(b0)
{
	float range;
	float nearVal;
	float farVal;
	float offset;
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 main(InputType input) : SV_TARGET
{
	// Get the blurred scene
	float4 blurScene = blurSceneTexture.Sample(SampleType, input.tex);
	
	// Get the first scene 
	float4 scene = normalSceneTexture.Sample(SampleType, input.tex);

	// Get the depth
	float depth = depthSceneTexture.Sample(SampleType, input.tex).r;

	float centreDepthTexel = depthSceneTexture.Sample(SampleType, float2(0.5f, 0.5f)).r;

	// Invert the depth 
	depth = 1 - depth;
	centreDepthTexel = 1 - centreDepthTexel;

	// Scale to 0 - 1 range
	centreDepthTexel *= (farVal - nearVal);
	depth *= (farVal - nearVal);

	// Calculate blur factor
	float blurFactor = saturate(abs(depth - centreDepthTexel - offset) / range);

	// Return lerp
	return lerp(scene, blurScene, blurFactor);
}

