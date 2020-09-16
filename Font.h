#pragma once
#include <d3d9.h>
#include <d3dx9math.h>
#include <stdio.h>
#include <string.h>
#include "Obj.h"

class Font 
{
private:
	ID3DXFont *font;
	RECT fRec;
	std::string message;
public:
	Font(void);
	~Font(void);
	bool FontOption(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y);
	void Draw(DWORD Format, D3DCOLOR color);
	void SetText(std::string TextMessage);
	RECT CreateRect(int fx, int fy, int x, int y);
};