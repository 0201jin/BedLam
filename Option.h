#pragma once
#include "Include.h"
#include "Define.h"
class Option
{
public:
	string LoadOption(string find);
	void WriteOption(string find, string RepairOption);
private:
	string* StringSplit(string strOrigin, string strTok);
public:
	Option(void);
	~Option(void);
};

