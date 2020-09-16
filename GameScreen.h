#pragma once
#include "Stage.h"
#include "Obj.h"
#include "Font.h"
#include "VoxelDrawMgr.h"

class Obj;
class Font;
class GameScreen : public Stage
{
private:
	HWND hwnd;
	GraphicsDevice *gDevice;
	D3DXVECTOR3 position1;
	D3DXVECTOR3 target1;
	D3DXVECTOR3 up1;

public:
	bool Initialize(HWND hWnd);
	void Update(float gameTime);
	void Draw(float gameTime);
	void Release();
	void DeviceReload();

public:
	GameScreen(void);
	~GameScreen(void);
};

