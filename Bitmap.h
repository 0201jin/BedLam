#pragma once

class Bitmap
{
public:
	HDC			m_hdc, m_MemDC;
	HBITMAP		m_bitmap, m_oldbitmap;
public:
	Bitmap* LoadBmp(PTCHAR pFileName);
	void Release();
public:
	HDC GetMemDC(void){ return m_MemDC; }
public:
	Bitmap(void);
	~Bitmap(void);
};

