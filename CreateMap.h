#pragma once
#include "Stage.h"
#include "Obj.h"
#include "Font.h"
#include "MapMgr.h"

class Obj;
class Font;
class CreateMap : public Stage
{
private:
	HWND hwnd;
	GraphicsDevice *gDevice;
	list<Obj*> m_buttonlist;
	list<Obj*> m_MapTypeButtonList;
	list<Obj*> m_BGlist;
	Obj* m_TextBoxlist;
	vector<Font*> m_FontClassList;	
	aan MapData;
	MapMgr mapmgr;

public:
	void SetDevice(GraphicsDevice *_gDevice) { gDevice = _gDevice; }
	Obj* CreateButton(float _fx, float _fy, float _x, float _y, string _DrawId, GraphicsDevice *_gDevice, LPDIRECT3DTEXTURE9 tex, LPDIRECT3DTEXTURE9 tex2);
	Obj* CreateMapTypeButton(float _fx, float _fy, float _x, float _y, string _DrawId, GraphicsDevice *_gDevice, LPDIRECT3DTEXTURE9 tex, LPDIRECT3DTEXTURE9 tex2);
	Font* CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y);
	Obj* CreateBG(GraphicsDevice *_gDevice, float _x, float _y, float _fx, float _fy, LPDIRECT3DTEXTURE9 tex);
	Obj* CreateTextBox(LPDIRECT3DDEVICE9 device, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex2, HWND hwnd, string _DrawId, std::wstring message);

public:
	bool Initialize(HWND hWnd);
	void Update(float gameTime);
	void Draw(float gameTime);
	void Release();
	void DeviceReload();

public:
	CreateMap(void);
	~CreateMap(void);
};

