#include "DrawBackGround.h"


DrawBackGround::DrawBackGround()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized  = false;
}

DrawBackGround::~DrawBackGround()
{
	if(sprite)
	{
		sprite->Release();
		sprite = 0;
	}

	printf("\n백그라운드 클래스 삭제\n");
}

bool DrawBackGround::Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 texture)
{
	tex = texture;

	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		//MessageBox(NULL, "백그라운드 설정 중 문제 발생!",NULL,NULL);
		return false;
	}

	position.x = x;
	position.y = y;
	position.z = 0;

	m_tInfo.fCX = width;
	m_tInfo.fCY = height;
	m_tInfo.fX = x;
	m_tInfo.fY = y;

	initialized = true;

	color = D3DCOLOR_ARGB(255,255,255,255);

	return true;
}

bool DrawBackGround::IsInitialized()
{
	return initialized;
}

void DrawBackGround::Draw(float gameTime)
{
	if(sprite)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		sprite->Draw(tex, NULL, NULL, &position, color);

		sprite->End();
	}
}

int DrawBackGround::Update(float gameTime)
{
	return 0;
}

bool DrawBackGround::Initialize()
{
	return true;
}

void DrawBackGround::Release()
{
	delete tex;

	delete sprite;
}
