#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include <d3d9.h>
#include <d3dx9.h>

class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	bool Initialize(HWND hWnd, bool windowed);
	void Clear(D3DCOLOR color);
	void Begin();
	void End();
	void Present();
	int Cleanup();
	HRESULT Getdf();

	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE pd3dSprite;
private:
	LPDIRECT3D9 direct3d;
};

#endif