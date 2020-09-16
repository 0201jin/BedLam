#pragma once

#include "GameSprite.h"
#include "Define.h"
#include "Include.h"

typedef std::wstring String;

class Obj
{
protected:
	INFO m_tInfo;
	static map<string, GameSprite*>* m_pMapSprite;
	int a;
	string m_m_gtext;
public:
	void Seta(int _a) { a = _a; }
	int Geta() { return a; }
	string GetText();
	RECT GetRect();
	void SetPos(float _fx, float _fy);
	void SetSize(float _x, float _y);
	INFO GetInfo() { return m_tInfo; }
	static void SetSprite(map<string,GameSprite*>* _pMapSprite) { m_pMapSprite = _pMapSprite; }
public:
	virtual bool Initialize() = 0;
	virtual int Update(float gameTime) = 0;
	virtual void Draw(float gameTime) = 0;
	virtual void Release() = 0;
public:
	Obj(void);
	virtual ~Obj(void);
};

