#pragma once

#include "Include.h"
#include "Define.h"

#pragma comment(lib, "imm32.lib")

#define IMEMGR ImeMgr::Instance()

typedef std::wstring String;
using namespace std;

class ImeMgr
{
private:
	static ImeMgr *m_This;

public:
	static ImeMgr & Instance();

	bool GetMsg(HWND hWnd, UINT msg,WPARAM wparam, LPARAM lparam);

	wchar_t* GetString();

	void SetString(wchar_t* nn);

private:
	bool		GetChar(WPARAM wparam, LPARAM lparam);

	bool		GetKey(WPARAM wparam, LPARAM lparam);

	bool		GetComposition(HWND hWnd, WPARAM wparam, LPARAM lparam);

public:
	ImeMgr(void);
	~ImeMgr(void);
};

