#include "CreateMap.h"
#include "DrawBackGround.h"
#include "GraphicsDevice.h"
#include "Language.h"
#include "Option.h"
#include "StageMgr.h"
#include "CreateMapButton.h"
#include "CreateMapCreateButton.h"
#include "TextBox.h"

CreateMap::CreateMap(void)
{
}


CreateMap::~CreateMap(void)
{
	Release();
}

bool CreateMap::Initialize(HWND hWnd)
{
	gDevice = StageMgr::GetInst()->GetDevice();

	Language sd;

	Option op;

	string nn = op.LoadOption("Language");

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	LPDIRECT3DTEXTURE9 tex1 = StageMgr::GetInst()->GetResource("Button1");

	LPDIRECT3DTEXTURE9 tex2 = StageMgr::GetInst()->GetResource("Button2");

	LPDIRECT3DTEXTURE9 tex5 = StageMgr::GetInst()->GetResource("TextBox");

	LPDIRECT3DTEXTURE9 tex6 = StageMgr::GetInst()->GetResource("TextBox1");

	LPDIRECT3DTEXTURE9 tex3 = StageMgr::GetInst()->GetResource("CreateButton1");

	LPDIRECT3DTEXTURE9 tex4 = StageMgr::GetInst()->GetResource("CreateButton2");



	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));

	m_buttonlist.push_back(CreateButton(400, 100, 80, 600, "Back", gDevice, tex1, tex2)); //취소

	m_buttonlist.push_back(CreateButton(400, 100, 800, 600, "Create", gDevice, tex1, tex2)); //만들기

	m_MapTypeButtonList.push_back(CreateMapTypeButton(500, 80, 390, 400, "GameMode", gDevice, tex3, tex4)); //맵 타입 버튼

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("CreateMap Back", nn + ".txt").c_str(), 25, 400, 100, 80, 600)); //취소

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("CreateMap CreateMap", nn + ".txt").c_str(), 25, 400, 100, 800, 600)); //만들기

	m_TextBoxlist = CreateTextBox(gDevice->device, 390, 150, tex5, tex6, hwnd, "textbox", L"Map Name"); //텍스트 박스

	//mapmgr.CreateMap(300, "wilde");

	return true;
}

void CreateMap::Update(float gameTime)
{
	for (list<Obj*>::iterator iter = m_buttonlist.begin();
		iter != m_buttonlist.end(); ++iter)
	{
		int iResult = (*iter)->Update(gameTime);
		if (iResult == 1)
		{
			StageMgr::GetInst()->SetState(IDS_STAGE_SINGLEMODE, hwnd);
			return;
		}

		else if (iResult == 2)
		{
			//맵 데이터를 저장한 데이터 파일을 만든다.

			mapmgr.CreateMap(300, m_TextBoxlist->GetText());
			StageMgr::GetInst()->SetMapString(m_TextBoxlist->GetText());

			StageMgr::GetInst()->SetState(IDS_STAGE_GAME, hwnd); //원래는 게임 로딩창으로 넘어가야함	

			return;
		}
	}

	for (list<Obj*>::iterator iter = m_MapTypeButtonList.begin();
		iter != m_MapTypeButtonList.end(); ++iter)
	{
		int iResult = (*iter)->Update(gameTime);
	}

	m_TextBoxlist->Update(gameTime);
}

void CreateMap::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(255, 255, 255));
	gDevice->Begin();

	// <- Draw Logic ->//

	for (list<Obj*>::iterator iter = m_BGlist.begin();
		iter != m_BGlist.end(); ++iter)
	{
		(*iter)->Draw(gameTime);
	}

	for (list<Obj*>::iterator iter = m_buttonlist.begin();
		iter != m_buttonlist.end(); ++iter)
	{
		(*iter)->Draw(gameTime);
	}

	for (list<Obj*>::iterator iter = m_MapTypeButtonList.begin();
		iter != m_MapTypeButtonList.end(); ++iter)
	{
		(*iter)->Draw(gameTime);
	}

	m_TextBoxlist->Draw(gameTime);

	for (vector<Font*>::iterator iter = m_FontClassList.begin();
		iter != m_FontClassList.end(); ++iter)
	{
		(*iter)->Draw(DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	}

	// <- Draw Logic ->//

	gDevice->End();
	gDevice->Present();
}

void CreateMap::Release()
{
	for (list<Obj*>::iterator iter = m_BGlist.begin();
		iter != m_BGlist.end(); ++iter)
	{
		delete (*iter);
	}

	for (list<Obj*>::iterator iter = m_buttonlist.begin();
		iter != m_buttonlist.end(); ++iter)
	{
		delete (*iter);
	}

	for (list<Obj*>::iterator iter = m_MapTypeButtonList.begin();
		iter != m_MapTypeButtonList.end(); ++iter)
	{
		delete (*iter);
	}

	for (vector<Font*>::iterator iter = m_FontClassList.begin();
		iter != m_FontClassList.end(); ++iter)
	{
		delete (*iter);
	}

	delete m_TextBoxlist;
}

Obj* CreateMap::CreateButton(float _fx, float _fy, float _x, float _y, string _DrawId, GraphicsDevice* _gDevice, LPDIRECT3DTEXTURE9 tex, LPDIRECT3DTEXTURE9 tex2)
{
	CreateMapButton* AA = new CreateMapButton();
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex, tex2);
	AA->SetDxinput(StageMgr::GetInst()->GetDxinput());
	AA->SetDrawID(_DrawId);
	return AA;
}

Font* CreateMap::CreateFontClass(LPDIRECT3DDEVICE9 pd3dDevice, std::string FontLocation, std::string Message, int FontSize, int fx, int fy, int x, int y)
{
	Font* AA = new Font();
	AA->FontOption(pd3dDevice, FontLocation, Message, FontSize, fx, fy, x, y);
	return AA;
}

Obj* CreateMap::CreateBG(GraphicsDevice* _gDevice, float _x, float _y, float _fx, float _fy, LPDIRECT3DTEXTURE9 tex)
{
	DrawBackGround* AA = new DrawBackGround();
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex);
	return AA;
}

Obj* CreateMap::CreateMapTypeButton(float _fx, float _fy, float _x, float _y, string _DrawId, GraphicsDevice* _gDevice, LPDIRECT3DTEXTURE9 tex, LPDIRECT3DTEXTURE9 tex2)
{
	CreateMapCreateButton* AA = new CreateMapCreateButton();
	AA->SetDrawID(_DrawId);
	AA->Initailize(_gDevice->device, _fx, _fy, _x, _y, tex, tex2);
	AA->SetDxinput(StageMgr::GetInst()->GetDxinput());
	return AA;
}

Obj* CreateMap::CreateTextBox(LPDIRECT3DDEVICE9 device, float x, float y, LPDIRECT3DTEXTURE9 tex1, LPDIRECT3DTEXTURE9 tex2, HWND hwnd, string _DrawId, String message)
{
	TextBox* AA = new TextBox();
	AA->SetDrawID(_DrawId);
	AA->Initailize(device, x, y, tex1, tex2, hwnd, message);
	AA->SetDxinput(StageMgr::GetInst()->GetDxinput());
	return AA;
}

void CreateMap::DeviceReload()
{
	gDevice = StageMgr::GetInst()->GetDevice();

	m_BGlist.clear();
	m_buttonlist.clear();
	m_MapTypeButtonList.clear();
	m_FontClassList.clear();
	m_TextBoxlist->Release();

	Language sd;

	Option op;

	string nn = op.LoadOption("Language");

	LPDIRECT3DTEXTURE9 tex = StageMgr::GetInst()->GetResource("Background");

	LPDIRECT3DTEXTURE9 tex1 = StageMgr::GetInst()->GetResource("Button1");

	LPDIRECT3DTEXTURE9 tex2 = StageMgr::GetInst()->GetResource("Button2");

	LPDIRECT3DTEXTURE9 tex3 = StageMgr::GetInst()->GetResource("CreateButton1");

	LPDIRECT3DTEXTURE9 tex4 = StageMgr::GetInst()->GetResource("CreateButton2");

	LPDIRECT3DTEXTURE9 tex5 = StageMgr::GetInst()->GetResource("TextBox");

	LPDIRECT3DTEXTURE9 tex6 = StageMgr::GetInst()->GetResource("TextBox1");

	m_BGlist.push_back(CreateBG(gDevice, 0, 0, 1280, 720, tex));

	m_buttonlist.push_back(CreateButton(400, 100, 80, 600, "Back", gDevice, tex1, tex2)); //취소

	m_buttonlist.push_back(CreateButton(400, 100, 800, 600, "Create", gDevice, tex1, tex2)); //만들기

	m_MapTypeButtonList.push_back(CreateMapTypeButton(500, 80, 390, 400, "GameMode", gDevice, tex3, tex4)); //맵 타입 버튼

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("CreateMap Back", nn + ".txt").c_str(), 25, 400, 100, 80, 600)); //취소

	m_FontClassList.push_back(CreateFontClass(gDevice->device, "res\\Menu.otf", sd.LoadLanguage("CreateMap CreateMap", nn + ".txt").c_str(), 25, 400, 100, 800, 600)); //만들기

	m_TextBoxlist = CreateTextBox(gDevice->device, 390, 150, tex5, tex6, hwnd, "textbox", L"Map Name"); //텍스트 박스

}
