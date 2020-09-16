#pragma once
#include "Stage.h"
#include "Obj.h"
#include "Font.h"
#include "Define.h"

class Obj;
class Font;
class Setting : public Stage
{
private:
	OP OptionSetting;
public:
	Setting(void);
	~Setting(void);
};

