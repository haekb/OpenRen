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

	supportedModes->m_bHardware = false;
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
	int* test = (int*)param_1;

	g_OpenRen->m_RenderLinkStruct = (unsigned int*)param_1;

	// 0-index debugging based, sorry!
	*(undefined4*)(param_1 + 0x6c) = (unsigned int)(*OpenRen::or_Init);
	*(undefined4*)(param_1 + 0x70) = (unsigned int)(*OpenRen::or_Fun1);
	*(undefined4*)(param_1 + 0x74) = (unsigned int)(*OpenRen::or_Fun2);//2;
	*(undefined4*)(param_1 + 0x78) = (unsigned int)(*OpenRen::or_Fun3);//3;
	*(undefined4*)(param_1 + 0x7c) = (unsigned int)(*OpenRen::or_Fun4);//4;
	*(undefined4*)(param_1 + 0x80) = 5;
	*(undefined4*)(param_1 + 0x84) = (unsigned int)(*OpenRen::or_Fun6);//6;
	*(undefined4*)(param_1 + 0x88) = (unsigned int)(*OpenRen::or_Fun7);//7;
	*(undefined4*)(param_1 + 0x8c) = (unsigned int)(*OpenRen::or_Fun8);//8;
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
	*(undefined4*)(param_1 + 0xb0) = (unsigned int)(*OpenRen::or_Fun19);//19;
	*(undefined4*)(param_1 + 0xb4) = 20;
	*(undefined4*)(param_1 + 0xb8) = 21;
	*(undefined4*)(param_1 + 0xbc) = (unsigned int)(*OpenRen::or_Flip);//22;
	*(undefined4*)(param_1 + 0xc0) = 23;
	*(undefined4*)(param_1 + 0xc4) = (unsigned int)(*OpenRen::or_Fun24);//24;
	*(undefined4*)(param_1 + 200) =  (unsigned int)(*OpenRen::or_Fun25);//25;
	*(undefined4*)(param_1 + 0xcc) = (unsigned int)(*OpenRen::or_Fun26);//26;
	*(undefined4*)(param_1 + 0xd0) = (unsigned int)(*OpenRen::or_Fun27);//27;
	*(undefined4*)(param_1 + 0xd4) = (unsigned int)(*OpenRen::or_LockSurface);//28;
	*(undefined4*)(param_1 + 0xd8) = (unsigned int)(*OpenRen::or_UnlockSurface);//29;
	*(undefined4*)(param_1 + 0xe4) = (unsigned int)(*OpenRen::or_Fun30);//30;
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
	if (g_OpenRen->m_Window) {
		return 0;
	}

	// Magic from the decompiled d3d.ren
	pInitStruct->magic = 0xd5d;

	SDL_Init(SDL_INIT_VIDEO);

	g_OpenRen->m_Window = SDL_CreateWindow("Test", 32, 32, 1280, 720, SDL_WINDOW_OPENGL);

	// temp!
	g_OpenRen->m_Renderer = SDL_CreateRenderer(g_OpenRen->m_Window, -1, 0);

	SDL_SetRenderDrawColor(g_OpenRen->m_Renderer, 255, 128, 0, 255);
	SDL_RenderClear(g_OpenRen->m_Renderer);
	SDL_RenderPresent(g_OpenRen->m_Renderer);
	SDL_SetRenderDrawColor(g_OpenRen->m_Renderer, 0, 128, 255, 255);

	g_OpenRen->m_ScreenSurface = SDL_CreateRGBSurfaceWithFormat(0, 1280, 720, 32, SDL_PIXELFORMAT_RGB888);

	g_OpenRen->m_MainTexture = NULL;

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

//0x74
// Without this, CreateObject crashes!
void OpenRen::or_Fun2(int iParm1, int iParm2)
{
	return;
}

//0x78
// Without this, DestroyObject crashes!
void OpenRen::or_Fun3(int iParm1)
{
	return;
}

//0x7c
// Lightmap related?
unsigned int** OpenRen::or_Fun4(unsigned int* puParm1)
{
	
#if 0
	undefined* puVar1;
	undefined** ppuVar2;
	int iVar3;

	ppuVar2 = (undefined * *)FUN_10021c50(0x10);
	if (ppuVar2 != (undefined * *)0x0) {
		puVar1 = (undefined*)* puParm1;
		*(undefined2*)(ppuVar2 + 3) = 0xffff;
		ppuVar2[2] = puVar1;
		if (DAT_1008ca34 == 0) {
			if (DAT_1008d978 != 0) {
				iVar3 = FUN_1006cc90(ppuVar2);
				if (iVar3 == 0) {
					FUN_10021d60(0, (byte*)s_Warning:_unable_to_create_lightm_100a8f70);
					DAT_1008d978 = 0;
				}
			}
		}
		else {
			FUN_10021d10((byte*)s_Warning:_NoLMPages_is_TRUE_100a8f50);
		}
		return ppuVar2;
	}
	return (undefined * *)0;
#endif

	return (unsigned int**)0;
}

//0x84
// Big function, might be draw related?
// Gets called if or_Fun9 returns 0
void OpenRen::or_Fun6(int* piParm1, unsigned int uParm2)
{
	bool test = true;
}

//0x88
// EndOptimized2D ?
unsigned int OpenRen::or_Fun7()
{
#if 0
	int iVar1;

	if ((DAT_1008d7c8 == 0) && (DAT_1008d988 != (int*)0x0)) {
		iVar1 = (**(code * *)(*DAT_1008d988 + 0x14))(DAT_1008d988);
		if (iVar1 != 0) {
			return 0;
		}
		DAT_1008d7c8 = 1;
		return 1;
	}
	return 0;
#endif
	return 0;
}

//0x8c
// End3D related?
unsigned int OpenRen::or_Fun8()
{
	return 1;
}

//0x90
unsigned int OpenRen::or_Fun9()
{
#if 0
	// Basically 0?
	return DAT_1008d7c8;
#endif
	return 0;
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
// Looks like a switch statement
unsigned int __cdecl OpenRen::or_Fun12(int param_1)
{
#if 1


#endif
	return 0;
}

//0xa8
// Draw related
unsigned int OpenRen::or_Fun14(unsigned int uParam1)
{
#if 0
	DAT_10089448 = uParm1 & 0xffffff | 0xff000000;
#endif
	// 255?
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

//0xb0
// Probably RenderObjects related, it's a big function!
unsigned int OpenRen::or_Fun19()
{
	return 0;
}

//0xbc
// 99% it's FlipScreen, so we'll just name it so.
void __cdecl OpenRen::or_Flip(unsigned int param_1)
{
	SDL_RenderClear(g_OpenRen->m_Renderer);

	if (g_OpenRen->m_ScreenSurface == NULL) {
		return;
	}

	SDL_SaveBMP(g_OpenRen->m_ScreenSurface, "Screen.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_OpenRen->m_Renderer, g_OpenRen->m_ScreenSurface);

	SDL_RenderCopy(g_OpenRen->m_Renderer, texture, NULL, NULL);

	SDL_RenderPresent(g_OpenRen->m_Renderer);


	if (texture != NULL) {
		SDL_DestroyTexture(texture);
	}

	SDL_FillRect(g_OpenRen->m_ScreenSurface, NULL, 0x000000);

	return;
}



//0xc4
// Something to do with display format?

struct pixelFormat {
	unsigned int unknown;
	unsigned int mode; 
	unsigned int first[4];
	unsigned int second[4];
	unsigned int third[4];
	// Dunno what's next!
};

void OpenRen::or_Fun24(unsigned int* param_1)
{
	// Fills it according to the memory dumps I've seen.
	pixelFormat* pf = (pixelFormat*)param_1;

	// It's either 2 or 3, 2 is 16bit according to some decompiled debug funcs, and 3 is from mem dump
	pf->mode = 3;

	// Masks?
	pf->first[0] = 0;
	pf->first[1] = 16711680;
	pf->first[2] = 65280;
	pf->first[3] = 255;

	pf->second[0] = 0;
	pf->second[1] = 8;
	pf->second[2] = 8;
	pf->second[3] = 8;

	pf->third[0] = 32;
	pf->third[1] = 16;
	pf->third[2] = 8;
	pf->third[3] = 0;

	return;
#if 0
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
#if 0
// AVP2, `this` is param_1, param_1 is a DAT var
void __thiscall FUN_1001ded2(void* this, int param_1)
{
	undefined4* puVar1;
	int iVar2;
	int iVar3;

	iVar2 = 4;
	*(undefined4*)((int)this + 4) = *(undefined4*)(param_1 + 4);
	puVar1 = (undefined4*)((int)this + 8);
	param_1 = param_1 - (int)this;
	iVar3 = iVar2;
	do {
		*puVar1 = *(undefined4*)(param_1 + (int)puVar1);
		puVar1 = puVar1 + 1;
		iVar3 = iVar3 + -1;
	} while (iVar3 != 0);
	puVar1 = (undefined4*)((int)this + 0x18);
	iVar3 = iVar2;
	do {
		*puVar1 = *(undefined4*)((int)puVar1 + param_1);
		puVar1 = puVar1 + 1;
		iVar3 = iVar3 + -1;
	} while (iVar3 != 0);
	puVar1 = (undefined4*)((int)this + 0x28);
	do {
		*puVar1 = *(undefined4*)((int)puVar1 + param_1);
		puVar1 = puVar1 + 1;
		iVar2 = iVar2 + -1;
	} while (iVar2 != 0);
	return;
}
#endif

//200
// Font or Surface Init?
int** __cdecl OpenRen::or_Fun25(int param_1, int param_2)
{
	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	amask = 0x00000000;

	//SDL_Surface* surface = SDL_CreateRGBSurface(0, param_1, param_2, 24, rmask, gmask, bmask, amask);


	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, param_1, param_2, 32, SDL_PIXELFORMAT_RGB888);//SDL_PIXELFORMAT_RGB332);
	g_OpenRen->m_SurfaceCache.push_back(surface);

	return (int**)surface;
}
//0xcc
// Most likely DestroySurface
void __cdecl OpenRen::or_Fun26(int** param_1)
{
	return;
}

//0xd0
// Called after or_Fun25 (SurfaceInit)
// Might be a lock? Param 1 is a pointer address, 2 is width, 3 is height, and 4 is pitch?
void OpenRen::or_Fun27(int iParm1, undefined4* puParm2, undefined4* puParm3, undefined4* puParm4)
{
	if (iParm1 == NULL) {
		return;
	}
	SDL_Surface* surface = (SDL_Surface*)iParm1;

	if (surface == NULL) {
		return;
	}

	// Maybe it's surface info? Odd how it already has the info filled in :thinking:
	*puParm2 = surface->w;
	*puParm3 = surface->h;
	*puParm4 = surface->pitch;

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

static void* pixelSurface;
static void* after;
//0xd4
// Does something with a surface
// offset 100 (dec: 256) holds a function? 
// Lock Surface!
unsigned int __cdecl OpenRen::or_LockSurface(hSurf param_1)
{
	SDL_Surface* surface = (SDL_Surface*) param_1;

	if (surface == NULL) {
		return 0;
	}
	//SDL_LockSurface(surface);


	//pixelSurface = malloc(32 * 32 * 3);
	//memset(pixelSurface, 0, 32 * 32 * 3);

	return (unsigned int)surface->pixels;
}
//0xd8
// Takes in surface pointer and calls a function offset 128 from param_1
// with a second parameter of 0
void OpenRen::or_UnlockSurface(hSurf param_1)
{
	if (param_1 == NULL) {
		return;
	}


	SDL_Surface* surface = (SDL_Surface*)param_1;

	
	//SDL_Surface* test = SDL_CreateRGBSurfaceWithFormatFrom(param_1, 32, 32, 32, 32, SDL_PIXELFORMAT_RGB888);
	//SDL_SaveBMP(test, "test.bmp");
	SDL_SaveBMP(surface, "test.bmp");
	//SDL_UnlockSurface(surface);
}

//0xe4
// No clue! Hasn't been called yet.
unsigned int __cdecl OpenRen::or_Fun30(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4* param_5, undefined4* param_6)
{
	return 0;
}

//FUN_10021f40 console?

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

	// Console variable result?
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

struct drawStruct {
	unsigned int surfacePtr;
	unsigned int unknown[2];
	unsigned int srcPtr;
	unsigned int dstPtr;
	float unknownFloat; // Fade percentage?
	unsigned int unknown2;
	unsigned int colourKey;
};

//0xec
// Related to DrawSurfaceToSurface
// Draw to Screen?
void OpenRen::or_Fun34(int* piParm1)
{
#if 0
	// 3d mode?
	if (DAT_1008d7c8 != 0) {
		// Throw = "Warning: drawing a nonoptimized surface while in 3D mode."
	}

#endif

	drawStruct* ds = (drawStruct*)piParm1;

	SDL_Surface* surface = (SDL_Surface*) ds->surfacePtr;
	
	// These come pre-clipped!
	LTRect* src = (LTRect*)ds->srcPtr;
	LTRect* dst = (LTRect*)ds->dstPtr;

	SDL_Rect sdlSrc = { src->left, src->top, src->right, src->bottom };
	SDL_Rect sdlDst = { dst->left, dst->top, dst->right, dst->bottom };

	unsigned int colourKeyLT = ds->colourKey;

	// SDL uses a per format rgb, LT probably just uses 8 bits? Convert it!
	int r, g, b;
	GETRGB(colourKeyLT, r, g, b);

	//2164195583 <-- 255,0,255
	SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, r, g, b));

	int result = SDL_BlitSurface(surface, &sdlSrc, g_OpenRen->m_ScreenSurface, &sdlDst);
	//int result = SDL_BlitScaled(surface, &sdlSrc, g_OpenRen->m_ScreenSurface, &sdlDst);

	if (result != 0) {
		const char* error = SDL_GetError();
	}

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

