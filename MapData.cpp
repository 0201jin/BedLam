#include "MapData.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Define.h"
#include <string.h>

MapData::MapData(void)
{
}


MapData::~MapData(void)
{
}

vector<aan> MapData::ReadDataList()
{
	vector<aan> vec;

	ifstream in;
	in.open("res\\Data\\MLDATA.dat", ios::in | ios::binary); //바이너리 모드로 파일을 오픈

	aan mme;

	while (!in.eof()){
		in.read((char*)&mme, sizeof(aan)); //바이너리 형식으로 파일에서 읽어옴
		if(in.eof())
			break;
		vec.push_back(mme);
	}

	if (in.is_open() == true){
		in.close();
	}

	return vec; 
}

void MapData::WriteDataList(vector<aan> vec)
{
	ofstream in;
	in.open("res\\Data\\MLDATA.dat", ios::out | ios::binary); //바이너리 모드로 파일을 오픈
	
	if( in ) { 
		for(vector<aan>::iterator iter = vec.begin();
			iter != vec.end(); ++iter)
		{
			in.write((char* ) &(*iter), sizeof(aan)); //바이너리 형식으로 파일에 입력
		}
		in.clear(); 
	} 

	if (in.is_open() == true){
		in.close();
	}
}
