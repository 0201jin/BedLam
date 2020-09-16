#include "Stage.h"


Stage::Stage(void)
{
}


Stage::~Stage(void)
{
}

void Stage::Release()
{
	for(map<string,DrawBackGround*>::iterator iter = g_map.begin();
		iter != g_map.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	g_map.clear();
	m_map.clear();
}

bool Stage::Initialize(HWND hWnd)
{
	return true;
}

void Stage::Update(float gameTime)
{

}

void Stage::Draw(float gameTime)
{

}

void Stage::DeviceReload()
{

}
