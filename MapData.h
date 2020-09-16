#pragma once
#include "Include.h"
#include "Define.h"

class MapData
{
public:
	void WriteDataList(vector<aan> vec);
	vector<aan> MapData::ReadDataList();

private:
	aan mem; 

public:
	MapData(void);
	~MapData(void);
};

