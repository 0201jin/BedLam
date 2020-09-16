#include "MenuButton.h"
#include "Mouse.h"
#include "KeyMgr.h"


MenuButton::MenuButton()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized  = false;
}

MenuButton::~MenuButton()
{
	if(sprite)
	{
		sprite->Release();
		sprite = 0;
	}
}

bool MenuButton::Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex2)
{
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

	m_tInfo.fCX = width;
	m_tInfo.fCY = height;
	m_tInfo.fX = x;
	m_tInfo.fY = y;

	m_iScene = 0;

	mma = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized = true;

	return true;
}

bool MenuButton::IsInitialized()
{
	return initialized;
}

int MenuButton::Update(float gameTime)
{
	if(PtInRect(&GetRect(),Mouse::GetPos()))
	{
		m_iScene = 1;

		DIMOUSESTATE MouseState;

		if(!m_pDirectInput->MouseProcess(&MouseState))
		{
			return 0;
		}

		if(MouseState.rgbButtons[0])
		{
			mma = 1;
		}

		if(MouseState.rgbButtons[0] == 0 && mma == 1)
		{
			mma = 2;
		}

		if(mma == 2)
		{
			if(DrawID == "Start")
			{
				return 1;
			}

			else if(DrawID == "Option")
			{
				return 2;
			}

			else if(DrawID == "Exit")
			{
				return 3;
			}
		}
	}

	else
	{
		m_iScene = 0;
		mma = 0;
	}

	return 0;
}

void MenuButton::Draw(float gameTime)
{
	if(sprite)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		sprite->Draw(texture[m_iScene], NULL, NULL, &position, color);

		sprite->End();
	}
}

bool MenuButton::Initialize()
{
	return true;
}

void MenuButton::Release()
{
	for(std::vector<LPDIRECT3DTEXTURE9>::iterator iter = texture.begin();
		iter != texture.end(); ++iter)
	{
		delete (*iter);
	}

	delete sprite;
}
