#include "ImeMgr.h"
#include <iostream>

ImeMgr *ImeMgr::m_This;

String textstring;
int gCaret;
int com;
int* comdata;

ImeMgr::ImeMgr(void)
{
	wcout.imbue(locale("korean"));
	m_This = this;
	textstring = L"";
	gCaret = 0;
	com = 0;
	comdata = new int;
	printf("\nIME MGR 클래스 실행 완료\n");
}


ImeMgr::~ImeMgr(void)
{
}

bool ImeMgr::GetMsg(HWND hWnd, UINT msg,WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_CHAR:						
		return GetChar(wparam,lparam);

	case WM_KEYDOWN:					
		return GetKey(wparam,lparam);

	case WM_IME_COMPOSITION:			
		GetComposition(hWnd,wparam, lparam);
	}

	//wcout << gCaret << " " << textstring << "\n";
	return false;
}

wchar_t* ImeMgr::GetString()
{
	return (wchar_t*)textstring.c_str();
}

void ImeMgr::SetString(wchar_t* nn)
{
	comdata = new int;
	com = 0;
	textstring = nn;
	gCaret = textstring.length();
}

bool ImeMgr::GetChar(WPARAM wparam, LPARAM lparam)
{
	if (!IsDBCSLeadByte(reinterpret_cast<BYTE&>(wparam)))
	{
		if (wparam >= 0 && wparam <= 255)
		{
			wchar_t lChar = wparam;
			switch (lChar)
			{
			case L'\r': // Enter
				comdata = new int;
				com = 0;
				break;
			case L'\b':		// 백스페이스.
				if (gCaret > 0)
				{
					textstring.pop_back();
					gCaret--;
					com = 0;
					comdata = new int;
				}
				return true;

			default:
				{
					wchar_t sert[2] = { wparam, L'\0' };
					textstring.insert(gCaret++, sert);
					com = 0;
					comdata = new int;
				}		
				return true;
			}
			return false;
		}
	}
}

bool ImeMgr::GetKey(WPARAM wparam, LPARAM lparam)
{
	switch (wparam){
	/*case VK_LEFT:
		if (gCaret > 0)
		{
			comdata = new int;
			com = 0;
			gCaret--;
		}
		return true;

	case VK_RIGHT:
		if (static_cast<unsigned>(gCaret) < textstring.length())
		{
			comdata = new int;
			com = 0;
			gCaret++;
		}
		return true;*/

	case VK_DELETE:
		if (static_cast<unsigned>(gCaret) < textstring.length())
		{
			comdata = new int;
			com = 0;
			textstring.erase(gCaret, 1);
		}
		return true;

	//case VK_HOME:
	//	com = 0;
	//	comdata = new int;
	//	gCaret = 0;
	//	return true;

	//case VK_END:
	//	comdata = new int;
	//	com = 0;
	//	gCaret = textstring.length();
	//	return true;

	//case VK_PROCESSKEY:
	//	if(lparam == 0x14B0001) // 좌측
	//	{
	//		comdata = new int;
	//		com = 0;
	//		if (gCaret > 0)
	//		{
	//			gCaret--;
	//		}
	//	}
	//	else if(lparam == 0x14D0001) // 우측.
	//	{
	//		comdata = new int;
	//		com = 0;
	//		if (static_cast<unsigned>(gCaret) < textstring.length())
	//		{
	//			gCaret++;
	//		}
	//	}

	//	return true;
	}
	return true;
}

bool ImeMgr::GetComposition(HWND hWnd, WPARAM wparam, LPARAM lparam)
{
	HIMC	hImc = ImmGetContext(hWnd);
	int nLenght = 0;

	//cout << wparam << "\n";

	if(lparam & GCS_RESULTSTR){		
		nLenght = ImmGetCompositionStringW(hImc, GCS_COMPSTR, NULL, 0) / sizeof(wchar_t);
		if(nLenght > 0)
		{
			wchar_t* lBuffer = new wchar_t[nLenght + 1];
			int lResult = ImmGetCompositionStringW(hImc, GCS_RESULTSTR, lBuffer, nLenght * sizeof(wchar_t));
			lBuffer[nLenght] = L'\0';

			if(lResult == 0) return false;

			textstring.pop_back();

			gCaret--;

			textstring.insert(gCaret, lBuffer);

			gCaret++;

			com = 0;

			comdata = new int;

			delete[] lBuffer;	

			ImmReleaseContext(hWnd, hImc);	
		}
	}
	else if(lparam & GCS_COMPSTR)
	{
		nLenght = ImmGetCompositionStringW(hImc, GCS_COMPSTR, NULL, 0) / sizeof(wchar_t);

		if(wparam == 27)
		{
			com = 0;
			comdata = new int;
			wchar_t* lBuffer = new wchar_t[nLenght + 1];
			int lResult = ImmGetCompositionStringW(hImc, GCS_COMPSTR, lBuffer, nLenght * sizeof(wchar_t));
			lBuffer[nLenght] = L'\0';

			textstring.pop_back();

			gCaret--;

			textstring.insert(gCaret, lBuffer);

			delete[] lBuffer;

			ImmReleaseContext(hWnd, hImc);	
		}
		if(nLenght > 0)
		{
			wchar_t* lBuffer = new wchar_t[nLenght + 1];
			int lResult = ImmGetCompositionStringW(hImc, GCS_COMPSTR, lBuffer, nLenght * sizeof(wchar_t));
			lBuffer[nLenght] = L'\0';

			comdata[com] = wparam;

			if(com > 0 && wparam != 27)
			{
				textstring.pop_back();
				gCaret--;
				if(comdata[com-2] != comdata[com])
				{
					com++;
				}
				else
				{
					com--;
				}	
			}
			else
			{
				com++;
			}

			textstring.insert(gCaret, lBuffer);

			gCaret++;

			delete[] lBuffer;	

			ImmReleaseContext(hWnd, hImc);	
		}
	}
	return true;
}

ImeMgr & ImeMgr::Instance()
{
	return *m_This;
}

static ImeMgr & Instance()
{

}