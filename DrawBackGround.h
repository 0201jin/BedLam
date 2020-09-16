#ifndef DRAWBACKGROUND_H
#define DRAWBACKGROUND_H

#include <d3dx9.h>
#include <string>
#include "Obj.h"

class DrawBackGround : public Obj
{
public:
	DrawBackGround();
	DrawBackGround(float x, float y);
	~DrawBackGround();

	bool Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 texture);
	bool IsInitialized();
	virtual bool Initialize();
	virtual int Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();
	D3DXVECTOR3 position;
private:
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	bool initialized;
};
#endif

