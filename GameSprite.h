#ifndef GAMESPRIETE_H
#define GAMESPRIETE_H

#include <d3dx9.h>
#include <string>

class GameSprite
{
public:
	GameSprite();
	GameSprite(float x, float y);
	~GameSprite();

	D3DXVECTOR3 position;
	bool Initailize(LPDIRECT3DDEVICE9 device, std::string file, float width, float height);
	bool IsInitialized();
	D3DXVECTOR3 Getposition();
	virtual void Update(float gameTime);
	virtual void Draw(float gameTime);
private:
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	bool initialized;
};

#endif