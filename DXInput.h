#pragma once
#pragma comment(lib, "DInput8.lib")
#pragma comment(lib, "Dxguid.lib")

#include <Windows.h>
#include <DInput.h>

class DXInput
{
public: //함수
	bool InitDirectInput(HINSTANCE hInst, HWND hWnd, bool keyboard, bool mouse);
	bool KeyProcess(BYTE key);
	bool KeyProcess(BYTE* key);
	bool MouseProcess(DIMOUSESTATE* MouseState);
	void DeviceAcquire();
	void DeviceUnacquire();
	void Release();

private: //변수
	LPDIRECTINPUT8 m_pDi;
	LPDIRECTINPUTDEVICE8 m_pKey;
	LPDIRECTINPUTDEVICE8 m_pMouse;
	BYTE m_KeyState[256];
	HRESULT m_hr;

public: //생성자, 소멸자
	DXInput(void);
	~DXInput(void);
};

