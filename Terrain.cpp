#include "Terrain.h"
#include "Obj.h"
#include "StageMgr.h"

MapMgr mapmgr;

Terrain::Terrain(void)
{
	m_chunk_heigh = vector<vector<int>>(32, vector<int>(32, 0));
}


Terrain::~Terrain(void)
{
}

bool Terrain::Initialize()
{
	return true;
}

void Terrain::Initialize(LPDIRECT3DDEVICE9 device, string mapName)
{
	Device = device;

	Device->SetRenderState(D3DRS_ZENABLE, TRUE);

	Device->SetRenderState ( D3DRS_ZWRITEENABLE , TRUE ); 

	Device->SetRenderState ( D3DRS_ZFUNC , D3DCMP_LESSEQUAL );

	mapmgr.ReadMapData(mapName);

	m_chunk_heigh = mapmgr.ChunkLoad(0, 0);

	for(int x = 0; x < 32; x++)
	{
		for(int z = 0; z < 32; z++)
		{
			m_VoxelDrawMgr.push_back(CreateVoxel(Device, x, m_chunk_heigh[z][x], z, D3DCOLOR_XRGB(x, m_chunk_heigh[x][z]*25, z)));

			//printf("%d", m_chunk_heigh[x][z]);
		}			
	}
}

int Terrain::Update(float gameTime)
{
	return 0;
}

void Terrain::Draw(float gameTime)
{
	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);

	for(vector<Obj*>::iterator iter = m_VoxelDrawMgr.begin();
		iter != m_VoxelDrawMgr.end(); ++iter)
	{
		(*iter)->Draw(gameTime);
	}

	Device->Present(0, 0, 0, 0); 
}

void Terrain::Release()
{

}

Obj* Terrain::CreateVoxel(LPDIRECT3DDEVICE9 device, float _x, float _y, float _z, D3DCOLOR _COLOR)
{
	VoxelDrawMgr* AA = new VoxelDrawMgr();
	AA->SetColor(_COLOR);
	AA->Initialize(device, _x, _y, _z);
	return AA;
}
