#include "FractalNoise.h"

FractalNoise::FractalNoise(void)
{
	m_perlinSource = new PerlinNoise();

	m_octaves = 8;
	m_lacunarity = 2.0f;
	m_persistence = 0.5f;
	m_baseFrequency = 1.0f;
	m_baseAmplitude = 1.0f;
}

FractalNoise::~FractalNoise(void)
{
	delete m_perlinSource;
}

float FractalNoise::noise(float x, float y, float z)
{
	float sum = 0;
	float freq = m_baseFrequency;
	float amp = m_baseAmplitude;

	for (int i=0; i<m_octaves; ++i) {
		sum += m_perlinSource->noise(x*freq, y*freq, z*freq)*amp;

		freq *= m_lacunarity;
		amp *= m_persistence;
	}

	return sum;
}

void FractalNoise::setOctaves(int o)
{
	if (o > 0) {
		m_octaves = o;
	}
}

void FractalNoise::setPersistence(float p)
{
	m_persistence = p;
}

void FractalNoise::setLacunarity(float l)
{
	m_lacunarity = l;
}

void FractalNoise::setBaseFrequency(float f)
{
	m_baseFrequency = f;
}

void FractalNoise::setBaseAmplitude(float a)
{
	m_baseAmplitude = a;
}
