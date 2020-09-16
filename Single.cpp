#include "Single.h"
#include "DrawBackGround.h"
#include "GraphicsDevice.h"
#include "Language.h"
#include "Option.h"
#include "StageMgr.h"
#include "SingleButton.h"

Single::Single(void)
{
}


Single::~Single(void)
{
	Release();
}

bool Single::Initialize(HWND hWnd)
{
	gDevice = StageMgr::GetInst()->GetDevice();

	Language sd;

	Option op;

	string nn = op.LoadOption("Language");

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	LPDIRECT3DTEXTURE9 tex1 = StageMgr::GetInst()->GetResource("Button1");

	LPDIRECT3DTEXTURE9 tex2 = StageMgr::GetInst()->GetResource("Button2");

	LPDIRECT3DTEXTURE9 tex3 = StageMgr::GetInst()->GetResource("ListBox");

	LPDIRECT3DTEXTURE9 tex5 = StageMgr::GetInst()->GetResource("ListBox_Scroll_Button");

	LPDIRECT3DTEXTURE9 tex6 = StageMgr::GetInst()->GetResource("ItemBox");
	
	aan mm;

	mm.MapName = "hhc";

	mm.MapCreateDate = "hhc";

	mm.PlayTime = "hhc";

	mm.MapGameMode = "hhc";

	m_Maplist.push_back(mm);

	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));

	m_buttonlist.push_back(CreateButton(400, 100, 0, 600,"Back",gDevice, tex1, tex2)); //第肺啊扁

	m_buttonlist.push_back(CreateButton(400, 100, 440, 600,"Create",gDevice, tex1, tex2)); //甘 积己

	m_buttonlist.push_back(CreateButton(400, 100, 880, 600,"Delete",gDevice, tex1, tex2)); //甘 昏力
	
	m_ListBoxlist.push_back(CreateList(gDevice->device, 500, 400, 50, 50, tex3, tex5, tex6));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("SingleMode Back",nn+".txt").c_str(), 25, 400, 100, 0, 600)); //第肺啊扁

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("SingleMode CreateMap",nn+".txt").c_str(), 25, 400, 100, 440, 600)); //甘 积己

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("SingleMode DeleteMap",nn+".txt").c_str(), 25, 400, 100, 880, 600)); //甘 昏力

	return true;
}

void Single::Update(float gameTime)
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
			StageMgr::GetInst()->SetState(IDS_STAGE_CREATEMAP, hwnd);
			return;
		}

		else if(iResult == 3) 
		{
			//StageMgr::GetInst()->SetState(IDS_STAGE_MAIN, hwnd);
			return;
		}
	}

	for(list<Obj*>::iterator iter = m_ListBoxlist.begin(); 
		iter != m_ListBoxlist.end(); ++iter)
	{
		int iResult = (*iter)->Update(gameTime);
	}
}

void Single::Draw(float gameTime)
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

	for(list<Obj*>::iterator iter = m_ListBoxlist.begin();
		iter != m_ListBoxlist.end(); ++iter)
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

void Single::Release()
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

	for(list<Obj*>::iterator iter = m_ListBoxlist.begin();
		iter != m_ListBoxlist.end(); ++iter)
	{
		delete (*iter);
	}

	for(vector<Font*>::iterator iter = m_FontClassList.begin();
		iter != m_FontClassList.end(); ++iter)
	{
		delete (*iter);
	}
}

Obj* Single::CreateButton(float _fx, float _fy, float _x, float _y, string _DrawId, GraphicsDevice *_gDevice, LPDIRECT3DTEXTURE9 tex, LPDIRECT3DTEXTURE9 tex2)
{
	SingleButton* AA = new SingleButton();
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex, tex2);
	AA->SetDxinput(StageMgr::GetInst()->GetDxinput());
	AA->SetDrawID(_DrawId);
	return AA;
}

Font* Single::CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y)
{
	Font* AA = new Font();
	AA->FontOption(pd3dDevice, FontLocation, Message, FontSize, fx, fy, x, y);
	return AA;
}

Obj* Single::CreateBG(GraphicsDevice *_gDevice, float _x, float _y, float _fx, float _fy, LPDIRECT3DTEXTURE9 tex)
{
	DrawBackGround* AA = new DrawBackGround();
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex);
	return AA;
}

Obj* Single::CreateList(LPDIRECT3DDEVICE9 device, float width, float height, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex3, LPDIRECT3DTEXTURE9 tex)
{
	ListBox* AA = new ListBox();
	for(list<aan>::iterator iter = m_Maplist.begin();
		iter != m_Maplist.end(); ++iter)
	{
		AA->AddListItem(*iter);
	}
	AA->Initailize(device, width, height, x, y, tex1, tex3, tex);
	AA->SetDxinput(StageMgr::GetInst()->GetDxinput());
	return AA;
}

void Single::DeviceReload()
{
	gDevice = StageMgr::GetInst()->GetDevice();

	Language sd;

	Option op;

	string nn = op.LoadOption("Language");

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	LPDIRECT3DTEXTURE9 tex1 = StageMgr::GetInst()->GetResource("Button1");

	LPDIRECT3DTEXTURE9 tex2 = StageMgr::GetInst()->GetResource("Button2");

	LPDIRECT3DTEXTURE9 tex3 = StageMgr::GetInst()->GetResource("ListBox");

	LPDIRECT3DTEXTURE9 tex5 = StageMgr::GetInst()->GetResource("ListBox_Scroll_Button");

	LPDIRECT3DTEXTURE9 tex6 = StageMgr::GetInst()->GetResource("ItemBox");

	m_Maplist.clear();
	m_ListBoxlist.clear();
	m_FontClassList.clear();
	m_buttonlist.clear();
	m_BGlist.clear();

	aan mm;

	mm.MapName = "hhc";

	mm.MapCreateDate = "hhc";

	mm.PlayTime = "hhc";

	mm.MapGameMode = "hhc";

	m_Maplist.push_back(mm);

	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));

	m_buttonlist.push_back(CreateButton(400, 100, 0, 600,"Back",gDevice, tex1, tex2)); //第肺啊扁

	m_buttonlist.push_back(CreateButton(400, 100, 440, 600,"Create",gDevice, tex1, tex2)); //甘 积己

	m_buttonlist.push_back(CreateButton(400, 100, 880, 600,"Delete",gDevice, tex1, tex2)); //甘 昏力

	m_ListBoxlist.push_back(CreateList(gDevice->device, 500, 400, 50, 50, tex3, tex5, tex6));

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("SingleMode Back",nn+".txt").c_str(), 25, 400, 100, 0, 600)); //第肺啊扁

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("SingleMode CreateMap",nn+".txt").c_str(), 25, 400, 100, 440, 600)); //甘 积己

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("SingleMode DeleteMap",nn+".txt").c_str(), 25, 400, 100, 880, 600)); //甘 昏力

}
