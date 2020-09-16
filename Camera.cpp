#include "Camera.h"


Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}

void Camera::Initialize(LPDIRECT3DDEVICE9 device)
{
	g_device = device;

	position = D3DXVECTOR3(-0.5f, -0.5f, 2.0f);
	target = D3DXVECTOR3 (-0.5f, -0.5f, -0.5f);
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	g_device->SetTransform(D3DTS_VIEW, &V);
	ShowCursor(false);
}

void Camera::SetCamera(D3DXVECTOR3 gposition, D3DXVECTOR3 gtarget, D3DXVECTOR3 gup)
{
	position = gposition;
	target = gtarget;
	up = gup;
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	g_device->SetTransform(D3DTS_VIEW, &V);
}

D3DXVECTOR3 Camera::GetCameraPosition()
{
	return position;
}

D3DXVECTOR3 Camera::GetCameraTarget()
{
	return target;
}

D3DXVECTOR3 Camera::GetCameraUp()
{
	return up;
}

void Camera::FrontWalk(float fSpeed)
{
	D3DXVECTOR3  vView;
	vView = target - position;

	D3DXVec3Normalize(&vView, &vView);

	position += vView * fSpeed;
	target += vView * fSpeed;

	D3DXMATRIX V;

	//Ä«¸Þ¶ó
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	g_device->SetTransform( D3DTS_VIEW, &V );
}

void Camera::SideWalk(float fSpeed)
{
	D3DXVECTOR3  vView;
	D3DXVECTOR3  vCross;
	vView = target - position;
	D3DXVec3Cross( &vCross, &up , &vView );
	D3DXVec3Normalize(&vCross, &vCross);
	D3DXVec3Normalize(&vView, &vView);

	position  += vCross * fSpeed;
	target += vCross * fSpeed;

	D3DXMATRIX V;

	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	g_device->SetTransform( D3DTS_VIEW, &V );
}

void Camera::RotationCross(float fAngle)
{
	D3DXVECTOR3  vView;
	D3DXMATRIXA16 matRot;

	vView = target - position;

	D3DXMatrixRotationAxis(&matRot, &up, fAngle);
	D3DXVec3TransformCoord(&vView, &vView, &matRot);

	target = position + vView;

	D3DXMATRIX V;

	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	g_device->SetTransform( D3DTS_VIEW, &V );
}

void Camera::RotationUp(float fAngle)
{
	D3DXVECTOR3  vView;
	D3DXVECTOR3  vCross;
	D3DXMATRIXA16 matRot;

	vView = target - position;

	D3DXVec3Cross(&vCross, &up, &vView);
	D3DXMatrixRotationAxis(&matRot, &vCross, fAngle);
	D3DXVec3TransformCoord(&vView, &vView, &matRot);

	if(vView.y >= -10 && vView.y <= 10)
	{
		target = position + vView;

		D3DXMATRIX V;

		D3DXMatrixLookAtLH(&V, &position, &target, &up);
		g_device->SetTransform( D3DTS_VIEW, &V );
	}
}
