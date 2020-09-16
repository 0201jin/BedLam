#include "CreateMapCreateButton.h"
#include "Mouse.h"
#include "KeyMgr.h"

string GameMode[2] = 
{
	"CreateMode",
	"SurviveMode"
};

string MapType[2] = 
{
	"FlatLand",
	"Nature"
};

CreateMapCreateButton::CreateMapCreateButton(void)
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized  = false;
}


CreateMapCreateButton::~CreateMapCreateButton(void)
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

bool CreateMapCreateButton::Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex2)
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

	TypeCount = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);

	if(DrawID == "GameMode")
	{
		m_FontClassList.push_back(CreateFontClass(device, "res\\Menu.otf", GameMode[0], 25, 500, 80, position.x, position.y));
	}

	else if(DrawID == "MapType")
	{
		m_FontClassList.push_back(CreateFontClass(device, "res\\Menu.otf", MapType[0], 25, 500, 80, position.x, position.y));
	}

	initialized = true;

	return true;
}

bool CreateMapCreateButton::IsInitialized()
{
	return initialized;
}

bool CreateMapCreateButton::Initialize()
{
	return true;
}

int CreateMapCreateButton::Update(float gameTime)
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
			mma = 0;
			if(DrawID == "GameMode")
			{
				//여기에 맞는 로직의 코드를 작성
				TypeCount++;
				if(1 < TypeCount)
				{
					TypeCount = 0;
				}
				
				for(vector<Font*>::iterator iter = m_FontClassList.begin();
					iter != m_FontClassList.end(); ++iter)
				{
					(*iter)->SetText(GameMode[TypeCount]);
				}

				return 1;
			}

			else if(DrawID == "MapType")
			{
				//여기에 맞는 로직의 코드를 작성
				TypeCount++;
				if(1 < TypeCount)
				{
					TypeCount = 0;
				}

				for(vector<Font*>::iterator iter = m_FontClassList.begin();
					iter != m_FontClassList.end(); ++iter)
				{
					(*iter)->SetText(MapType[TypeCount]);
				}
				return 2;
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

void CreateMapCreateButton::Draw(float gameTime)
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

void CreateMapCreateButton::Release()
{
	for(std::vector<LPDIRECT3DTEXTURE9>::iterator iter = texture.begin();
		iter != texture.end(); ++iter)
	{
		delete (*iter);
	}

	delete sprite;
}

Font* CreateMapCreateButton::CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y)
{
	Font* AA = new Font();
	AA->FontOption(pd3dDevice, FontLocation, Message, FontSize, fx, fy, x, y);
	return AA;
}

int CreateMapCreateButton::GetTypeCount()
{
	return TypeCount;
}
