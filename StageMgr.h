#pragma once

#include "Define.h"
#include "Stage.h"
#include "GraphicsDevice.h"
#include "DXInput.h"
#include "Include.h"
#include "ImeMgr.h"
#include "MapMgr.h"

class Stage;
class StageMgr
{
private:
	Stage* m_pState;
	GraphicsDevice* gDevice;
	DXInput* gDxinput;
	map<string, LPDIRECT3DTEXTURE9> TextureDB;
	list<string> location;
	HINSTANCE m_hInstance;
	bool window = true;
	string sMapString;
	//ImeMgr imemgr;

public: //window 활성/비활성
	void Setwindow(bool win)
	{
		window = win;
	}

	bool Getwindow()
	{
		return window;
	}

	void SetMapString(string mapName)
	{
		sMapString = mapName;
	}

	string GetMapString()
	{
		return sMapString;
	}

public: //textureDB 함수 모음
	void AddResource(string name, string Location) 
	{
		LPDIRECT3DTEXTURE9 texture;
		//텍스쳐를 만든 다음 추가

		if(!SUCCEEDED(D3DXCreateTextureFromFileEx(gDevice->device, Location.c_str(),D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, 
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture)))
		{
			printf("\n텍스쳐 생성 실패\n");
		}

		printf("\n텍스쳐 생성 성공\n");

		location.push_back(Location);

		TextureDB.insert(make_pair(name,texture));
	}

	void RefreshResource()
	{
		TextureDB.clear();
		/*for(list<string>::iterator iter = location.begin();
		iter != location.end(); ++iter)
		{
		LPDIRECT3DTEXTURE9 texture;

		if(!SUCCEEDED(D3DXCreateTextureFromFileEx(gDevice->device, (*iter).c_str(),D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, 
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture)))
		{
		printf("\n텍스쳐 생성 실패\n");
		}
		printf("%s\n", (*iter).c_str());
		}	*/
	}

	void LoadResource()
	{
		AddResource("Background", "res\\Intro.png");

		AddResource("Title", "res\\Title.png");

		AddResource("Button1", "res\\button.png");

		AddResource("Button2", "res\\button1.png");

		AddResource("ListBox", "res\\ListBox.png");

		AddResource("ListBox_Scroll_Button", "res\\ListBox_Scroll_But.png");

		AddResource("ItemBox", "res\\ItemBox.png");

		AddResource("CreateButton1", "res\\CreateButton.png");

		AddResource("CreateButton2", "res\\CreateButton1.png");

		AddResource("TextBox", "res\\TextBox.png");

		AddResource("TextBox1", "res\\TextBox1.png");
	}

	bool CheckResource(string name)
	{
		if(TextureDB.find(name) == TextureDB.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	LPDIRECT3DTEXTURE9 GetResource(string name)
	{
		return TextureDB.at(name);
	}

	int GetSize()
	{
		return TextureDB.size();
	}

public: //스테이트
	Stage* GetState() { return m_pState; } 

public: //디바이스
	void SetDevice(HWND hWnd)
	{ 	
		if(!gDevice->Initialize(hWnd, true))
		{
			printf("\n디바이스 생성 실패\n");

			MessageBox(hWnd,"디바이스 생성 오류!","오류!",0);

			//PostQuitMessage(0);
		}
		else
		{
			printf("\n디바이스 생성 성공\n");
		}
	}

	GraphicsDevice* GetDevice()
	{
		return gDevice;
	}

	HRESULT Getdf()
	{
		HRESULT hr = gDevice->Getdf();
		return hr;
	}

	int DeviceCleanUp()
	{
		return gDevice->Cleanup();
	}

public: //DXInput
	void SetDxinput(HWND hWnd, HINSTANCE hInstance)
	{
		gDxinput = new DXInput();

		if(!gDxinput->InitDirectInput(hInstance, hWnd, true, true))
		{
			return;
		}
	}

	DXInput* GetDxinput()
	{
		return gDxinput;
	}

	//public: //IME MGR
	//	void SetImeMgr(ImeMgr imemgr)
	//	{
	//		m_imemgr = imemgr;
	//	}
	//
	//	ImeMgr GetImeMgr()
	//	{
	//		return m_imemgr;
	//	}

public:
	void SetState(STAGEID _STAGEID, HWND hWnd);
	void Draw(float gameTime);
	void Update(float gameTime);
	void Release();
	void DeviceReload();

private:
	static StageMgr* m_pInst;
public:
	static StageMgr* GetInst()
	{
		if(m_pInst == NULL)
		{
			m_pInst = new StageMgr;
		}
		return m_pInst;
	}
	void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}
public:
	StageMgr(void);
	~StageMgr(void);
};

