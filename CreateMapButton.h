#pragma once
#include <d3dx9.h>
#include <string>
#include "DXInput.h"
#include "Obj.h"

class CreateMapButton : public Obj
{
public:
	CreateMapButton(float x, float y);
	CreateMapButton(void);
	~CreateMapButton(void);

	bool Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex2);
	bool IsInitialized();
	virtual bool Initialize();
	virtual int Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();
	D3DXVECTOR3 position;
	void SetDrawID(string _drawId){DrawID  = _drawId;}

	void SetDxinput(DXInput *mm)
	{
		m_pDirectInput = mm;
	}

private:
	int	m_iScene;
	std::vector<LPDIRECT3DTEXTURE9> texture;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	std::string DrawID;
	DXInput *m_pDirectInput;
	bool initialized;
	int mma;
};

