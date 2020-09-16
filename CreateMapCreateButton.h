#pragma once
#include <d3dx9.h>
#include <string>
#include "DXInput.h"
#include "Obj.h"
#include "Font.h"

class CreateMapCreateButton  : public Obj
{
private:
	int	m_iScene;
	std::vector<LPDIRECT3DTEXTURE9> texture;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	std::string DrawID;
	DXInput *m_pDirectInput;
	bool initialized;
	int mma, TypeCount;
	D3DXVECTOR3 position;
	vector<Font*> m_FontClassList;

	Font* CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y);

public:
	bool Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex2);
	bool IsInitialized();
	virtual bool Initialize();
	virtual int Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();

	void SetDrawID(string _drawId){DrawID  = _drawId;}
	string GetDrawId() { return DrawID; }
	int GetTypeCount();

	void SetDxinput(DXInput *mm)
	{
		m_pDirectInput = mm;
	}

public:
	CreateMapCreateButton(void);
	~CreateMapCreateButton(void);
};

