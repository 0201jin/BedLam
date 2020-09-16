#pragma once
#include "MapMgr.h"
#include "VoxelDrawMgr.h"

class Terrain : public Obj
{
private:
	vector<vector<int>> m_chunk_heigh;
	LPDIRECT3DDEVICE9 Device;
	vector<Obj*> m_VoxelDrawMgr;

	Obj* CreateVoxel(LPDIRECT3DDEVICE9 device, float _x, float _y, float _z, D3DCOLOR _COLOR);

public:
	void Initialize(LPDIRECT3DDEVICE9 device, string mapName);

	virtual bool Initialize();
	virtual int Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();

public:
	Terrain(void);
	~Terrain(void);
};

