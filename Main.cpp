#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "GraphicsDevice.h"
#include "GameSprite.h"
#include <list>
#include "Define.h"
#include "StageMgr.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "ImeMgr.h"

using namespace std;

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND g_hWnd;

HINSTANCE g_hInstance;

int g_nCmdShow;

ImeMgr imemgr;

int abab = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_nCmdShow = nCmdShow;
	g_hInstance = hInstance;
	
	// 바꿀 수 있는지 시험해보고 바꿈

	/* 디버깅용 콘솔창 */
#if _DEBUG
	FILE *fp;
	AllocConsole();
	HWND hwnd = GetConsoleWindow(); //콘솔창을 가져옴
	freopen_s(&fp, "CONIN$", "rb", stdin);
	freopen_s(&fp, "CONOUT$", "wb", stdout);
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW); //콘솔창을 맨 앞으로 당겨옴
#endif
	/* 디버깅용 콘솔창 */

	if(GenerateWindow(hInstance, nCmdShow, "BedLam", "BedLam", 1280, 720, g_hWnd))
	{
		MSG msg;

		//StageMgr::GetInst()->SetImeMgr(imemgr);

		StageMgr::GetInst()->Setwindow(false);

		StageMgr::GetInst()->SetDevice(g_hWnd);

		StageMgr::GetInst()->DeviceCleanUp();	

		StageMgr::GetInst()->SetDxinput(g_hWnd, hInstance);

		StageMgr::GetInst()->SetState(IDS_STAGE_INTRO,g_hWnd);

		while(true)
		{
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);

				DispatchMessage(&msg);			
			}

			if(msg.message == WM_QUIT) break;
			else
			{
				//업데이트와 렌더링
				if (StageMgr::GetInst()->Getdf() == D3DERR_DEVICELOST ) 
				{  // 디바이스를 잃었고 복구될수 없다
					//printf("복구 불가\n");
				} 

				else if(StageMgr::GetInst()->Getdf() == D3DERR_DEVICENOTRESET ) 
				{     // 복구 될수 있다
					if(StageMgr::GetInst()->DeviceCleanUp() == 0)
					{
						StageMgr::GetInst()->DeviceReload();	
					}
				}
				if(SUCCEEDED(StageMgr::GetInst()->Getdf()))
				{
					KeyMgr::GetInst()->CheckKey();
					StageMgr::GetInst()->Draw(0.0f);
					StageMgr::GetInst()->Update(0.0f);
					//printf("%d\n", abab);
				}			
			}
		}

		StageMgr::GetInst()->DestroyInst();

		KeyMgr::GetInst()->DestoryInst();

		ChangeDisplaySettings(NULL, 0);

		return msg.wParam;
	}

	return 0;
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd)
{
	return GenerateWindow(hInstance, nCmdShow, className, windowTitle, 0, 0, width, height,hWnd);
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd)
{
	WNDCLASSEX wcex;

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&wcex))
	{
		return false;
	}

	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_SYSMENU, x, y, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	return true;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(IMEMGR.GetMsg(hWnd, message, wParam, lParam))
	{

	}

	switch(message)
	{
	case WM_ACTIVATEAPP:
		{
			if(wParam == true)
			{								
				StageMgr::GetInst()->Setwindow(true);
			}
			else if(wParam == false)
			{
				StageMgr::GetInst()->Setwindow(false);			
			}

			return 0;
		}
	case WM_IME_COMPOSITION:
		{
			return NULL;
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}