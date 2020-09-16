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
	in.open("res\\Data\\MLDATA.dat", ios::in | ios::binary); //���̳ʸ� ���� ������ ����

	aan mme;

	while (!in.eof()){
		in.read((char*)&mme, sizeof(aan)); //���̳ʸ� �������� ���Ͽ��� �о��
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
	in.open("res\\Data\\MLDATA.dat", ios::out | ios::binary); //���̳ʸ� ���� ������ ����
	
	if( in ) { 
		for(vector<aan>::iterator iter = vec.begin();
			iter != vec.end(); ++iter)
		{
			in.write((char* ) &(*iter), sizeof(aan)); //���̳ʸ� �������� ���Ͽ� �Է�
		}
		in.clear(); 
	} 

	if (in.is_open() == true){
		in.close();
	}
}
