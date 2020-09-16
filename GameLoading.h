#pragma once
#include "Stage.h"
#include "Obj.h"
#include "Font.h"

class Obj;
class Font;
class GameLoading : public Stage
{
public:
	bool Initialize(HWND hWnd);
	void Update(float gameTime);
	void Draw(float gameTime);
	void Release();
	void DeviceReload();

public:
	GameLoading(void);
	~GameLoading(void);
};

