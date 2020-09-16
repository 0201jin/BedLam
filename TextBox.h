#pragma once
#include "Obj.h"
#include "Font.h"
#include "DXInput.h"

typedef std::wstring String;

class StageMgr;
class TextBox : public Obj
{
private:
	std::vector<LPDIRECT3DTEXTURE9> texture;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	bool initialized;
	bool Quit;
	D3DXVECTOR3 position;
	vector<Font*> m_FontClassList;
	int	m_iScene;
	std::string DrawID;
	DXInput *m_pDirectInput;

	Font* CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y);

public:
	bool Initailize(LPDIRECT3DDEVICE9 device, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex2, HWND hwnd, String message);
	bool IsInitialized();
	virtual bool Initialize();
	virtual int Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();

	void SetDrawID(string _drawId){DrawID  = _drawId;}
	string GetDrawId() { return DrawID; }

	void SetDxinput(DXInput *mm)
	{
		m_pDirectInput = mm;
	}

public:
	TextBox(void);
	~TextBox(void);
};

