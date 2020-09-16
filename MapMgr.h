#pragma once
#include "FractalNoise.h"
#include <windows.h>
#include "include.h"

typedef struct BlockLocation
{
	int x;
	int y;
	int z;
	int blockcode;
}BlockLocation;

typedef struct XY
{
	int x;
	int y;
	XY(){}
	XY(int _x, int _y)
		:x(_x), y(_y)
	{

	}
}XY;

class MapMgr
{
public:
	MapMgr(void);
	~MapMgr(void);

public: //Noise
	void GetPerlinNoise();
	void SetPerlinNoise(int Octaves, float Persistence, float Lacunarity, float BaseFrequency, float BaseAmplitude);
	void DrawPixel();

	void CreateMap(int seed, string mapname);
	void ReadMapData(string mapname);

	vector<vector<int>> ChunkLoad(float x, float z);

private:
	float noise;
	float *noiseArray;

	vector<vector<BlockLocation>> m_world; 
	vector<BlockLocation> m_chunk;
	vector<int> m_ChunkSeed;
	vector<vector<int>> m_chunk_heigh;

	void MakeFolder( const string fileName )
	{
		for( int i=1; i < fileName.length(); i++ )
		{
			if( fileName[i] == '\\' || fileName[i] == '/' )
			{
				string subStr = fileName.substr( 0, i );
				const char* ccSubStr = subStr.c_str();

				CreateDirectory( ccSubStr, NULL );
			}
		}
	}
};

