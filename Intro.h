#ifndef INTRO_H
#define INTRO_H

#include "Stage.h"
#include "Obj.h"

class Obj;
class Intro : public Stage
{
private:
	HWND hwnd;
	list<Obj*> m_BGlist;
	GraphicsDevice *gDevice;
public:
	void SetDevice(GraphicsDevice *_gDevice) { gDevice = _gDevice; }
	Obj* CreateButton(float _fx, float _fy, float _x, float _y, string _DrawId);
	Obj* CreateBG(GraphicsDevice *_gDevice, float _x, float _y, float _fx, float _fy, LPDIRECT3DTEXTURE9 tex);
public:
	void Run();
	bool Initialize(HWND hWnd);
	void Update(float gameTime);
	void Draw(float gameTime);
	void Release();
	void DeviceReload();
public:
	Intro(void);
	~Intro(void);
};
#endif

