#pragma once
#include "Include.h"
#include "Define.h"
class Language
{
public:
	string* StringSplit(string strOrigin, string strTok);
	string LoadLanguage(string find, string filename);
public:
	Language(void);
	~Language(void);
};

