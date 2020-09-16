#pragma once
#include "PerlinNoise.h"

class FractalNoise
{
public:
	FractalNoise(void);
	~FractalNoise(void);
	
	float noise(float x, float y, float z);
	void setOctaves(int o);
	void setPersistence(float p);
	void setLacunarity(float l);

	void setBaseFrequency(float f);
	void setBaseAmplitude(float a);

private:
	PerlinNoise *m_perlinSource;

	int m_octaves;
	float m_persistence;
	float m_lacunarity;
	float m_baseFrequency;
	float m_baseAmplitude;
};

