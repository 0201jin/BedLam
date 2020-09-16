#include "Option.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Define.h"
#include <string.h>


Option::Option(void)
{
}


Option::~Option(void)
{
}

string* Option::StringSplit(string strOrigin, string strTok)
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

	return strResult;
}

std::string Option::LoadOption(string find)
{
	string language;

	ifstream file;
	file.open("res\\Option\\Option.ini");

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
				file.close();
				return language;
			}
		}
	}
	file.close();

	return language;
}

void Option::WriteOption(string find, string RepairOption)
{
	//옵션값을 옵션데이터 파일에 저장해주는
}