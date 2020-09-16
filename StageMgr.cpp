#include "StageMgr.h"

//여기에 장면 헤더파일을 선언
#include "Intro.h"
#include "Menu.h"
#include "Setting.h"
#include "GameSelect.h"
#include "Single.h"
#include "CreateMap.h"
#include "GameScreen.h"
#include "GameLoading.h"

StageMgr* StageMgr::m_pInst = NULL;

StageMgr::StageMgr(void) : m_pState(NULL)
{
	gDevice = new GraphicsDevice();
}


StageMgr::~StageMgr(void)
{
	Release();
}

void StageMgr::SetState(STAGEID _STAGEID, HWND hWnd)
{
	if(m_pState != NULL)
	{
		m_pState->Release();
	}
	delete m_pState;

	switch(_STAGEID)
	{
	case IDS_STAGE_INTRO:
		m_pState = new Intro;
		printf("\nIntro 클래스 실행\n");
		break;

	case IDS_STAGE_MAIN:
		m_pState = new Menu;
		printf("\nMenu 클래스 실행\n");
		break;

	case IDS_STAGE_OPTION:
		m_pState = new Setting;
		printf("\nSetting 클래스 실행\n");
		break;

	case IDS_STAGE_GAMESELECT:
		m_pState = new GameSelect;
		printf("\nGameSelect 클래스 실행\n");
		break;

	case IDS_STAGE_SINGLEMODE:
		m_pState = new Single;
		printf("\nSingle 클래스 실행\n");
		break;

	case IDS_STAGE_CREATEMAP:
		m_pState = new CreateMap;
		printf("\nCreateMap 클래스 실행\n");
		break;

	case IDS_STAGE_MAPLOADING:
		m_pState = new GameLoading;
		printf("GameLoading 클래스 실행");
		break;

	case IDS_STAGE_GAME:
		m_pState = new GameScreen;
		printf("\nGameScreen 클래스 실행\n");
		break;
	}

	m_pState->Initialize(hWnd);
}

void StageMgr::Draw(float gameTime)
{
	m_pState -> Draw(gameTime);
}

void StageMgr::Update(float gameTime)
{
	m_pState -> Update(gameTime);
}

void StageMgr::DeviceReload()
{
	m_pState -> DeviceReload();
}

void StageMgr::Release()
{
	SAFE_DELETE(m_pState);
}
