#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <SDL.h>
#include <vector>
#include "ltlink.h"

#define DllExport   __declspec( dllexport )

// Decompiled Code Defines
#define undefined4 unsigned int

#define RENDERER_MAGIC_VALUE 0xd5d
#define RENDERER_DLL_NAME "Open Renderer"

// NOLF HEADER
// Render modes are what are used to describe a video mode/video card.
struct RMode
{
	unsigned int			m_bHardware;

	char			m_RenderDLL[256];		// What DLL this comes from.		
	char			m_InternalName[128];	// This is what the DLLs use to identify a card.
	char			m_Description[128];		// This is a 'friendly' string describing the card.

	unsigned int	m_Width, m_Height, m_BitDepth;
	RMode* m_pNext;
};
/*
class LTRect
{
public:
	LTRect(int l = 0, int t = 0, int r = 0, int b = 0) : left(l), top(t), right(r), bottom(b) {}
	inline void	Init(int inLeft, int inTop, int inRight, int inBottom)
	{
		left = inLeft;
		top = inTop;
		right = inRight;
		bottom = inBottom;
	}

	int left, top, right, bottom;
};
*/
// Gets r, g, and b as 0-255 integers.
#define GETR(val) (((val) >> 16) & 0xFF)
#define GETG(val) (((val) >> 8) & 0xFF)
#define GETB(val) ((val) & 0xFF)
#define GETRGB(val, r, g, b) \
	{\
		(r) = GETR(val);\
		(g) = GETG(val);\
		(b) = GETB(val);\
	}

// END NOLF

// Jake's guessing iunno

struct InitStruct
{
	int magic;
	// I see width/height mentioned, so it must just have one of these boys
	RMode renderMode;

	HWND hMainWnd;
};

class OpenRen {
	typedef int** hSurf;
public:
	OpenRen();
	~OpenRen();

	// Render Functions
	static unsigned int __cdecl or_Init(InitStruct* pInitStruct);

	static void or_Term();
	static void or_Fun2(int iParm1, int iParm2);
	static void or_Fun3(int iParm1);
	static unsigned int** or_Fun4(unsigned int* puParm1);
	static void or_Fun6(int* piParm1, unsigned int uParm2);
	static unsigned int or_Start3D();
	static unsigned int or_End3D();
	static unsigned int Is3DModeEnabled();
	static unsigned int or_Fun10();
	static void or_Fun11();
	static unsigned int __cdecl or_Fun12(int param_1);
	static unsigned int or_Fun14(unsigned int uParam1);
	static unsigned int __cdecl or_Fun17(int param_1);
	static void __cdecl or_Fun18(int param_1);
	static unsigned int or_Fun19(unsigned int* pParam1);
	static void __cdecl or_Flip(unsigned int param_1);
	static void or_SetScreenPixelFormat(unsigned int* param_1);
	static int** __cdecl or_CreateSurface(int param_1, int param_2);
	static void __cdecl or_Fun26(int** param_1);
	static void or_GetSurfaceDims(int iParm1, undefined4* puParm2, undefined4* puParm3, undefined4* puParm4);
	static unsigned int __cdecl or_LockSurface(hSurf param_1);
	static void or_UnlockSurface(hSurf param_1);
	static unsigned int __cdecl or_Fun30(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4* param_5, undefined4* param_6);
	static void or_Fun33();
	static void or_DrawToScreen(int* piParm1);
	static void or_VoidStub();
	static unsigned int or_UintStub();
	// End Render Functions`

	bool m_Is3DModeEnabled;

	unsigned int* m_RenderLinkStruct;

	RMode m_RenderMode;
	HWND m_hMainWnd;

	SDL_Window* m_Window;
	// temp!
	SDL_Renderer* m_Renderer;
	std::vector<SDL_Surface*> m_SurfaceCache;
	SDL_Surface* m_ScreenSurface;
private:
	

};

OpenRen* g_OpenRen = NULL;

// Decompiled reference for renderLinkStruct!
#define DAT_1008cbcc g_OpenRen->m_RenderLinkStruct