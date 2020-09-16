#pragma once

#include "Obj.h"

class Mouse : public Obj
{
public:
	static POINT GetPos()
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd,&pt);

		return pt;
	}
public:
	Mouse(void);
	virtual ~Mouse(void);
};

