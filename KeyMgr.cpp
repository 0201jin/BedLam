#include "KeyMgr.h"

KeyMgr* KeyMgr::m_pInst = NULL;

KeyMgr::KeyMgr(void)
{
}


KeyMgr::~KeyMgr(void)
{
}

void KeyMgr::CheckKey()
{
	m_dwKey = 0;
	if(GetAsyncKeyState(VK_LBUTTON))
		m_dwKey |= KEY_LBUTTON;

	else if(GetAsyncKeyState(VK_RBUTTON))
		m_dwKey |= KEY_RBUTTON;

	else if(GetAsyncKeyState('Q'))
		m_dwKey |= KEY_Q;

	else if(GetAsyncKeyState('W'))
		m_dwKey |= KEY_W;

	else if(GetAsyncKeyState('E'))
		m_dwKey |= KEY_E;

	else if(GetAsyncKeyState('R'))
		m_dwKey |= KEY_R;

	else if(GetAsyncKeyState('T'))
		m_dwKey |= KEY_T;

	else if(GetAsyncKeyState('Y'))
		m_dwKey |= KEY_Y;

	else if(GetAsyncKeyState('U'))
		m_dwKey |= KEY_U;

	else if(GetAsyncKeyState('I'))
		m_dwKey |= KEY_I;

	else if(GetAsyncKeyState('O'))
		m_dwKey |= KEY_O;

	else if(GetAsyncKeyState('P'))
		m_dwKey |= KEY_P;

	else if(GetAsyncKeyState('A'))
		m_dwKey |= KEY_A;

	else if(GetAsyncKeyState('S'))
		m_dwKey |= KEY_S;

	else if(GetAsyncKeyState('D'))
		m_dwKey |= KEY_D;

	else if(GetAsyncKeyState('F'))
		m_dwKey |= KEY_F;

	else if(GetAsyncKeyState('F'))
		m_dwKey |= KEY_F;

	else if(GetAsyncKeyState('F'))
		m_dwKey |= KEY_F;

	else if(GetAsyncKeyState('G'))
		m_dwKey |= KEY_G;

	else if(GetAsyncKeyState('H'))
		m_dwKey |= KEY_H;

	else if(GetAsyncKeyState('J'))
		m_dwKey |= KEY_J;

	else if(GetAsyncKeyState('K'))
		m_dwKey |= KEY_K;

	else if(GetAsyncKeyState('L'))
		m_dwKey |= KEY_L;

	else if(GetAsyncKeyState('Z'))
		m_dwKey |= KEY_Z;

	else if(GetAsyncKeyState('X'))
		m_dwKey |= KEY_X;

	else if(GetAsyncKeyState('C'))
		m_dwKey |= KEY_C;

	else if(GetAsyncKeyState('V'))
		m_dwKey |= KEY_V;

	else if(GetAsyncKeyState('B'))
		m_dwKey |= KEY_B;

	else if(GetAsyncKeyState('N'))
		m_dwKey |= KEY_N;

	else if(GetAsyncKeyState('M'))
		m_dwKey |= KEY_M;
}
