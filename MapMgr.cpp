#include "MapMgr.h"
#include <fstream>
#include <direct.h>

FractalNoise *noiseMaker = new FractalNoise();
int width = 32;
int height = 32;
float *noiseArray;
float mini = 0.0f;
float maxi = 0.0f;

MapMgr::MapMgr(void)
{
	m_chunk_heigh = vector<vector<int>>(32, vector<int>(32, 0));
}

MapMgr::~MapMgr(void)
{
}

void MapMgr::GetPerlinNoise()
{
	noiseArray = new float[width*height];
	float invWidth = 1.0f / float(width);
	float invHeight = 1.0f / float(height);
	for (int x=0; x<width; ++x) 
	{
		for (int y=0; y<height; ++y) {

			noise = noiseMaker->noise(float(x)*invWidth, float(y)*invHeight, 0.72);

			noiseArray[y*width + x] = noise;

			if (noise < mini) mini = noise;
			if (noise > maxi) maxi = noise;
		}
	}
}

void MapMgr::SetPerlinNoise(int Octaves, float Persistence, float Lacunarity, float BaseFrequency, float BaseAmplitude)
{
	noiseMaker->setOctaves(Octaves);
	noiseMaker->setPersistence(Persistence);
	noiseMaker->setLacunarity(Lacunarity);
	noiseMaker->setBaseFrequency(BaseFrequency);
	noiseMaker->setBaseAmplitude(BaseAmplitude);
}

void MapMgr::DrawPixel()
{
	float temp = 1.0f / (maxi - mini);
	HDC hdc = NULL;

	/*HDC hdc = GetDC(hwnd);
	PAINTSTRUCT ps;
	BeginPaint(hwnd, &ps);*/
	for (int x=0; x<width; ++x) 
	{
		for (int y=0; y<height; ++y) {
			noise = noiseArray[y*width + x];
			noise = -1.0f + 2.0f*(noise - mini)*temp;

			noise += 1.0f;
			noise *= 0.5f;

			// 그림을 그립니다.

			//SetPixel(hdc, x, y, RGB(noise*0xff,noise*0xff,noise*0xff));

			m_chunk_heigh[x][y] = noise*x; //곱하기에 따라서 지형이 바뀜

			printf("%f ", noise);
		}

		printf("\n");
	}
	/*EndPaint(hwnd, &ps);
	ReleaseDC(hwnd,hdc);*/
}

void MapMgr::CreateMap(int seed, string mapname)
{
	m_ChunkSeed.clear();
	int b = 0;

	if(seed < 0)
	{
		seed *= -1;
	}

	for(;;)
	{
		seed = (int)(seed*109+2047)%2048;

		if(b != 0)
		{
			if(seed == m_ChunkSeed[0])
			{
				printf("\nSeed Vector Create Done!\n");
				break;
			}
		}

		m_ChunkSeed.push_back(seed);

		b++;
	}

	ofstream in;

	MakeFolder("MapSave\\" + mapname +"\\Data\\");

	in.open("MapSave\\" + mapname +"\\Data\\SDATA.dat", ios::out | ios::binary); //바이너리 모드로 파일을 오픈

	if( in ) { 
		for(vector<int>::iterator iter = m_ChunkSeed.begin();
			iter != m_ChunkSeed.end(); ++iter)
		{
			in.write((char*) &(*iter), sizeof(int)); //바이너리 형식으로 파일에 입력
			printf("\n%d\n", (*iter));
		}
		in.clear(); 
	} 

	if (in.is_open() == true){
		in.close();
	}
}

void MapMgr::ReadMapData(string mapname)
{
	ifstream in;
	in.open("MapSave\\" + mapname +"\\Data\\SDATA.dat", ios::in | ios::binary); //바이너리 모드로 파일을 오픈

	int mme;

	if (in.fail())
	{
		in.close();
	}
	else
	{
		while (!in.eof()){
			in.read((char*)&mme, sizeof(int)); //바이너리 형식으로 파일에서 읽어옴
			if(in.eof())
				break;
			m_ChunkSeed.push_back(mme);

			printf("\n%d\n", mme);
		}

		if (in.is_open() == true){
			in.close();
		}
	}

	/*int d = 0;
	for(;;)
	{
	if(d != 0)
	{
	if(m_ChunkSeed[d] == m_ChunkSeed[0])
	{
	break;
	}
	}		
	printf("\n%d, %d",d,m_ChunkSeed[d]);
	d++;
	}*/
}

vector<vector<int>> MapMgr::ChunkLoad(float x, float y)
{
	if(m_ChunkSeed.size() > 0)
	{
		if(x < 0)
		{
			x *= -1.7;
		}

		if(y < 0)
		{
			y *= -1.7;
		}

		if(x == 0 || y == 0)
		{
			x += 1.2;
			y += 1.7;
		}

		float a;

		float chunkseed;

		a = x / y;

		chunkseed = (m_ChunkSeed[(int)(a*109+2047) % 2048] / 1000) * (a / 300000);

		SetPerlinNoise(8, chunkseed, chunkseed, chunkseed, chunkseed);

		GetPerlinNoise();

		DrawPixel();

		printf("\n%f\n", chunkseed);

		return m_chunk_heigh;
	}
}
