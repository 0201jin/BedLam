#include "ListBox.h"
#include "Mouse.h"
#include "KeyMgr.h"

ListBox::ListBox(void)
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	ItemCount = 400;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized  = false;
}


ListBox::~ListBox(void)
{
	for(list<Obj*>::iterator iter = m_ItemBox.begin();
		iter != m_ItemBox.end(); ++iter)
	{
		delete (*iter);
	}

	if(sprite)
	{
		sprite->Release();
		sprite = 0;
	}
}

bool ListBox::Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex3, LPDIRECT3DTEXTURE9 tex)
{
	texture.push_back(tex1);

	texture.push_back(tex3);

	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "해당 이미지를 불러오는데 문제가 생겼습니다.",NULL,NULL);
		return false;
	}

	position.x = x;
	position.y = y;
	position.z = 0;

	position_Scroll.x = position.x + 450;
	position_Scroll.y = position.y;
	position_Scroll.z = 0;

	position_Scroll_But.x = position_Scroll.x;
	position_Scroll_But.y = position_Scroll.y;
	position_Scroll_But.z = 0;

	m_tInfo.fCX = 500;
	m_tInfo.fCY = 400;
	m_tInfo.fX = position.x;
	m_tInfo.fY = position.y;

	color = D3DCOLOR_ARGB(255,255,255,255);

	initialized = true;

	int bmm = 0;

	for(vector<aan>::iterator iter = MapData.begin();
		iter != MapData.end(); ++iter)
	{
		m_ItemBox.push_back(CreateItemBoxClass(device, 450, 150, position.x, position.y + (m_tInfo.fCY * bmm), tex, (*iter)));
		bmm++;
	}

	return true;
}

bool ListBox::IsInitialized()
{
	return initialized;
}

bool ListBox::Initialize()
{
	return true;
}

int ListBox::Update(float gameTime)
{
	if(PtInRect(&GetRect(),Mouse::GetPos()))
	{
		if(Mouse::GetPos().y >= position_Scroll.y && Mouse::GetPos().y <= position_Scroll.y + m_tInfo.fCY && Mouse::GetPos().x >= position_Scroll.x && Mouse::GetPos().x <= position_Scroll.x + 50) //마우스의 y값이 스크롤 y값보다 크고 마우스 y+a가 스크롤 y+a보다 작으면 실행 | 마우스의 x값이 스크롤 x값보다 크고 마우스 x+a가 스크롤 x+a보다 작으면 실행
		{
			if(GetAsyncKeyState(VK_LBUTTON)) //버튼 클릭이 되어 있으면 | 버튼과 리스트 전체적인 부분을 나누기 위해서 나눔
			{
				if(Mouse::GetPos().y >= position_Scroll.y && Mouse::GetPos().y + 20 <= position_Scroll.y + m_tInfo.fCY) //옮기기 적당한가를 체크 후 적당하면 True
				{
					position_Scroll_But.y = Mouse::GetPos().y; //스크롤 버튼의 y값을 마우스 y값으로 설정
				}	
			}
		}
		DIMOUSESTATE MouseState;

		if(!m_pDirectInput->MouseProcess(&MouseState))
		{
			return 0;
		}

		if(MouseState.lZ > 0)
		{
			if(position_Scroll_But.y > position_Scroll.y)
				position_Scroll_But.y -= 1;
			printf("Mouse Wheel Up! IZ = %ld\n", MouseState.lZ);
		}

		if(MouseState.lZ < 0)
		{
			if(position_Scroll_But.y+20 < position_Scroll.y+400)
				position_Scroll_But.y += 1;
			printf("Mouse Wheel Down! IZ = %ld\n", MouseState.lZ);
		}
	}
	return 0;
}

void ListBox::Draw(float gameTime)
{
	if(sprite)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		sprite->Draw(texture[0], NULL, NULL, &position, color); //리스트박스 틀	

		sprite->Draw(texture[1], NULL, NULL, &position_Scroll_But, color); //리스트박스 스크롤 버튼

		for(list<Obj*>::iterator iter = m_ItemBox.begin();
			iter != m_ItemBox.end(); ++iter)
		{
			(*iter)->Draw(gameTime);
		}

		sprite->End();
	}
}

void ListBox::Release()
{
	for(std::vector<LPDIRECT3DTEXTURE9>::iterator iter = texture.begin();
		iter != texture.end(); ++iter)
	{
		delete (*iter);
	}

	for(std::vector<aan>::iterator iter = MapData.begin();
		iter != MapData.end(); ++iter)
	{
		delete &iter;
	}

	delete sprite;
}

ItemBox* ListBox::CreateItemBoxClass(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, aan ItemData)
{
	ItemBox* AA = new ItemBox();
	AA->Initailize(device,width, height, x, y, tex1, ItemData);
	return AA;
}
