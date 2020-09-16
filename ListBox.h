#pragma once
#include <d3dx9.h>
#include <string>
#include "Obj.h"
#include "DXInput.h"
#include "ItemBox.h"

class ListBox : public Obj
{
public:
	ListBox(float x, float y);
	ListBox(void);
	~ListBox(void);

	bool Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex3, LPDIRECT3DTEXTURE9 tex);
	bool IsInitialized();
	virtual bool Initialize();
	virtual int Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();

	void SetDxinput(DXInput *mm)
	{
		m_pDirectInput = mm;
	}

	void AddListItem(aan ListItem) 
	{ 
		MapData.push_back(ListItem); 
	}

	D3DXVECTOR3 position;
	D3DXVECTOR3 position_Scroll;
	D3DXVECTOR3 position_Scroll_But;

private:
	int	m_iScene;
	std::vector<LPDIRECT3DTEXTURE9> texture;
	vector<aan> MapData;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	std::string DrawID;
	bool initialized;
	DXInput *m_pDirectInput;
	int ItemCount;
	list<Obj*> m_ItemBox;

	ItemBox* CreateItemBoxClass(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, aan ItemData);
};

