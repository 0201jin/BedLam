#include "GameSelect.h"
#include "GameSelectButton.h"
#include "DrawBackGround.h"
#include "GraphicsDevice.h"
#include "Language.h"
#include "Option.h"
#include "StageMgr.h"
#include "MenuButton.h"

GameSelect::GameSelect(void)
{
}


GameSelect::~GameSelect(void)
{
	Release();
}

bool GameSelect::Initialize(HWND hWnd)
{
	gDevice = StageMgr::GetInst()->GetDevice();

	Language sd;

	Option op;

	string nn = op.LoadOption("Language");

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	LPDIRECT3DTEXTURE9 tex1 = StageMgr::GetInst()->GetResource("Button1");

	LPDIRECT3DTEXTURE9 tex2 = StageMgr::GetInst()->GetResource("Button2");

	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 150,"Single",gDevice, tex1, tex2));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 280,"Multi",gDevice, tex1, tex2));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 410,"Back",gDevice, tex1, tex2));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("GameSelect Single",nn+".txt").c_str(), 25, 400, 100, 440, 150));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("GameSelect Multi",nn+".txt").c_str(), 25, 400, 100, 440, 280));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("GameSelect Back",nn+".txt").c_str(), 25, 400, 100, 440, 410));

	return true;
}

void GameSelect::Update(float gameTime)
{
	for(list<Obj*>::iterator iter = m_buttonlist.begin(); 
		iter != m_buttonlist.end(); ++iter)
	{
		int iResult = (*iter)->Update(gameTime);
		if(iResult == 1) 
		{
			StageMgr::GetInst()->SetState(IDS_STAGE_SINGLEMODE, hwnd);
			return;
		}

		else if(iResult == 2) 
		{
			//StageMgr::GetInst()->SetState(IDS_STAGE_OPTION, hwnd);
			return;
		}

		else if(iResult == 3) 
		{
			StageMgr::GetInst()->SetState(IDS_STAGE_MAIN, hwnd);
			return;
		}
	}
}

void GameSelect::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(255,255,255));
	gDevice->Begin();

	// <- Draw Logic ->//

	for(list<Obj*>::iterator iter = m_BGlist.begin();
		iter != m_BGlist.end(); ++iter)
	{
		(*iter)->Draw(gameTime);
	}

	for(list<Obj*>::iterator iter = m_buttonlist.begin();
		iter != m_buttonlist.end(); ++iter)
	{
		(*iter)->Draw(gameTime);
	}

	for(vector<Font*>::iterator iter = m_FontClassList.begin();
		iter != m_FontClassList.end(); ++iter)
	{
		(*iter)->Draw(DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(0,0,0));
	}

	// <- Draw Logic ->//

	gDevice->End();
	gDevice->Present();
}

void GameSelect::Release()
{
	for(list<Obj*>::iterator iter = m_BGlist.begin();
		iter != m_BGlist.end(); ++iter)
	{
		delete (*iter);
	}

	for(list<Obj*>::iterator iter = m_buttonlist.begin();
		iter != m_buttonlist.end(); ++iter)
	{
		delete (*iter);
	}

	for(vector<Font*>::iterator iter = m_FontClassList.begin();
		iter != m_FontClassList.end(); ++iter)
	{
		delete (*iter);
	}
}

Obj* GameSelect::CreateButton(float _fx, float _fy, float _x, float _y, string _DrawId, GraphicsDevice *_gDevice, LPDIRECT3DTEXTURE9 tex, LPDIRECT3DTEXTURE9 tex2)
{
	GameSelectButton* AA = new GameSelectButton();
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex, tex2);
	AA->SetDxinput(StageMgr::GetInst()->GetDxinput());
	AA->SetDrawID(_DrawId);
	return AA;
}

Font* GameSelect::CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y)
{
	Font* AA = new Font();
	AA->FontOption(pd3dDevice, FontLocation, Message, FontSize, fx, fy, x, y);
	return AA;
}

Obj* GameSelect::CreateBG(GraphicsDevice *_gDevice, float _x, float _y, float _fx, float _fy, LPDIRECT3DTEXTURE9 tex)
{
	DrawBackGround* AA = new DrawBackGround();
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex);
	return AA;
}

void GameSelect::DeviceReload()
{
	gDevice = StageMgr::GetInst()->GetDevice();

	Language sd;

	Option op;

	string nn = op.LoadOption("Language");

	m_BGlist.clear();
	m_buttonlist.clear();
	m_FontClassList.clear();

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	LPDIRECT3DTEXTURE9 tex1 = StageMgr::GetInst()->GetResource("Button1");

	LPDIRECT3DTEXTURE9 tex2 = StageMgr::GetInst()->GetResource("Button2");

	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 150,"Single",gDevice, tex1, tex2));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 280,"Multi",gDevice, tex1, tex2));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 410,"Back",gDevice, tex1, tex2));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("GameSelect Single",nn+".txt").c_str(), 25, 400, 100, 440, 150));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("GameSelect Multi",nn+".txt").c_str(), 25, 400, 100, 440, 280));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("GameSelect Back",nn+".txt").c_str(), 25, 400, 100, 440, 410));

}
