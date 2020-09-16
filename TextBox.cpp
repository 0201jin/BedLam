#include "TextBox.h"
#include <iostream>
#include <Windows.h>
#include "StageMgr.h"
#include "ImeMgr.h"
#include "Mouse.h"

String gText;
ImeMgr Imemgr;

TextBox::TextBox(void)
{
}

TextBox::~TextBox(void)
{
}

std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0); 
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0); 
	std::string r(buf);
	delete[] buf;
	return r;
}

bool TextBox::Initailize(LPDIRECT3DDEVICE9 device, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex2, HWND hwnd, String message)
{
	gText = message;
	initialized = true;

	texture.push_back(tex1);

	texture.push_back(tex2);

	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "해당 이미지를 불러오는데 문제가 생겼습니다.",NULL,NULL);
		return false;
	}

	position.x = x;
	position.y = y;
	position.z = 0;

	m_iScene = 0;

	m_tInfo.fCX = 500;
	m_tInfo.fCY = 80;
	m_tInfo.fX = position.x;
	m_tInfo.fY = position.y;

	wchar_t* mme = L"";

	Imemgr.SetString(mme);

	string aab = ws2s(gText);

	m_FontClassList.push_back(CreateFontClass(device, "res\\Menu.otf", aab, 25, 480, 80, position.x + 10, position.y));

	return true;
}

bool TextBox::IsInitialized()
{
	return initialized;
}

bool TextBox::Initialize()
{
	return initialized;
}

int TextBox::Update(float gameTime)
{	
	if(PtInRect(&GetRect(),Mouse::GetPos()))
	{
		DIMOUSESTATE MouseState;

		if(!m_pDirectInput->MouseProcess(&MouseState))
		{
			return 0;
		}

		if(MouseState.rgbButtons[0])
		{
			m_iScene = 1;
		}
	}
	else
	{
		DIMOUSESTATE MouseState;

		if(!m_pDirectInput->MouseProcess(&MouseState))
		{
			return 0;
		}

		if(MouseState.rgbButtons[0])
		{
			gText = Imemgr.GetString();

			Imemgr.SetString((wchar_t*)gText.c_str());
			m_iScene = 0;
		}
	}

	if(m_iScene == 1)
	{
		gText = Imemgr.GetString();

		string aab = ws2s(gText);

		for(vector<Font*>::iterator iter = m_FontClassList.begin();
			iter != m_FontClassList.end(); ++iter)
		{
			(*iter)->SetText(aab);
		}

		m_m_gtext = aab;
	}

	return 0;
}

void TextBox::Draw(float gameTime)
{
	if(sprite)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		sprite->Draw(texture[m_iScene], NULL, NULL, &position, color);

		sprite->End();

		for(vector<Font*>::iterator iter = m_FontClassList.begin();
			iter != m_FontClassList.end(); ++iter)
		{
			(*iter)->Draw(DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(0,0,0));
		}
	}
}

void TextBox::Release()
{

}

Font* TextBox::CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y)
{
	Font* AA = new Font();
	AA->FontOption(pd3dDevice, FontLocation, Message, FontSize, fx, fy, x, y);
	return AA;
}
