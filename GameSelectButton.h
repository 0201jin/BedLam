#pragma once
#include "DXInput.h"
#include "Obj.h"

class GameSelectButton : public Obj
{
public:
	GameSelectButton();
	GameSelectButton(float x, float y);
	~GameSelectButton(void);
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
	LPDIRECT3DDEVICE9 gdevice;
	std::vector<LPDIRECT3DTEXTURE9> texture;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	std::string DrawID;
	bool initialized;
	int mma;
	DXInput *m_pDirectInput;
};

