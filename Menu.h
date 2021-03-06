#ifndef MENU_H
#define MENU_H

#include "Stage.h"
#include "Obj.h"
#include "Font.h"
#include "MapMgr.h"

class Obj;
class Font;
class Menu : public Stage
{
private:
	HWND hwnd;
	GraphicsDevice *gDevice;
	list<Obj*> m_buttonlist;
	vector<Font*> m_FontClassList;
	list<Obj*> m_BGlist;
	Font* CreditFont;
	clock_t time1, time2;

public:
	void SetDevice(GraphicsDevice *_gDevice) { gDevice = _gDevice; }
	Obj* CreateButton(float _fx, float _fy, float _x, float _y, string _DrawId, GraphicsDevice *_gDevice, LPDIRECT3DTEXTURE9 tex, LPDIRECT3DTEXTURE9 tex2);
	Font* CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y);
	Obj* CreateBG(GraphicsDevice *_gDevice, float _x, float _y, float _fx, float _fy, LPDIRECT3DTEXTURE9 tex);
public:
	bool Initialize(HWND hWnd);
	void Update(float gameTime);
	void Draw(float gameTime);
	void Release();
	void DeviceReload();

public:
	Menu(void);
	~Menu(void);
};

#endif