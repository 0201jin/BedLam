#include "Intro.h"
#include "DrawBackGround.h"
#include "GraphicsDevice.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "Define.h"
#include "Objfac.h"
#include "StageMgr.h"
#include "Obj.h"
#include <stdio.h>


Intro::Intro(void)
{
}


Intro::~Intro(void)
{
	Release();
}

bool Intro::Initialize(HWND hWnd)
{
	gDevice = StageMgr::GetInst()->GetDevice();

	StageMgr::GetInst()->LoadResource();

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));

	printf("\nIntro Loading Complete\n");

	printf("\nBackGround Draw Complete\n");
	
	return true;
}

void Intro::Update(float gameTime)
{
	// <- Loading Logic -> //

	if(GetAsyncKeyState(VK_RETURN))
	{
		StageMgr::GetInst()->SetState(IDS_STAGE_MAIN, hwnd);
	}

	// <- Loading Logic -> //
}

void Intro::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(255,255,255));
	gDevice->Begin();

	for(list<Obj*>::iterator iter = m_BGlist.begin();
		iter != m_BGlist.end(); ++iter)
	{
		(*iter)->Draw(gameTime);
	}

	gDevice->End();
	gDevice->Present();
}

void Intro::Release()
{
	for(list<Obj*>::iterator iter = m_BGlist.begin();
		iter != m_BGlist.end(); ++iter)
	{
		delete (*iter);
	}

	printf("\nIntro Delete\n");
}

void Intro::Run()
{
	Draw(0.0f);
	Update(0.0f);
}

Obj* Intro::CreateBG(GraphicsDevice *_gDevice, float _x, float _y, float _fx, float _fy, LPDIRECT3DTEXTURE9 tex)
{
	DrawBackGround* AA = new DrawBackGround();
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex);
	return AA;
}

void Intro::DeviceReload()
{
	m_BGlist.clear();

	gDevice = StageMgr::GetInst()->GetDevice();

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));
}
