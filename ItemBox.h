#pragma once
#include "Obj.h"
#include "Font.h"

class ItemBox : public Obj
{
private:
	std::vector<LPDIRECT3DTEXTURE9> texture;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	bool initialized;
	D3DXVECTOR3 position;
	vector<Font*> m_FontClassList;

	Font* CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y);
public:
	bool Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, aan ItemData);
	bool IsInitialized();
	virtual bool Initialize();
	virtual int Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();
public:
	ItemBox(float x, float y);
	ItemBox(void);
	~ItemBox(void);
};

