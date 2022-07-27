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

cbuffer TimeBuffer : register(b1)
{
	float time;//should be based on delta time from the timer class
	float amplitude;
	float frequency;
	float speed;
}

cbuffer WaveBuffer : register(b2)
{
	float4 waveA;
	float4 waveB;
	float4 waveC;
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
};

float3 GerstnerWave(float4 wave, float3 p, float3 tangent, float3 binormal, int returnSwitch)
{
	float steepness = wave.z;
	float wavelength = wave.w;
	float PI = 3.142;
	float k = 2 * PI / wavelength;
	float c = sqrt(9.8 / k);
	float2 d = normalize(wave.xy);
	float f = k * (dot(d, p.xz) - c * time);
	float a = steepness / k;

	tangent += float3(
				-d.x * d.x * (steepness * sin(f)),
				d.x * (steepness * cos(f)),
				-d.x * d.y * (steepness * sin(f))
			);
	binormal += float3(
				-d.x * d.y * (steepness * sin(f)),
				d.y * (steepness * cos(f)),
				-d.y * d.y * (steepness * sin(f))
			);
	p = (
				d.x * (a * cos(f)),
				a * sin(f),
				d.y * (a * cos(f))
			);
	
	float3 normal = normalize(cross(binormal, tangent));
	
	switch (returnSwitch)
	{
		case 0:
			return p;
			break;
		case 1:
			return normal;
			break;
	}

}

OutputType main(InputType input)
{
	OutputType output;
	
	float3 gridPoint;
	gridPoint.x = input.position.x;
	gridPoint.y = input.position.y;
	gridPoint.z = input.position.z;
	float3 p = gridPoint;
	float3 tangent = float3(1, 0, 0);
	float3 binormal = float3(0, 0, 1);
	float3 normal = float3(0, 0, 0);
	
	
	p += GerstnerWave(waveA, gridPoint, tangent, binormal, 0);
	normal += GerstnerWave(waveA, gridPoint, tangent, binormal, 1);
	p += GerstnerWave(waveB, gridPoint, tangent, binormal, 0);
	normal += GerstnerWave(waveB, gridPoint, tangent, binormal, 1);
	p += GerstnerWave(waveC, gridPoint, tangent, binormal, 0);
	normal += GerstnerWave(waveC, gridPoint, tangent, binormal, 1);
	
	
	input.position.x = p.x;
	input.position.y = p.y;
	input.position.z = p.z;
	
	input.normal = normal;//normals 
	
	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only and normalise.
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	return output;
}
