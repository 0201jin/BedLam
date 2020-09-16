#pragma once
#include "Include.h"
#include "Define.h"
#include "DXInput.h"
#include "Camera.h"

class Character
{
private:
	DXInput *m_pDirectInput;
	POINT m_pt; 

public:
	void Initialize(LPDIRECT3DDEVICE9 device, float x, float y, float z);
	void Initialize(LPDIRECT3DDEVICE9 device);
	void update();
	float GetX();
	float GetY();
	float GetZ();
	D3DXVECTOR3 GetTarget();
	D3DXVECTOR3 GetUp();

	void SetTarget(D3DXVECTOR3 m_target);
	void SetUp(D3DXVECTOR3 m_up);

	void SetDxinput(DXInput *mm)
	{
		m_pDirectInput = mm;
	}

public:
	Camera camera;
	D3DXVECTOR3 position;
	D3DXVECTOR3 target;
	D3DXVECTOR3 up;

public:
	Character(void);
	~Character(void);
};

