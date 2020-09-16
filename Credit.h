#pragma once
#include "Include.h"
#include "Define.h"

class Credit
{
public:
	char* LoadCredit(int ab);
	int LoadCreditTurn();
	void SetCreditTurn(int CreditTurn);
public:
	Credit(void);
	~Credit(void);
};

