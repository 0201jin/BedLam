#include "Obj.h"

map<string,GameSprite*>* Obj::m_pMapSprite = NULL;

Obj::Obj(void)
{
}


Obj::~Obj(void)
{
}

RECT Obj::GetRect()
{
	RECT  rt = 
	{
		int(m_tInfo.fX),
		int(m_tInfo.fY),
		int(m_tInfo.fX + m_tInfo.fCX),
		int(m_tInfo.fY + m_tInfo.fCY)
	};

	return rt;
}

void Obj::SetPos(float _fx, float _fy)
{
	m_tInfo.fY = _fy;
	m_tInfo.fX = _fx;
}

void Obj::SetSize(float _x, float _y)
{
	m_tInfo.fCX = _x;
	m_tInfo.fCY = _y;
}

string Obj::GetText()
{
	return m_m_gtext;
}
