#include "ItemBox.h"
#include "Mouse.h"
#include "KeyMgr.h"

ItemBox::ItemBox(void)
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized  = false;
}

ItemBox::ItemBox(float x, float y)
{
	position.x = x;
	position.y = y;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized  = false;
}


ItemBox::~ItemBox(void)
{
	for(vector<Font*>::iterator iter = m_FontClassList.begin();
		iter != m_FontClassList.end(); ++iter)
	{
		delete (*iter);
	}

	if(sprite)
	{
		sprite->Release();
		sprite = 0;
	}
}

bool ItemBox::Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, aan ItemData)
{
	texture.push_back(tex1);

	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "�ش� �̹����� �ҷ����µ� ������ ������ϴ�.",NULL,NULL);
		return false;
	}

	position.x = x;
	position.y = y;
	position.z = 0;

	m_tInfo.fCX = width;
	m_tInfo.fCY = height;
	m_tInfo.fX = position.x;
	m_tInfo.fY = position.y;

	color = D3DCOLOR_ARGB(255,255,255,255);

	m_FontClassList.push_back(CreateFontClass(device, "res\\Menu.otf", ItemData.MapName, 25, 220, 70, position.x + 20, position.y)); //�� �̸�

	m_FontClassList.push_back(CreateFontClass(device, "res\\Menu.otf", ItemData.PlayTime, 25, 220, 70, position.x + 240, position.y)); //�÷��� �ð�

	m_FontClassList.push_back(CreateFontClass(device, "res\\Menu.otf", ItemData.MapCreateDate, 25, 220, 70, position.x + 20, position.y + 70)); //�� ���� ��¥

	m_FontClassList.push_back(CreateFontClass(device, "res\\Menu.otf", ItemData.MapGameMode, 25, 220, 70, position.x + 240, position.y + 70)); //�� ���� ���

	initialized = true;

	printf("\nItemBox Ŭ���� �ε�\n");

	return true;
}

bool ItemBox::IsInitialized()
{
	return initialized;
}

bool ItemBox::Initialize()
{
	return true;
}

int ItemBox::Update(float gameTime)
{
	if(PtInRect(&GetRect(),Mouse::GetPos()))
	{
	}
	return 0;
}

void ItemBox::Draw(float gameTime)
{
	if(sprite)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		sprite->Draw(texture[0], NULL, NULL, &position, color); //����Ʈ�ڽ� Ʋ	

		sprite->End();

		for(vector<Font*>::iterator iter = m_FontClassList.begin();
			iter != m_FontClassList.end(); ++iter)
		{
			(*iter)->Draw(DT_VCENTER, D3DCOLOR_XRGB(0,0,0));
		}
	}
}

void ItemBox::Release()
{
	for(std::vector<LPDIRECT3DTEXTURE9>::iterator iter = texture.begin();
		iter != texture.end(); ++iter)
	{
		delete (*iter);
	}

	delete sprite;
}

Font* ItemBox::CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y)
{
	Font* AA = new Font();
	AA->FontOption(pd3dDevice, FontLocation, Message, FontSize, fx, fy, x, y);
	return AA;
}
