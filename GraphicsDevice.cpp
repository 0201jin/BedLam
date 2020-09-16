#include "GraphicsDevice.h"
#include "Include.h"

GraphicsDevice::GraphicsDevice()
{
}

bool GraphicsDevice::Initialize(HWND hwnd, bool windowed)
{
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed               = TRUE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_COPY;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if(!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hwnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, 
		&device)))
	{
		return false;
	}

	//D3DXCreateSprite(device, &pd3dSprite);

	return true;
}

void GraphicsDevice::Clear(D3DCOLOR color)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void GraphicsDevice::Begin()
{
	device->BeginScene();
}

void GraphicsDevice::End()
{
	device->EndScene();
}

void GraphicsDevice::Present()
{
	device->Present(NULL, NULL, NULL, NULL);
}

GraphicsDevice::~GraphicsDevice()
{
	if(device)
	{
		device->Release();
		device = 0;
	}

	if(direct3d)
	{
		direct3d->Release();
		direct3d = 0;
	}
}

int GraphicsDevice::Cleanup()
{
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed               = TRUE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_COPY;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT hr = device->Reset(&d3dpp);

	if(!SUCCEEDED(hr))
	{
		return 1;
	}
	return 0;
	//D3DXCreateSprite(device, &pd3dSprite);
}

HRESULT GraphicsDevice::Getdf()
{
	HRESULT hr1 = device->TestCooperativeLevel();
	return hr1;
}
