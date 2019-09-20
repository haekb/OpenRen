// OpenRen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// Fake Exports for now

#define DllExport   __declspec( dllexport )

// NOLF HEADER
// Render modes are what are used to describe a video mode/video card.
struct RMode
{
	bool			m_bHardware;

	char			m_RenderDLL[256];		// What DLL this comes from.		
	char			m_InternalName[128];	// This is what the DLLs use to identify a card.
	char			m_Description[128];		// This is a 'friendly' string describing the card.

	unsigned int	m_Width, m_Height, m_BitDepth;
	RMode* m_pNext;
};
// END NOLF

// Jake's guessing iunno

struct InitStruct
{
	int magic;
	// I see width/height mentioned, so it must just have one of these boys
	RMode renderMode;

	HWND hMainWnd;
};


struct LinkStruct {
	/*
	37 functions?
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
	*/

	// FUN_100215a0
	// Initializes d3d, setups window, and sets position
	unsigned int (__cdecl *Init)(InitStruct* param_1);
	
	// FUN_100211d0
	// Loops setting up some variables
	// Eventually runs ShowCursor(1)
	// Maybe Term?
	void (*Term)(void);

	// UndefinedFunction_10039fe0
	// Possibly CreateSurface?
	void (*CreateSurface)(int width, int height);

	// UndefinedFunction_1003aac0
	// Lol no clue, Maybe DeleteSurface?
	void (*DeleteSurface)(int iParm1);

	// UndefinedFunction_10033160
	// Ohboy double pointer ahhh
	// Mentions LightMaps
	unsigned char** (*UndefinedFunction_10033160)(unsigned int* puParm1);

	void (*UndefinedFunction_10032c00)(unsigned char** ppuParm1);

	void (*UndefinedFunction_100262f0)(int* piParm1, unsigned int uParm2);

	unsigned int (*UndefinedFunction_10032e50)(void);
#if 0
	// Flip the screen.  Flags are a combination of FLIPSCREEN_ flags in de_codes.
		// Returns LT_OK or LT_NOTINITIALIZED.
	LTRESULT(*FlipScreen)(uint32 flags);

	// Clear the backbuffer.  Pass in NULL to clear the whole screen.
	// Flags is a combination of the CLEARSCREEN_ flags in de_codes.h.
	// Returns LT_OK or LT_NOTINITIALIZED.
	LTRESULT(*ClearScreen)(LTRect* pClearRect, uint32 flags);

	// You must be in a Start3D()/End3D() block in order to render
	// through any cameras.
	// Returns LT_OK or LT_NOTINITIALIZED or LT_ALREADYIN3D.
	LTRESULT(*Start3D)();

	// Render from the camera's position into its rectangle.
	// Returns LT_OK or LT_NOTINITIALIZED or LT_NOTIN3D.
	LTRESULT(*RenderCamera)(HLOCALOBJ hCamera);

	// Renders the list of objects through the given camera.
	// Returns LT_OK or LT_NOTINITIALIZED or LT_NOTIN3D.
	LTRESULT(*RenderObjects)(HLOCALOBJ hCamera, HLOCALOBJ* pObjects, int nObjects);

	// You must be in a StartOptimized2D()/EndOptimized2D() block to draw any optimized 2D surfaces.
	LTRESULT(*StartOptimized2D)();
	LTRESULT(*EndOptimized2D)();

	// Change the src/dest blend mode for rendering Optimized2D surfaces  (Defaults to LTSURFACEBLEND_ALPHA)
	// Note : Drawing a surface w/ a blend mode other than _ALPHA will automatically optimize the surface
	LTRESULT(*SetOptimized2DBlend)(LTSurfaceBlend blend);
	LTRESULT(*GetOptimized2DBlend)(LTSurfaceBlend& blend);

	// Change the color used on Optimized2D surfaces  (i.e. apply a color filter to Optimized2D)
	LTRESULT(*SetOptimized2DColor)(HLTCOLOR hColor);
	LTRESULT(*GetOptimized2DColor)(HLTCOLOR& hColor);

	// Returns LT_OK or LT_NOTINITIALIZED or LT_NOTIN3D.
	LTRESULT(*End3D)();

	// Get a (NULL-terminated) list of supported render modes.
	RMode* (*GetRenderModes)();
	void		(*RelinquishRenderModes)(RMode* pModes);

	// Fills in the current render mode.
	LTRESULT(*GetRenderMode)(RMode* pMode);

	// Goes into the requested render mode.
	// Returns LT_OK if successful.  Note: it may not have set the _exact_ mode you
	// requested.  You can check with GetRenderMode() to see what the new mode is.
	// Returns LT_KEPTSAMEMODE if it couldn't set the mode requested, but
	// was able to restore the previous mode.
	// Returns LT_UNABLETORESTOREVIDEO if it couldn't set the mode and couldn't
	// restore the video mode (in which case it will give a message and shutdown
	// afterwards).
	LTRESULT(*SetRenderMode)(RMode* pMode);

	// Shutdown the renderer.  flags is a combination of the RSHUTDOWN_ flags in de_codes.h.
	// The renderer won't come back until you call SetRenderMode().
	LTRESULT(*ShutdownRender)(uint32 flags);
#endif
};
// END

unsigned int __cdecl ls_Init(InitStruct* pInitStruct);

extern "C"
{
	DllExport int entry(unsigned int param_1, int param_2, unsigned int param_3);
	DllExport void __cdecl FreeModeList(void* param_1);
	DllExport RMode* GetSupportedModes(void);
	DllExport void __cdecl RenderDLLSetup(LinkStruct* param_1);
};

// Entry
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
void __cdecl RenderDLLSetup(LinkStruct* pLinkStruct)
{
#if 1
	int debug = true;

#if 1
	pLinkStruct->Init = ls_Init;
	pLinkStruct->Term = NULL;
	pLinkStruct->CreateSurface = NULL;
	pLinkStruct->DeleteSurface = NULL;
	pLinkStruct->UndefinedFunction_100262f0 = NULL;
	pLinkStruct->UndefinedFunction_10032c00 = NULL;
	pLinkStruct->UndefinedFunction_10032e50 = NULL;
	pLinkStruct->UndefinedFunction_10033160 = NULL;
#else
#define undefined4 unsigned int
	unsigned int param_1[2048] = {0};

	* (undefined4*)(param_1 + 0x6c) = (unsigned int)(*ls_Init);
	*(undefined4*)(param_1 + 0x70) = NULL;
	*(undefined4*)(param_1 + 0x74) = NULL;
	*(undefined4*)(param_1 + 0x78) = NULL;
	*(undefined4*)(param_1 + 0x7c) = NULL;
	*(undefined4*)(param_1 + 0x80) = NULL;
	*(undefined4*)(param_1 + 0x84) = NULL;
	*(undefined4*)(param_1 + 0x88) = NULL;
	*(undefined4*)(param_1 + 0x8c) = NULL;
	*(undefined4*)(param_1 + 0x90) = NULL;
	*(undefined4*)(param_1 + 0x94) = NULL;
	*(undefined4*)(param_1 + 0x98) = NULL;
	*(undefined4*)(param_1 + 0xa0) = NULL;
	*(undefined4*)(param_1 + 0xa4) = NULL;
	*(undefined4*)(param_1 + 0xa8) = NULL;
	*(undefined4*)(param_1 + 0xac) = NULL;
	*(undefined4*)(param_1 + 0x9c) = NULL;
	*(undefined4*)(param_1 + 0xdc) = NULL;
	*(undefined4*)(param_1 + 0xe0) = NULL;
	*(undefined4*)(param_1 + 0xb0) = NULL;
	*(undefined4*)(param_1 + 0xb4) = NULL;
	*(undefined4*)(param_1 + 0xb8) = NULL;
	*(undefined4*)(param_1 + 0xbc) = NULL;
	*(undefined4*)(param_1 + 0xc0) = NULL;
	*(undefined4*)(param_1 + 0xc4) = NULL;
	*(undefined4*)(param_1 + 200) = NULL;
	*(undefined4*)(param_1 + 0xcc) = NULL;
	*(undefined4*)(param_1 + 0xd0) = NULL;
	*(undefined4*)(param_1 + 0xd4) = NULL;
	*(undefined4*)(param_1 + 0xd8) = NULL;
	*(undefined4*)(param_1 + 0xe4) = NULL;
	*(undefined4*)(param_1 + 0xe8) = NULL;
	*(undefined4*)(param_1 + 0xf4) = NULL;
	*(undefined4*)(param_1 + 0xf8) = NULL;
	*(undefined4*)(param_1 + 0xec) = NULL;
	*(undefined4*)(param_1 + 0xfc) = NULL;
	*(undefined4*)(param_1 + 0xf0) = NULL;
#endif

	return;
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

unsigned int __cdecl ls_Init(InitStruct* pInitStruct)
{
	// Magic from the decompiled d3d.ren
	pInitStruct->magic = 0xd5d;

	// Maybe RMode?
	std::string renderDll = "Open Renderer";
	std::string internalName = "Some Card";
	std::string description = "A Video Card";

	memset(pInitStruct->renderMode.m_RenderDLL, 0, 256);
	memset(pInitStruct->renderMode.m_InternalName, 0, 128);
	memset(pInitStruct->renderMode.m_Description, 0, 128);

	renderDll.copy(pInitStruct->renderMode.m_RenderDLL, 256);
	internalName.copy(pInitStruct->renderMode.m_InternalName, 128);
	description.copy(pInitStruct->renderMode.m_Description, 128);

	pInitStruct->renderMode.m_bHardware = true;
	pInitStruct->renderMode.m_Width = 1280;
	pInitStruct->renderMode.m_Height = 720;
	pInitStruct->renderMode.m_BitDepth = 32;

	pInitStruct->renderMode.m_pNext = NULL;

#if 1
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = NULL;
	wc.hInstance = NULL;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		NULL,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

#endif

	return 0;
}
