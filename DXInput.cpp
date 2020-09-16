#include "DXInput.h"


DXInput::DXInput(void)
{
	m_pKey = NULL;
	m_pMouse = NULL;
	m_pDi = NULL;
}


DXInput::~DXInput(void)
{
	Release();
}

bool DXInput::InitDirectInput(HINSTANCE hInst, HWND hWnd, bool keyboard, bool mouse)
{
	if(FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDi, NULL)))
	{
		return false;
	}

	if(keyboard)
	{
		if(FAILED(m_pDi->CreateDevice(GUID_SysKeyboard, &m_pKey, NULL)))
			return false;
		if(FAILED(m_pKey->SetDataFormat(&c_dfDIKeyboard)))
			return false;
		if(FAILED(m_pKey->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY)))
			return false;
		while(m_pKey->Acquire() == DIERR_INPUTLOST);
	}
	if(mouse)
	{
		if(FAILED(m_pDi->CreateDevice(GUID_SysMouse, &m_pMouse, NULL)))
			return false;
		if(FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
			return false;
		if(FAILED(m_pMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			return false;
		while(m_pMouse->Acquire() == DIERR_INPUTLOST);
	}

	return true;
}

bool DXInput::KeyProcess(BYTE key)
{
	ZeroMemory(m_KeyState, sizeof(m_KeyState));

	m_hr = m_pKey->GetDeviceState(sizeof(m_KeyState), m_KeyState);

	if(FAILED(m_hr))
	{
		m_hr = m_pKey->Acquire();
		while(m_hr == DIERR_INPUTLOST)
			m_pKey->Acquire();

		return false;
	}

	if(m_KeyState[key] & 0x80)
	{
		return true;
	}

	return false;
}

bool DXInput::KeyProcess(BYTE* key)
{
	ZeroMemory(key, 256);

	m_hr = m_pKey->GetDeviceState(256, key);

	if(FAILED(m_hr))
	{
		m_hr = m_pKey->Acquire();
		while(m_hr == DIERR_INPUTLOST)
			m_pKey->Acquire();

		return false;
	}

	return true;
}

bool DXInput::MouseProcess(DIMOUSESTATE* MouseState)
{
	ZeroMemory(MouseState, sizeof(DIMOUSESTATE));

	m_hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), MouseState);

	if(FAILED(m_hr))
	{
		m_hr = m_pMouse->Acquire();
		while(m_hr == DIERR_INPUTLOST)
			m_pMouse->Acquire();
		return false;
	}

	return true;
}

void DXInput::DeviceAcquire()
{
	if(m_pKey)
		m_pKey->Acquire();
	if(m_pMouse)
		m_pMouse->Acquire();
}

void DXInput::DeviceUnacquire()
{
	if(m_pKey)
		m_pKey->Unacquire();
	if(m_pMouse)
		m_pMouse->Acquire();
}

void DXInput::Release()
{
	if(m_pDi)
	{
		if(m_pKey)
		{
			m_pKey->Unacquire();
			m_pKey->Release();
			m_pKey = NULL;
		}
		if(m_pMouse)
		{
			m_pMouse->Unacquire();
			m_pMouse->Release();
			m_pMouse = NULL;
		}

		m_pDi->Release();
		m_pDi = NULL;
	}
}
