#pragma once
#include "Include.h"

class Camera
{
private:
	LPDIRECT3DDEVICE9 g_device;
	D3DXVECTOR3 position;
	D3DXVECTOR3 target;
	D3DXVECTOR3 up;

public:
	void Initialize(LPDIRECT3DDEVICE9 device);
	void SetCamera(D3DXVECTOR3 position, D3DXVECTOR3 target, D3DXVECTOR3 up);
	void FrontWalk(float fSpeed);
	void SideWalk(float fSpeed);
	void RotationCross(float fAngle);
	void RotationUp(float fAngle);
	D3DXVECTOR3 GetCameraPosition();
	D3DXVECTOR3 GetCameraTarget();
	D3DXVECTOR3 GetCameraUp();

public:
	Camera(void);
	~Camera(void);
};

