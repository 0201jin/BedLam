#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <d3dx9.h>
#include <string>
#include "Obj.h"
#include "DXInput.h"

class MenuButton : public Obj
{
public:
	MenuButton();
	MenuButton(float x, float y);
	~MenuButton();

	bool Initailize(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex2);
	bool IsInitialized();
	virtual bool Initialize();
	virtual int Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();
	D3DXVECTOR3 position;
	void SetDrawID(string _drawId){DrawID  = _drawId;}

	void SetDxinput(DXInput *mm)
	{
		m_pDirectInput = mm;
	}

private:
	int	m_iScene;
	std::vector<LPDIRECT3DTEXTURE9> texture;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	std::string DrawID;
	bool initialized;
	int mma;
	DXInput *m_pDirectInput;
};

#endif