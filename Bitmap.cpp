#include "Bitmap.h"
#include "Define.h"

Bitmap::Bitmap(void)
{
}


Bitmap::~Bitmap(void)
{
}

Bitmap* Bitmap::LoadBmp(PTCHAR pFileName)
{
	m_hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(m_hdc);

	m_bitmap = (HBITMAP)LoadImage(NULL,pFileName, IMAGE_BITMAP
		,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_oldbitmap = (HBITMAP)SelectObject(m_MemDC, m_bitmap);

	ReleaseDC(g_hWnd,m_hdc);

	return this;
}

void Bitmap::Release()
{
	SelectObject(m_MemDC,m_oldbitmap);
	DeleteObject(m_bitmap);
	DeleteDC(m_MemDC);
}
