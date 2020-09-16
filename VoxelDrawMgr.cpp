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
	// �Թ�ü ȸ����Ű��
	// ----------------------------------------- //

	//D3DXMATRIX Rx, Ry;

	//// x�� 45�� ȸ��
	//static float x = 0.0f;
	////D3DXMatrixRotationX(&Rx, 3.14f / 2.5f);
	//D3DXMatrixRotationX(&Rx, x);
	//x += 0.1;

	//if( x>= 6.28f )
	//	x = 0.0f;

	//// �� �����Ӵ� y ȸ�� ����
	//static float y = 0.0f;
	//D3DXMatrixRotationY(&Ry, y);
	//y += 0.1;

	//// ������ 2*PI �� �̸��� 0���� �ʱ�ȭ�Ѵ�.
	//if( y>= 6.28f )
	//	y = 0.0f;

	//// ȸ���� �����Ѵ�.
	//D3DXMATRIX p = Rx * Ry;

	//Device->SetTransform(D3DTS_WORLD, &p);

	// ----------------------------------------- //
	// ��� �׸���
	// ----------------------------------------- //

	// �ĸ� ���۸� �Ұ��ϰ� ���� ����, ���ٽ� ���۸� ���� ���(0xFFFFFFFF)�� 1.0���� �ʱ�ȭ�Ѵ�
	//Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);

	//Device->BeginScene(); // ��� �׸��� ����!

	Device->SetTexture(0,NULL);
	Device->SetStreamSource(0, VB, 0, sizeof(Vertex)); // ��Ʈ�� �ҽ��� �����Ѵ�
	Device->SetIndices(IB); // �ε��� ���� �������� ���纻�� �����Ѵ�
	Device->SetFVF(Vertex::FVF); // ���ؽ� ������ FVF�� �����Ѵ�
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12); // �ε��� ������ �̿��� �⺻�� �׸���!
	//Device->EndScene(); // ��� �׸��� ��!

	// �ĸ� ���۸� �����Ѵ�
	//Device->Present(0, 0, 0, 0);
}

void VoxelDrawMgr::Draw(float gameTime) //���Ⱑ �׸� �׸��� �Լ�
{
	Device->SetTexture(0,NULL);
	Device->SetStreamSource(0, VB, 0, sizeof(Vertex)); // ��Ʈ�� �ҽ��� �����Ѵ�
	Device->SetIndices(IB); // �ε��� ���� �������� ���纻�� �����Ѵ�
	Device->SetFVF(Vertex::FVF); // ���ؽ� ������ FVF�� �����Ѵ�
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12); // �ε��� ������ �̿��� �⺻�� �׸���!
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

	VB->Lock(0, 0, (void**) &vertices, 0); // ��ü ���۸� ��ٴ�

	// �Թ�ü �����ͷ� ���� ä���(����ü�� �������� �� 8��)
	vertices[0] = Vertex(x, y, z, color);
	vertices[1] = Vertex(x, y+1, z, color);
	vertices[2] = Vertex(x+1, y+1, z, color);
	vertices[3] = Vertex(x+1, y, z, color);
	vertices[4] = Vertex(x, y, z+1, color);
	vertices[5] = Vertex(x, y+1, z+1, color);
	vertices[6] = Vertex(x+1, y+1, z+1, color);
	vertices[7] = Vertex(x+1, y, z+1, color);

	VB->Unlock(); // ���� �̿��� ���� �� ����� �����Ѵ�

	// 36 * sizeof(WORD) ũ���� ���⸸ ������ 16��Ʈ �ε��� ���۸� �����
	Device->CreateIndexBuffer(36 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	// �Թ�ü�� �ﰢ�� ����
	WORD* indices = 0;
	//Vertex* vertices2;
	IB->Lock(0, 0, (void**) &indices, 0);

	// ����
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// �ĸ�
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	// ���� ����
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// ������ ����
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// ���
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// �ϴ�
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	IB->Unlock();

	// ----------------------------------------- //
	// ī�޶� �ʱ�ȭ(��ġ�� ���� ����)
	// ----------------------------------------- //

	/*D3DXVECTOR3 position(0.0f, 0.0f, -20.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &V);*/

	// ----------------------------------------- //
	// ���� ��� ����
	// ----------------------------------------- //

	D3DXMATRIX proj;

	// �þ߰� 45��, ��Ⱦ�� (�ʺ� / ����)
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.25f, (float) Width / (float) Height, 1.0f, 1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	// ----------------------------------------- //
	// ���� ���� ����
	// ----------------------------------------- //

	Device->SetRenderState(D3DRS_LIGHTING, false);

	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	//�� ó���� ������ ���� �ڷ� �з��� ����(�ѱ��� �ڷκ����� ���� ��)
	//������ ���� ������ ����
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
