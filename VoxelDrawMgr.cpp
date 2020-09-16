#include "VoxelDrawMgr.h"

int Width  = 1280;
int Height = 720;

LPDIRECT3DSURFACE9 z_buffer = NULL;
const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

VoxelDrawMgr::VoxelDrawMgr(void)
{
}


VoxelDrawMgr::~VoxelDrawMgr(void)
{
}

void VoxelDrawMgr::nDraw()
{
	// ----------------------------------------- //
	// 입방체 회전시키기
	// ----------------------------------------- //

	//D3DXMATRIX Rx, Ry;

	//// x축 45도 회전
	//static float x = 0.0f;
	////D3DXMatrixRotationX(&Rx, 3.14f / 2.5f);
	//D3DXMatrixRotationX(&Rx, x);
	//x += 0.1;

	//if( x>= 6.28f )
	//	x = 0.0f;

	//// 각 프레임당 y 회전 증가
	//static float y = 0.0f;
	//D3DXMatrixRotationY(&Ry, y);
	//y += 0.1;

	//// 각도가 2*PI 에 이르면 0으로 초기화한다.
	//if( y>= 6.28f )
	//	y = 0.0f;

	//// 회전을 결합한다.
	//D3DXMATRIX p = Rx * Ry;

	//Device->SetTransform(D3DTS_WORLD, &p);

	// ----------------------------------------- //
	// 장면 그리기
	// ----------------------------------------- //

	// 후면 버퍼를 소거하고 깊이 버퍼, 스텐실 버퍼를 각각 흰색(0xFFFFFFFF)과 1.0으로 초기화한다
	//Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);

	//Device->BeginScene(); // 장면 그리기 시작!

	Device->SetTexture(0,NULL);
	Device->SetStreamSource(0, VB, 0, sizeof(Vertex)); // 스트림 소스를 지정한다
	Device->SetIndices(IB); // 인덱스 버퍼 포인터의 복사본을 전달한다
	Device->SetFVF(Vertex::FVF); // 버텍스 포맷을 FVF로 지정한다
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12); // 인덱스 정보를 이용해 기본형 그리기!
	//Device->EndScene(); // 장면 그리기 끝!

	// 후면 버퍼를 선언한다
	//Device->Present(0, 0, 0, 0);
}

void VoxelDrawMgr::Draw(float gameTime) //여기가 그림 그리는 함수
{
	Device->SetTexture(0,NULL);
	Device->SetStreamSource(0, VB, 0, sizeof(Vertex)); // 스트림 소스를 지정한다
	Device->SetIndices(IB); // 인덱스 버퍼 포인터의 복사본을 전달한다
	Device->SetFVF(Vertex::FVF); // 버텍스 포맷을 FVF로 지정한다
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12); // 인덱스 정보를 이용해 기본형 그리기!
}

void VoxelDrawMgr::Initialize(LPDIRECT3DDEVICE9 device, float x, float y, float z)
{
	D3DPRESENT_PARAMETERS d3dpp;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	_x = x;
	_z = z;
	Device = device;
	Device->CreateVertexBuffer(8 * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_MANAGED, &VB, 0);

	Vertex* vertices;

	VB->Lock(0, 0, (void**) &vertices, 0); // 전체 버퍼를 잠근다

	// 입방체 데이터로 버퍼 채우기(육면체는 꼭지점이 총 8개)
	vertices[0] = Vertex(x, y, z, color);
	vertices[1] = Vertex(x, y+1, z, color);
	vertices[2] = Vertex(x+1, y+1, z, color);
	vertices[3] = Vertex(x+1, y, z, color);
	vertices[4] = Vertex(x, y, z+1, color);
	vertices[5] = Vertex(x, y+1, z+1, color);
	vertices[6] = Vertex(x+1, y+1, z+1, color);
	vertices[7] = Vertex(x+1, y, z+1, color);

	VB->Unlock(); // 버퍼 이용이 끝난 후 잠금을 해제한다

	// 36 * sizeof(WORD) 크기의 쓰기만 가능한 16비트 인덱스 버퍼를 만든다
	Device->CreateIndexBuffer(36 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	// 입방체의 삼각형 정의
	WORD* indices = 0;
	//Vertex* vertices2;
	IB->Lock(0, 0, (void**) &indices, 0);

	// 전면
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// 후면
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	// 왼쪽 측면
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// 오른쪽 측면
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// 상단
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// 하단
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	IB->Unlock();

	// ----------------------------------------- //
	// 카메라 초기화(위치와 방향 조정)
	// ----------------------------------------- //

	/*D3DXVECTOR3 position(0.0f, 0.0f, -20.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &V);*/

	// ----------------------------------------- //
	// 투영 행렬 지정
	// ----------------------------------------- //

	D3DXMATRIX proj;

	// 시야각 45도, 종횡비 (너비 / 높이)
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.25f, (float) Width / (float) Height, 1.0f, 1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	// ----------------------------------------- //
	// 렌더 상태 지정
	// ----------------------------------------- //

	Device->SetRenderState(D3DRS_LIGHTING, false);

	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	//맨 처음에 생성된 블럭이 뒤로 밀려서 보임(한글의 뒤로보내기 같은 식)
	//렌더링 순서 문제로 추측
}

bool VoxelDrawMgr::Initialize()
{
	return true;
}

void VoxelDrawMgr::SetColor(D3DCOLOR _COLOR)
{
	//color = _COLOR;
}

int VoxelDrawMgr::Update(float gameTime)
{
	return 0;
}

void VoxelDrawMgr::Release()
{

}
