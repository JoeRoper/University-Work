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

cbuffer TimeBuffer : register(b1)
{
	float time; //should be based on delta time from the timer class
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
	float4 lightViewPos : TEXCOORD1;
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
	
	//do a switch statement to return different things for normal and that make it calculate 
	//each time it will restart the calculation and have the same values

}

OutputType main(InputType input)
{
	OutputType output;
	

	//water code
	//input.position.x += amplitude * sin((input.position.z * frequency) + (time * speed)) * input.normal.x;
	//input.position.y += amplitude * sin((input.position.x * frequency) + (time * speed)) * input.normal.y;
	//input.position.z += amplitude * sin((input.position.y * frequency) + (time * speed)) * input.normal.z;
	//direction, steepness, wavelength
	//float4 waveA = float4(1, 1, 0.25, 60);
	//float4 waveB = float4(1, 0.6, 0.25, 31);
	//float4 waveC = float4(1, 1.3, 0.25, 18);
	float3 gridPoint;
	gridPoint.x = input.position.x;
	gridPoint.y = input.position.y;
	gridPoint.z = input.position.z;
	float3 p = gridPoint;
	float3 tangent = float3(1, 0, 0);
	float3 binormal = float3(0, 0, 1);
	float3 normal = normalize(cross(binormal, tangent));
	float3 normal1 = normalize(cross(binormal, tangent));
	float3 normal2 = normalize(cross(binormal, tangent));
	float3 normal3 = normalize(cross(binormal, tangent));
	
	
	p += GerstnerWave(waveA, gridPoint, tangent, binormal, 0);
	normal1 = GerstnerWave(waveA, gridPoint, tangent, binormal, 1);
	normal += GerstnerWave(waveA, gridPoint, tangent, binormal, 1);
	p += GerstnerWave(waveB, gridPoint, tangent, binormal, 0);
	normal2 = GerstnerWave(waveB, gridPoint, tangent, binormal, 1);
	normal += GerstnerWave(waveB, gridPoint, tangent, binormal, 1);
	p += GerstnerWave(waveC, gridPoint, tangent, binormal, 0);
	normal3 = GerstnerWave(waveC, gridPoint, tangent, binormal, 1);
	normal += GerstnerWave(waveC, gridPoint, tangent, binormal, 1);
	
	float3 normalFinal = (normal1 + normal2 + normal3);
	
	input.position.x = p.x;
	input.position.y = p.y;
	input.position.z = p.z;
	
	input.normal = normal; //normals b
	//input.normal = normalFinal;//normals a
	
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




