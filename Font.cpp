#include "Font.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <WinGDI.h>
#include <windows.h>

Font::Font(void)
{
}


Font::~Font(void)
{
	if(font) { font -> Release(); font = 0;}
	printf("\n폰트 클래스 종료\n");
}

bool Font::FontOption(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y)
{
	font = NULL;

	HRESULT hr = D3DXCreateFont(pd3dDevice, FontSize, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, "res\\Menu.otf", &font);

	if(!SUCCEEDED(hr))
	{
		printf("font load Err");
		return false;
	}

	//SetRect(&fRec, Lx, Ty, Rx, By); //개발 함수로 변경해야됨

	fRec = CreateRect(fx, fy, x, y); //하하 변경했다!

	message = Message;

	return true;
}

void Font::Draw(DWORD Format, D3DCOLOR color)
{
	font->DrawTextA(NULL, message.c_str(), -1, &fRec, Format, color);
}

RECT Font::CreateRect(int fx, int fy, int x, int y)
{
	RECT  rt = 
	{
		int(x),
		int(y),
		int(x + fx),
		int(y + fy)
	};
	return rt;
}

void Font::SetText(std::string TextMessage)
{
	message = TextMessage;
}

