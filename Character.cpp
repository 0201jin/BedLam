#include "Character.h"

Character::Character(void)
{
}


Character::~Character(void)
{
}

void Character::Initialize(LPDIRECT3DDEVICE9 device, float x, float y, float z)
{
	camera.Initialize(device);

	position.x = x;
	position.y = y;
	position.z = z;
	target = camera.GetCameraTarget();
	up = camera.GetCameraUp();

	m_pt.x = 1280 / 2;
	m_pt.y = 720 / 2;
	ClientToScreen(g_hWnd, &m_pt);
	SetCursorPos(m_pt.x, m_pt.y);

	camera.SetCamera(position, target, up);
}

void Character::Initialize( LPDIRECT3DDEVICE9 device)
{
	camera.Initialize(device);

	camera.SetCamera(position, target, up);
}

void Character::update()
{
	POINT  pt;                                      //현재 마우스 위치 , m_pt는 화면중앙 좌표
	GetCursorPos(&pt);

	if(pt.x - m_pt.x != 0)
	{
		camera.RotationCross((pt.x - m_pt.x) / 500.0f);
	}

	if(pt.y - m_pt.y != 0)
	{
		camera.RotationUp((pt.y - m_pt.y) / 500.0f);
	}

	//다시 화면의 중앙으로 마우스를 셋팅
	SetCursorPos(m_pt.x , m_pt.y);

	if(m_pDirectInput->KeyProcess(DIK_W))
	{
		camera.FrontWalk(0.5);
	}
	if(m_pDirectInput->KeyProcess(DIK_S))
	{
		camera.FrontWalk(-0.5);
	}
	if(m_pDirectInput->KeyProcess(DIK_A))
	{
		camera.SideWalk(-0.5);
	}
	if(m_pDirectInput->KeyProcess(DIK_D))
	{
		camera.SideWalk(0.5);
	}
	if (m_pDirectInput->KeyProcess(DIK_ESCAPE))
	{
		exit(0);
	}

	position = camera.GetCameraPosition();
	target = camera.GetCameraTarget();
	up = camera.GetCameraUp();
}

float Character::GetX()
{
	return position.x;
}

float Character::GetY()
{
	return position.y;
}

float Character::GetZ()
{
	return position.z;
}

D3DXVECTOR3 Character::GetTarget()
{
	return target;
}

D3DXVECTOR3 Character::GetUp()
{
	return up;
}
