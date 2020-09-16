#include "Menu.h"
#include "DrawBackGround.h"
#include "GraphicsDevice.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "Define.h"
#include "Objfac.h"
#include "MenuButton.h"
#include <stdio.h>
#include "Language.h"
#include "StageMgr.h"
#include "Option.h"
#include "Credit.h"
#include "MapData.h"

Menu::Menu(void)
{
}


Menu::~Menu(void)
{
	Release();
}

bool Menu::Initialize(HWND hWnd)
{
	Language sd;

	Option op;

	Credit Cr;

	MapData md;

	gDevice = StageMgr::GetInst()->GetDevice();

	/*vector<aan> mm;

	aan m1;

	m1.MapCreateDate = "aas";
	m1.MapGameMode = "aas";
	m1.MapName = "aas";
	m1.PlayTime = "aas";

	mm.push_back(m1);

	md.WriteDataList(mm);

	vector<aan> mm1 = md.ReadDataList();

	for(vector<aan>::iterator iter = mm1.begin();
		iter != mm1.end(); ++iter)
	{
		printf("\n%s\n",(*iter).MapCreateDate);
	}*/

    //Cr.SetCreditTurn(0); //크레딧 턴 설정
	 
	int acb = Cr.LoadCreditTurn(); //크레딧 턴 로드

	CreditFont = CreateFontClass(gDevice->device, "res\\Menu.otf", Cr.LoadCredit(acb), 25, 400, 70, 870, 0);

	string nn = op.LoadOption("Language");

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	LPDIRECT3DTEXTURE9 tex3 = StageMgr::GetInst()->GetResource("Title");

	LPDIRECT3DTEXTURE9 tex1 = StageMgr::GetInst()->GetResource("Button1");

	LPDIRECT3DTEXTURE9 tex2 = StageMgr::GetInst()->GetResource("Button2");

	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));

	m_BGlist.push_back(CreateBG(gDevice, 340, 80, 600, 150, tex3));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 300,"Start",gDevice, tex1, tex2));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 430,"Option",gDevice, tex1, tex2));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 560,"Exit",gDevice, tex1, tex2));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("Menu Start",nn+".txt").c_str(), 25, 400, 100, 440, 300));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("Menu Option",nn+".txt").c_str(), 25, 400, 100, 440, 430));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("Menu Exit",nn+".txt").c_str(), 25, 400, 100, 440, 560));

	printf("\nMenu Loading Complete\n");

	time1 = clock();

	return true;
}

void Menu::Update(float gameTime)
{
	for(list<Obj*>::iterator iter = m_buttonlist.begin(); 
		iter != m_buttonlist.end(); ++iter)
	{
		int iResult = (*iter)->Update(gameTime);
		if(iResult == 1) 
		{
			StageMgr::GetInst()->SetState(IDS_STAGE_GAMESELECT, hwnd);
			return;
		}

		else if(iResult == 2) 
		{
			//StageMgr::GetInst()->SetState(IDS_STAGE_OPTION, hwnd);
			return;
		}

		else if(iResult == 3) 
		{
			PostQuitMessage(0);
		}
	}

	time2 = clock();

	if((time2 - time1) > (4 * CLOCKS_PER_SEC))
	{
		time1 = clock();
		Credit Cr;

		int acb = Cr.LoadCreditTurn(); //크레딧 턴 로드

		acb++;

		Cr.SetCreditTurn(acb); //크레딧 턴 설정

		acb = Cr.LoadCreditTurn();

		CreditFont->SetText(Cr.LoadCredit(acb));
	}
	
}

void Menu::Draw(float gameTime)
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

	CreditFont->Draw(DT_RIGHT|DT_VCENTER, D3DCOLOR_XRGB(172,46,238));

	// <- Draw Logic ->//

	gDevice->End();
	gDevice->Present();
}

void Menu::Release()
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

	delete CreditFont;
}

Obj* Menu::CreateButton(float _fx, float _fy, float _x, float _y, string _DrawId, GraphicsDevice *_gDevice, LPDIRECT3DTEXTURE9 tex, LPDIRECT3DTEXTURE9 tex2)
{
	MenuButton* AA = new MenuButton();
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex, tex2);
	AA->SetDxinput(StageMgr::GetInst()->GetDxinput());
	AA->SetDrawID(_DrawId);
	return AA;
}

Font* Menu::CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y)
{
	Font* AA = new Font();
	AA->FontOption(pd3dDevice, FontLocation, Message, FontSize, fx, fy, x, y);
	return AA;
}

Obj* Menu::CreateBG(GraphicsDevice *_gDevice, float _x, float _y, float _fx, float _fy, LPDIRECT3DTEXTURE9 tex)
{
	DrawBackGround* AA = new DrawBackGround();
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex);
	return AA;
}

void Menu::DeviceReload()
{
	m_BGlist.clear();
	m_buttonlist.clear();
	m_FontClassList.clear();

	Language sd;

	Option op;

	Credit Cr;

	MapData md;

	string nn = op.LoadOption("Language");

	gDevice = StageMgr::GetInst()->GetDevice();

	int acb = Cr.LoadCreditTurn(); //크레딧 턴 로드

	CreditFont = CreateFontClass(gDevice->device, "res\\Menu.otf", Cr.LoadCredit(acb), 25, 400, 70, 870, 0);

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	LPDIRECT3DTEXTURE9 tex3 = StageMgr::GetInst()->GetResource("Title");

	LPDIRECT3DTEXTURE9 tex1 = StageMgr::GetInst()->GetResource("Button1");

	LPDIRECT3DTEXTURE9 tex2 = StageMgr::GetInst()->GetResource("Button2");

	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));

	m_BGlist.push_back(CreateBG(gDevice, 340, 80, 600, 150, tex3));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 300,"Start",gDevice, tex1, tex2));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 430,"Option",gDevice, tex1, tex2));

	m_buttonlist.push_back(CreateButton(400, 100, 440, 560,"Exit",gDevice, tex1, tex2));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("Menu Start",nn+".txt").c_str(), 25, 400, 100, 440, 300));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("Menu Option",nn+".txt").c_str(), 25, 400, 100, 440, 430));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("Menu Exit",nn+".txt").c_str(), 25, 400, 100, 440, 560));

}
