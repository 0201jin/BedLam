#pragma once
class PerlinNoise
{
public:
	PerlinNoise(void);
	~PerlinNoise(void);

	float noise(float x, float y, float z);

private:
	int *p; 
	float *Gx;
	float *Gy;
	float *Gz;
};

