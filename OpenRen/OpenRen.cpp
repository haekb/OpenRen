// OpenRen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "OpenRen.h"

#include <math.h>

// DLL Export Functions
extern "C"
{
	DllExport int entry(unsigned int param_1, int param_2, unsigned int param_3);
	DllExport void __cdecl FreeModeList(void* param_1);
	DllExport RMode* GetSupportedModes(void);
	DllExport void __cdecl RenderDLLSetup(unsigned int param_1);
};

// Entry -- Not Used?
int entry(unsigned int param_1, int param_2, unsigned int param_3)
{
#if 1


	return 0;
#else
	int iVar1;
	int iVar2;
	int iVar3;

	iVar1 = param_2;
	iVar2 = _DAT_10091e08;
	if (param_2 != 0) {
		if ((param_2 != 1) && (param_2 != 2)) goto LAB_100818b6;
		if ((DAT_100a351c != (code*)0x0) &&
			(iVar2 = (*DAT_100a351c)(param_1, param_2, param_3), iVar2 == 0)) {
			return 0;
		}
		iVar2 = FUN_10081795(param_1, param_2);
	}
	if (iVar2 == 0) {
		return 0;
	}
LAB_100818b6:
	iVar2 = FUN_10084da1();
	if (param_2 == 1) {
		if (iVar2 != 0) {
			return iVar2;
		}
		FUN_10081795(param_1, 0);
	}
	if ((param_2 != 0) && (param_2 != 3)) {
		return iVar2;
	}
	iVar3 = FUN_10081795(param_1, param_2);
	param_2 = iVar2;
	if (iVar3 == 0) {
		param_2 = 0;
	}
	if (param_2 != 0) {
		if (DAT_100a351c != (code*)0x0) {
			iVar2 = (*DAT_100a351c)(param_1, iVar1, param_3);
			return iVar2;
		}
		return param_2;
	}
	return 0;
#endif
}

void __cdecl FreeModeList(void* param_1)
{
	return;
}

RMode* GetSupportedModes(void)
{
	// Boot up OpenRen if we haven't already!
	if (!g_OpenRen) {
		g_OpenRen = new OpenRen();
	}

#if 1
	RMode* supportedModes = NULL;

	supportedModes = (RMode*)malloc(sizeof(RMode));

	// Oops, we can't memory!
	if (!supportedModes)
	{
		return 0;
	}
	
	std::string renderDll = "Open Renderer";
	std::string internalName = "Some Card";
	std::string description = "A Video Card";

	memset(supportedModes->m_RenderDLL, 0, 256);
	memset(supportedModes->m_InternalName, 0, 128);
	memset(supportedModes->m_Description, 0, 128);

	renderDll.copy(supportedModes->m_RenderDLL, 256);
	internalName.copy(supportedModes->m_InternalName, 128);
	description.copy(supportedModes->m_Description, 128);

	supportedModes->m_bHardware = true;
	supportedModes->m_Width = 1280;
	supportedModes->m_Height = 720;
	supportedModes->m_BitDepth = 32;

	supportedModes->m_pNext = NULL;

	return supportedModes;
#else
	undefined4* puVar1;
	int iVar2;
	int iVar3;
	undefined4* puVar4;
	code** local_10;
	int* local_c[2];

	/* 0x212d0  2  GetSupportedModes */
	DAT_1008bf24 = 0;
	FUN_10069e40();
	puVar4 = DAT_1008bf7c;
	if (DAT_1008bf7c != &DAT_1008bf78) {
		do {
			iVar2 = puVar4[2];
			iVar3 = DirectDrawCreate(*(undefined4*)(iVar2 + 0x20), &local_10, 0);
			if (iVar3 == 0) {
				iVar3 = (**(code * *)* local_10)(local_10, &DAT_100881a8, local_c);
				if (iVar3 == 0) {
					DAT_1008bf20 = iVar2;
					(**(code * *)(*local_c[0] + 0x20))(local_c[0], 0, 0, 0, &LAB_10021220);
					(**(code * *)(*local_c[0] + 8))(local_c[0]);
				}
				(**(code * *)(*local_10 + 8))(local_10);
			}
			puVar1 = puVar4 + 1;
			puVar4 = (undefined4*)* puVar1;
		} while ((undefined4*)* puVar1 != &DAT_1008bf78);
	}
	puVar4 = DAT_1008bf7c;
	if (DAT_1008bf7c != &DAT_1008bf78) {
		do {
			puVar1 = (undefined4*)puVar4[1];
			FUN_10021cb0((LPVOID)puVar4[2]);
			puVar4 = puVar1;
		} while (puVar1 != &DAT_1008bf78);
	}
	DAT_1008bf78 = &DAT_1008bf78;
	DAT_1008bf7c = &DAT_1008bf78;
	return DAT_1008bf24;
#endif
}

//
// Probably has to do with function linking
//
void __cdecl RenderDLLSetup(/*LinkStruct* pLinkStruct*/ unsigned int param_1)
{
	// Boot up OpenRen if we haven't already!
	if (!g_OpenRen) {
		g_OpenRen = new OpenRen();
	}

#if 1
	int debug = true;
	//LinkStruct ls = *pLinkStruct;
#if 0
	pLinkStruct->Init = ls_Init;
	pLinkStruct->Term = NULL;
	pLinkStruct->CreateSurface = NULL;
	pLinkStruct->DeleteSurface = NULL;
	pLinkStruct->UndefinedFunction_100262f0 = NULL;
	pLinkStruct->UndefinedFunction_10032c00 = NULL;
	pLinkStruct->UndefinedFunction_10032e50 = NULL;
	pLinkStruct->UndefinedFunction_10033160 = NULL;
#else


	g_OpenRen->m_RenderLinkStruct = &param_1;

	// 0-index debugging based, sorry!
	*(undefined4*)(param_1 + 0x6c) = (unsigned int)(*OpenRen::or_Init);
	*(undefined4*)(param_1 + 0x70) = (unsigned int)(*OpenRen::or_Fun1);
	*(undefined4*)(param_1 + 0x74) = 2;
	*(undefined4*)(param_1 + 0x78) = 3;
	*(undefined4*)(param_1 + 0x7c) = 4;
	*(undefined4*)(param_1 + 0x80) = 5;
	*(undefined4*)(param_1 + 0x84) = (unsigned int)(*OpenRen::or_Fun6);//6;
	*(undefined4*)(param_1 + 0x88) = 7;
	*(undefined4*)(param_1 + 0x8c) = 8;
	*(undefined4*)(param_1 + 0x90) = (unsigned int)(*OpenRen::or_Fun9);//9;
	*(undefined4*)(param_1 + 0x94) = (unsigned int)(*OpenRen::or_Fun10);//10;
	*(undefined4*)(param_1 + 0x98) = (unsigned int)(*OpenRen::or_Fun11);//11;
	*(undefined4*)(param_1 + 0xa0) = (unsigned int)(*OpenRen::or_Fun12);//12;
	*(undefined4*)(param_1 + 0xa4) = 13;
	*(undefined4*)(param_1 + 0xa8) = (unsigned int)(*OpenRen::or_Fun14);//14;
	*(undefined4*)(param_1 + 0xac) = 15;
	*(undefined4*)(param_1 + 0x9c) = 16;
	*(undefined4*)(param_1 + 0xdc) = (unsigned int)(*OpenRen::or_Fun17);//17;
	*(undefined4*)(param_1 + 0xe0) = (unsigned int)(*OpenRen::or_Fun18);//18;
	*(undefined4*)(param_1 + 0xb0) = 19;
	*(undefined4*)(param_1 + 0xb4) = 20;
	*(undefined4*)(param_1 + 0xb8) = 21;
	*(undefined4*)(param_1 + 0xbc) = 22;
	*(undefined4*)(param_1 + 0xc0) = 23;
	*(undefined4*)(param_1 + 0xc4) = (unsigned int)(*OpenRen::or_Fun24);//24;
	*(undefined4*)(param_1 + 200) =  (unsigned int)(*OpenRen::or_Fun25);//25;
	*(undefined4*)(param_1 + 0xcc) = 26;
	*(undefined4*)(param_1 + 0xd0) = (unsigned int)(*OpenRen::or_Fun27);//27;
	*(undefined4*)(param_1 + 0xd4) = (unsigned int)(*OpenRen::or_Fun28);//28;
	*(undefined4*)(param_1 + 0xd8) = 29;
	*(undefined4*)(param_1 + 0xe4) = 30;
	*(undefined4*)(param_1 + 0xe8) = 31;
	*(undefined4*)(param_1 + 0xf4) = 32;
	*(undefined4*)(param_1 + 0xf8) = (unsigned int)(*OpenRen::or_Fun33);//33;
	*(undefined4*)(param_1 + 0xec) = (unsigned int)(*OpenRen::or_Fun34);//34;
	*(undefined4*)(param_1 + 0xfc) = 35;
	*(undefined4*)(param_1 + 0xf0) = 36;
#endif
#else
	/* 0x21410  3  RenderDLLSetup */
	DAT_1008cbcc = param_1;
	*(undefined4*)(param_1 + 0x6c) = 0x100215a0;
	*(undefined4*)(param_1 + 0x70) = 0x100211d0;
	*(undefined4*)(param_1 + 0x74) = 0x10039fe0;
	*(undefined4*)(param_1 + 0x78) = 0x1003aac0;
	*(undefined4*)(param_1 + 0x7c) = 0x10033160;
	*(undefined4*)(param_1 + 0x80) = 0x10032c00;
	*(undefined4*)(param_1 + 0x84) = 0x100262f0;
	*(undefined4*)(param_1 + 0x88) = 0x10032e50;
	*(undefined4*)(param_1 + 0x8c) = 0x10032ea0;
	*(undefined4*)(param_1 + 0x90) = 0x10032f20;
	*(undefined4*)(param_1 + 0x94) = 0x10034930;
	*(undefined4*)(param_1 + 0x98) = 0x10034b00;
	*(undefined4*)(param_1 + 0xa0) = 0x10034c70;
	*(undefined4*)(param_1 + 0xa4) = 0x10034ed0;
	*(undefined4*)(param_1 + 0xa8) = 0x10034eb0;
	*(undefined4*)(param_1 + 0xac) = 0x10034ef0;
	*(undefined4*)(param_1 + 0x9c) = 0x10034c60;
	*(undefined4*)(param_1 + 0xdc) = 0x10034580;
	*(undefined4*)(param_1 + 0xe0) = 0x10034510;
	*(undefined4*)(param_1 + 0xb0) = 0x1002d1c0;
	*(undefined4*)(param_1 + 0xb4) = 0x10032d00;
	*(undefined4*)(param_1 + 0xb8) = 0x10020fd0;
	*(undefined4*)(param_1 + 0xbc) = 0x100371e0;
	*(undefined4*)(param_1 + 0xc0) = 0x10032e40;
	*(undefined4*)(param_1 + 0xc4) = 0x10036df0;
	*(undefined4*)(param_1 + 200) = 0x100367b0;
	*(undefined4*)(param_1 + 0xcc) = 0x100368e0;
	*(undefined4*)(param_1 + 0xd0) = 0x10036920;
	*(undefined4*)(param_1 + 0xd4) = 0x10036950;
	*(undefined4*)(param_1 + 0xd8) = 0x100369a0;
	*(undefined4*)(param_1 + 0xe4) = 0x100369d0;
	*(undefined4*)(param_1 + 0xe8) = 0x10036a90;
	*(undefined4*)(param_1 + 0xf4) = 0x10036e40;
	*(undefined4*)(param_1 + 0xf8) = 0x10021e50;
	*(undefined4*)(param_1 + 0xec) = 0x10036cf0;
	*(undefined4*)(param_1 + 0xfc) = 0x10036ae0;
	*(undefined4*)(param_1 + 0xf0) = 0x10036da0;
	return;
#endif

}

unsigned int __cdecl OpenRen::or_Init(InitStruct* pInitStruct)
{
	// Magic from the decompiled d3d.ren
	pInitStruct->magic = 0xd5d;

	g_OpenRen->m_Window = SDL_CreateWindow("Test", 0, 0, 800, 600, SDL_WINDOW_OPENGL);

	// Disable if you have CShell with SDL Window Creation!
	return 0;
	
	
	// Stuff required for opengl
	// See: https://gamedev.stackexchange.com/a/119903
	// Create a hidden window with OpenGL Context enabled
	// Then share the pixel format with the foreign window
	SDL_Window* pOpenGLWindow = SDL_CreateWindow("", 0, 0, 1, 1, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

	char sBuf[32];
	sprintf_s<32>(sBuf, "%p", pOpenGLWindow);

	SDL_SetHint(SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT, sBuf);
	g_OpenRen->m_Window = SDL_CreateWindowFrom(pInitStruct->hMainWnd);
	SDL_SetHint(SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT, nullptr);

	SDL_DestroyWindow(pOpenGLWindow);

	SDL_SetWindowSize(g_OpenRen->m_Window, 1280, 720);
	SDL_SetWindowPosition(g_OpenRen->m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	return 0;
}

void OpenRen::or_Fun1()
{
	// Maybe Term?
}

//0x84
// Big function, might be draw related?
// Gets called if or_Fun9 returns 0
void OpenRen::or_Fun6(int* piParm1, unsigned int uParm2)
{
	bool test = true;
}

//0x90
unsigned int OpenRen::or_Fun9()
{
#if 0
	// Basically 0?
	return DAT_1008d7c8;
#endif
	return 1337;
}

//0x94
// Most likely StartOptimized2D
unsigned int OpenRen::or_Fun10()
{
	return 1;
}

//0x98
// Most likely EndOptimized2D
void OpenRen::or_Fun11()
{
	return;
}

//0xa0
// Possibly draw related. gets called when or_Fun9 returns non-zero.
unsigned int __cdecl OpenRen::or_Fun12(int param_1)
{
	return 0;
}

//0xa8
// Draw related
unsigned int OpenRen::or_Fun14(unsigned int uParam1)
{
#if 0
	DAT_10089448 = uParm1 & 0xffffff | 0xff000000;
#endif

	unsigned int temp = uParam1 & 0xffffff | 0xff000000;

	// Always returns 1
	return 1;
}

//0xdc
// Optimize Surface?
// When not linked, crashes on `g_pLTClient->OptimizeSurface`
// Big function eep! -- Takes in Surface Pointer
unsigned int __cdecl OpenRen::or_Fun17(int param_1)
{
	return 0;
}

//0xe0
void __cdecl OpenRen::or_Fun18(int param_1)
{
	bool test = true;

#if 0
#define code void
#define uint unsigned int

	int iVar1;
	int iVar2;
	int* piVar3;
	uint uVar4;

	if ((param_1 != 0) && (piVar3 = *(int**)(param_1 + 0x84), piVar3 != (int*)0x0)) {
		iVar1 = *piVar3;
		uVar4 = 0;
		iVar2 = piVar3[1];
		if (iVar1 * iVar2 != 0) {
			while (true) {
				if ((piVar3 + uVar4 * 7)[8] != 0) {
					piVar3 = (int*)(piVar3 + uVar4 * 7)[8];
					//(**(code * *)(*piVar3 + 8))(piVar3);
				}
				uVar4 = uVar4 + 1;
				if ((uint)(iVar1 * iVar2) <= uVar4) break;
				piVar3 = *(int**)(param_1 + 0x84);
			}
		}
		//FUN_10021cb0(*(LPVOID*)(param_1 + 0x84));
		*(undefined4*)(param_1 + 0x84) = 0;
	}
	return;
#endif
}



//0xc4
void OpenRen::or_Fun24(unsigned int* param_1)
{
	bool test = true;
#if 1
	// temp
#if 1
	// Represents 16 or 32 bit.
	// 2 = 16, else is 32?
	unsigned int DAT_1008bf2c = 2;

	// ?
	unsigned int DAT_1008bf30 = 0;
	unsigned int DAT_1008bf40 = 0;
	unsigned int DAT_1008bf50 = 0;
#endif

	int iVar1;
	undefined4* puVar2;
	undefined4* puVar3;

	*(undefined4*)(param_1 + 4) = DAT_1008bf2c;
	iVar1 = 4;
	puVar2 = &DAT_1008bf30;
	puVar3 = (undefined4*)(param_1 + 8);
	while (iVar1 != 0) {
		iVar1 = iVar1 + -1;
		*puVar3 = *puVar2;
		puVar2 = puVar2 + 1;
		puVar3 = puVar3 + 1;
	}
	iVar1 = 4;
	puVar2 = &DAT_1008bf40;
	puVar3 = (undefined4*)(param_1 + 0x18);
	while (iVar1 != 0) {
		iVar1 = iVar1 + -1;
		*puVar3 = *puVar2;
		puVar2 = puVar2 + 1;
		puVar3 = puVar3 + 1;
	}
	iVar1 = 4;
	puVar2 = &DAT_1008bf50;
	puVar3 = (undefined4*)(param_1 + 0x28);
	while (iVar1 != 0) {
		iVar1 = iVar1 + -1;
		*puVar3 = *puVar2;
		puVar2 = puVar2 + 1;
		puVar3 = puVar3 + 1;
	}
#endif

}

//200
// Font or Surface Init?
int** __cdecl OpenRen::or_Fun25(int param_1, int param_2)
{

#if 1

#if 1
	int* DAT_1008bf74 = 0;
#endif

	int iVar1;
	int** ppiVar2;
	undefined4 local_8c;
	undefined4 local_88;
	int local_84;
	int local_80;
	undefined4 local_24;
	int* local_10;
	undefined4 local_c;
	undefined4 local_8;

#if 0
	if (((DAT_1008bf74 != (int*)0x0) && (param_1 != 0)) && (param_2 != 0)) {
		memset(&local_8c, 0, 0x7c);
		local_84 = param_2;
		local_8c = 0x7c;
		local_80 = param_1;
		local_88 = 7;
		local_24 = 0x840;
		iVar1 = (**(code * *)(*DAT_1008bf74 + 0x18))(DAT_1008bf74, &local_8c, &local_10, 0);
		if (iVar1 == 0) {
			ppiVar2 = (int**)FUN_10021c50(0x8c);
			if (ppiVar2 != (int**)0x0) {
				*ppiVar2 = local_10;
				local_8 = 0;
				local_c = 0;
				(**(code * *)(*local_10 + 0x74))(local_10, 8, &local_c);
				ppiVar2[0x20] = (int*)0x0;
				memset(ppiVar2 + 1, 0, 0x7c);
				ppiVar2[1] = (int*)0x7c;
				(**(code * *)(*local_10 + 0x58))(local_10, ppiVar2 + 1);
				return ppiVar2;
			}
			(**(code * *)(*local_10 + 8))(local_10);
		}
	}
#endif
	return (int**)2;
#endif
}

//0xd0
void OpenRen::or_Fun27(int iParm1, undefined4* puParm2, undefined4* puParm3, undefined4* puParm4)
{
#if 0
	if (iParm1 != 0) {
		if (puParm2 != (undefined4*)0x0) {
			*puParm2 = *(undefined4*)(iParm1 + 0x10);
		}
		if (puParm3 != (undefined4*)0x0) {
			*puParm3 = *(undefined4*)(iParm1 + 0xc);
		}
		if (puParm4 != (undefined4*)0x0) {
			*puParm4 = *(undefined4*)(iParm1 + 0x14);
		}
	}
#endif
}

//0xd4
// Does something with a surface
// offset 100 (dec: 256) holds a function? 
unsigned int __cdecl OpenRen::or_Fun28(int** param_1)
{
#if 0



	int iVar1;
	undefined4 local_80[9];
	undefined4 local_5c = 0;

	if (param_1 != (int**)0x0) {
		//100
		typedef int func(int*, int, unsigned int*, int, int);
		func* fn100 = (func*)(**param_1 + 100);

		local_80[0] = 0x7c;
		iVar1 = fn100(*param_1, 0, local_80, 0, 0);//(**(code * *)(**param_1 + 100))(*param_1, 0, local_80, 0, 0);
		if (iVar1 == 0) {
			return local_5c;
		}
	}
	return 0;
#endif
	return 0;
}

//0xf8
void OpenRen::or_Fun33()
{
#if 1
#define float10 float
#define code void
#define ROUND(x) round(x)

	//0x1c
	typedef float10 func(unsigned int);
	func* fn0x1c = (func*) (g_OpenRen->m_RenderLinkStruct + 0x1c);

	// Temp
#if 1
	// ? Is apparentally `this` in some context?
	// Passed alongside ModelMinTri
	int* DAT_1008bf90 = NULL;


#endif

	int* piVar1;
	float10 fVar2;

	piVar1 = DAT_1008bf90;
	if (DAT_1008bf90 != (int*)0x0) {
		do {

			//((void(*)(void))0x1234)();
			fVar2 = fn0x1c(piVar1[6]);//(float10)(**(code * *)(DAT_1008cbcc + 0x1c))(piVar1[6]);
			*(float*)(piVar1 + 1) = (float)fVar2;
			*piVar1 = (int)ROUND((float)fVar2);
			if ((int*)piVar1[4] != (int*)0x0) {
				*(int*)piVar1[4] = piVar1[1];
			}
			if ((int*)piVar1[3] != (int*)0x0) {
				*(int*)piVar1[3] = *piVar1;
			}
			piVar1 = (int*)piVar1[7];
		} while (piVar1 != (int*)0x0);
	}
	/*
	FUN_100316e0();
	if (DAT_1008cba8 != 0) {
		DAT_10089400 = 0;
	}
	*/
#endif


	return;
}

//0xec
// Related to DrawSurfaceToSurface
void OpenRen::or_Fun34(int* piParm1)
{
	return;
}

OpenRen::OpenRen()
{
	m_hMainWnd = NULL;
	m_RenderLinkStruct = NULL;
	m_RenderMode = {};
	m_Window = NULL;
}

OpenRen::~OpenRen()
{
}
