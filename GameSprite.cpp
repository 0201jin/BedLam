#include "GameSprite.h"

GameSprite::GameSprite()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized  = false;
}

GameSprite::GameSprite(float x, float y)
{
	position.x = x;
	position.y = y;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized  = false;
}

GameSprite::~GameSprite()
{
	if(sprite)
	{
		sprite->Release();
		sprite = 0;
	}

	if(tex)
	{
		tex->Release();
		tex = 0;
	}
}

D3DXVECTOR3 GameSprite::Getposition()
{
	return position;
}

bool GameSprite::Initailize(LPDIRECT3DDEVICE9 device, std::string file, float width, float height)
{
	if(!SUCCEEDED(D3DXCreateTextureFromFileEx(device,file.c_str(),width, height, D3DX_DEFAULT, 0, 
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex)))
	{
		std::string s = "Texture가 없습니다";
		MessageBox(NULL,s.c_str(),NULL,NULL);
		return false;
	}

	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "스프라이트를 만드는데 문제가 생겼습니다.",NULL,NULL);
		return false;
	}

	initialized = true;

	return true;
}

bool GameSprite::IsInitialized()
{
	return initialized;
}

void GameSprite::Update(float gameTime)
{
	//업데이트 로직
}

void GameSprite::Draw(float gameTime)
{
	if(sprite && tex)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		sprite->Draw(tex, NULL, NULL, &position, color);

		sprite->End();
	}
}