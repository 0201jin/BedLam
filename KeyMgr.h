#pragma once
#include "Define.h"

class KeyMgr
{
private:
	DWORD m_dwKey;
public:
	void CheckKey();
	DWORD GetKey()const { return m_dwKey; }
private:
	static KeyMgr* m_pInst;
public:
	static KeyMgr* GetInst()
	{
		if(m_pInst == NULL)
			m_pInst = new KeyMgr;
		return m_pInst;
	}

	void DestoryInst()
	{
		SAFE_DELETE(m_pInst);
	}
public:
	KeyMgr(void);
	~KeyMgr(void);
};

