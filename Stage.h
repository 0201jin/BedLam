#pragma once

#include "Define.h"
#include "GameSprite.h"
#include "DrawBackGround.h"
#include "Include.h"
#include "GraphicsDevice.h"

class Stage
{
public:
	map<string,GameSprite*> m_map;
	map<string,DrawBackGround*> g_map;
	virtual bool Initialize(HWND hWnd);
	virtual void Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual void Release();
	virtual void DeviceReload();
public:
	Stage(void);
	~Stage(void);
};

