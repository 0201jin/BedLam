#include "GameScreen.h"
#include "StageMgr.h"
#include "Character.h"
#include "Terrain.h"

Character character;
Terrain terrain;

GameScreen::GameScreen(void)
{
}


GameScreen::~GameScreen(void)
{
	Release();
}

bool GameScreen::Initialize(HWND hWnd)
{
	gDevice = StageMgr::GetInst()->GetDevice();

	character.Initialize(gDevice->device, 0, 0, 10);

	character.SetDxinput(StageMgr::GetInst()->GetDxinput());

	terrain.Initialize(gDevice->device, StageMgr::GetInst()->GetMapString());

	StageMgr::GetInst()->Setwindow(true);

	return true;
}

void GameScreen::Update(float gameTime)
{
	if (StageMgr::GetInst()->Getwindow())
		character.update();
}

void GameScreen::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(255, 255, 255));
	gDevice->Begin();

	terrain.Draw(gameTime);

	gDevice->End();
	gDevice->Present();
}

void GameScreen::Release()
{

}

void GameScreen::DeviceReload()
{
	gDevice = StageMgr::GetInst()->GetDevice();

	character.Initialize(gDevice->device);

	//character.SetDxinput(StageMgr::GetInst()->GetDxinput());

	terrain.Initialize(gDevice->device, StageMgr::GetInst()->GetMapString());
}
