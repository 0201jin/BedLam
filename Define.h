#pragma once

#include "GraphicsDevice.h"
#include <list>

#define SAFE_DELETE(x) delete(x); (x) = 0;

// KEY CODE //

//<- MOUSE CODE ->//
const DWORD KEY_LBUTTON	 = 0x00000001;
const DWORD KEY_RBUTTON	 = 0x00000002;
//<- MOUSE CODE ->//


//<- KEY CODE ->//
const DWORD KEY_Q	 = 0x00000003;
const DWORD KEY_W	 = 0x00000004;
const DWORD KEY_E	 = 0x00000005;
const DWORD KEY_R	 = 0x00000006;
const DWORD KEY_T	 = 0x00000007;
const DWORD KEY_Y	 = 0x00000008;
const DWORD KEY_U	 = 0x00000009;
const DWORD KEY_I	 = 0x00000010;
const DWORD KEY_O	 = 0x00000011;
const DWORD KEY_P	 = 0x00000012;
const DWORD KEY_A	 = 0x00000013;
const DWORD KEY_S	 = 0x00000014;
const DWORD KEY_D	 = 0x00000015;
const DWORD KEY_F	 = 0x00000016;
const DWORD KEY_G	 = 0x00000017;
const DWORD KEY_H	 = 0x00000018;
const DWORD KEY_J	 = 0x00000019;
const DWORD KEY_K	 = 0x00000020;
const DWORD KEY_L	 = 0x00000021;
const DWORD KEY_Z    = 0x00000022;
const DWORD KEY_X	 = 0x00000023;
const DWORD KEY_C	 = 0x00000024;
const DWORD KEY_V	 = 0x00000025;
const DWORD KEY_B	 = 0x00000026;
const DWORD KEY_N	 = 0x00000027;
const DWORD KEY_M	 = 0x00000028;
const DWORD KEY_1	 = 0x00000029;
const DWORD KEY_2	 = 0x00000030;
const DWORD KEY_3	 = 0x00000031;
const DWORD KEY_4	 = 0x00000032;
const DWORD KEY_5	 = 0x00000033;
const DWORD KEY_6	 = 0x00000034;
const DWORD KEY_7	 = 0x00000035;
const DWORD KEY_8	 = 0x00000036;
const DWORD KEY_9	 = 0x00000037;
const DWORD KEY_0	 = 0x00000038;


const DWORD KEY_1NUM	 = 0x00000039;
const DWORD KEY_2NUM	 = 0x00000040;
const DWORD KEY_3NUM	 = 0x00000041;
const DWORD KEY_4NUM	 = 0x00000042;
const DWORD KEY_5NUM	 = 0x00000043;
const DWORD KEY_6NUM	 = 0x00000044;
const DWORD KEY_7NUM	 = 0x00000045;
const DWORD KEY_8NUM	 = 0x00000046;
const DWORD KEY_9NUM	 = 0x00000047;
const DWORD KEY_0NUM	 = 0x00000048;


const DWORD KEY_LCRL	 = 0x00000049;
const DWORD KEY_LSHIFT	 = 0x00000050;
const DWORD KEY_RCRL	 = 0x00000051;
const DWORD KEY_RSHIFT	 = 0x00000052;
const DWORD KEY_CAPS	 = 0x00000053;
const DWORD KEY_TAB		 = 0x00000054;
const DWORD KEY_ENTER	 = 0x00000055;
const DWORD KEY_SPACE	 = 0x00000056;
const DWORD KEY_BACKSPACE= 0x00000057;
const DWORD KEY_DEL		 = 0x00000058;
const DWORD KEY_INS		 = 0x00000059;
const DWORD KEY_HOME	 = 0x00000060;

const DWORD KEY_UP		 = 0x00000061;
const DWORD KEY_DOWN	 = 0x00000062;
const DWORD KEY_LEFT	 = 0x00000063;
const DWORD KEY_RIGHT	 = 0x00000064;

const DWORD KEY_F1		 = 0x00000065;
const DWORD KEY_F2		 = 0x00000066;
const DWORD KEY_F3		 = 0x00000067;
const DWORD KEY_F4		 = 0x00000068;
const DWORD KEY_F5		 = 0x00000069;
const DWORD KEY_F6		 = 0x00000070;
const DWORD KEY_F7		 = 0x00000071;
const DWORD KEY_F8		 = 0x00000072;
const DWORD KEY_F9		 = 0x00000073;
const DWORD KEY_F10		 = 0x00000074;
const DWORD KEY_F11		 = 0x00000075;
const DWORD KEY_F12		 = 0x00000076;

const DWORD KEY_ESC		 = 0x00000077;
const DWORD KEY_ALT		 = 0x00000078;

// KEY CODE //

extern HWND g_hWnd;

enum STAGEID
{
	IDS_STAGE_INTRO, //인트로
	IDS_STAGE_MAIN, //메인
	IDS_STAGE_OPTION, //환경설정
	IDS_STAGE_GAMESELECT, //게임 모드 선택 
	IDS_STAGE_SINGLEMODE, //싱글 모드 화면
	IDS_STAGE_CREATEMAP, //싱글 맵 생성 화면
	IDS_STAGE_GAME, //게임 화면
	IDS_STAGE_MAPLOADING, //맵 로딩 화면
};

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;
	tagInfo(){}
	tagInfo(float _fx, float _fy, float _fcx, float _fcy)
		:fX(_fx),fY(_fy),fCX(_fcx),fCY(_fcx)
	{

	}
}INFO;

typedef struct tagOption
{
	char *language;
	tagOption(){}
}OP;

typedef struct aan
{
	char* MapName;
	char* PlayTime;
	char* MapCreateDate;
	char* MapGameMode;
}aan;