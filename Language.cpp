#include "Language.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Define.h"
#include <string.h>

Language::Language(void)
{
}


Language::~Language(void)
{
}

std::string Language::LoadLanguage(string find, string filename)
{
	string language;

	ifstream file;
	file.open("res\\Language\\"+filename);

	char ch[200];

	if(file.is_open())
	{
		while(file.getline(ch, sizeof(ch)))
		{
			if(strstr(ch,find.c_str()))
			{
				string a = ch;
				string *to = StringSplit(a,"|");
				language = to[1];
				return language;
			}
		}
	}
	file.close();

	return language;
}

string* Language::StringSplit(string strOrigin, string strTok)
{
	int     cutAt;                            
	int     index     = 0;                    
	string* strResult = new string[10]; 

	while ((cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
	{
		if (cutAt > 0) 
		{
			strResult[index++] = strOrigin.substr(0, cutAt);  
		}
		strOrigin = strOrigin.substr(cutAt+1);
	}

	if(strOrigin.length() > 0)  
	{
		strResult[index++] = strOrigin.substr(0, cutAt); 
	}

	string *mm = strResult;

	return strResult; 
}
