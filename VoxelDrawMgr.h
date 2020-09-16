#pragma once
#include "Include.h"
#include "Define.h"
#include "Obj.h"

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z, D3DCOLOR color)
	{
		_x = x;
		_y = y;
		_z = z;
		_color = color;
	}
	float _x, _y, _z;
	D3DCOLOR _color;
	static const DWORD FVF;
};

class VoxelDrawMgr : public Obj
{
private:
	IDirect3DVertexBuffer9* VB;
	IDirect3DIndexBuffer9* IB;
	LPDIRECT3DDEVICE9 Device;
	D3DCOLOR color;
	Vertex* vertices;
	float _x, _z;

public:
	void nDraw();
	void Initialize(LPDIRECT3DDEVICE9 device, float _x, float _y, float _z);
	void SetColor(D3DCOLOR _COLOR);

	virtual bool Initialize();
	virtual int Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();

public:
	VoxelDrawMgr(void);
	~VoxelDrawMgr(void);
};

