#include "Credit.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Define.h"
#include <string.h>

Credit::Credit(void)
{
}


Credit::~Credit(void)
{
}

//ũ���� ����Ʈ
char credit[100][50] = {
	"����",
	"Programer : ���ᾲ"
};

int Credit::LoadCreditTurn()
{
	int CreditTurn = 0;

	HANDLE hFile;
	DWORD  dwByte;

	hFile = CreateFile("res\\Data\\CTDATA.dat",GENERIC_READ,NULL, 
		NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	ReadFile(hFile,&CreditTurn,sizeof(CreditTurn),&dwByte,NULL);

	CloseHandle(hFile);

	

	return CreditTurn;
}

void Credit::SetCreditTurn(int CreditTurn)
{
	HANDLE hFile;
	DWORD  dwByte;

	if(CreditTurn >= 2)
	{
		CreditTurn = 0;
	}

	hFile = CreateFile("res\\Data\\CTDATA.dat",GENERIC_WRITE,NULL,
		NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	WriteFile(hFile,&CreditTurn,sizeof(CreditTurn),&dwByte,NULL);

	CloseHandle(hFile);
}

char* Credit::LoadCredit(int ab)
{
	return credit[ab];
}
