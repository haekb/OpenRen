#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <SDL.h>

#define DllExport   __declspec( dllexport )

// Decompiled Code Defines
#define undefined4 unsigned int

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
// END NOLF

// Jake's guessing iunno

struct InitStruct
{
	int magic;
	// I see width/height mentioned, so it must just have one of these boys
	RMode renderMode;

	HWND hMainWnd;
};

// Don't think I can use this!
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
	unsigned int(__cdecl* Init)(InitStruct* param_1);

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

class OpenRen {

public:
	OpenRen();
	~OpenRen();

	// Render Functions
	static unsigned int __cdecl or_Init(InitStruct* pInitStruct);

	static void or_Fun1();
	static void or_Fun6(int* piParm1, unsigned int uParm2);
	static unsigned int or_Fun9();
	static unsigned int or_Fun10();
	static void or_Fun11();
	static unsigned int __cdecl or_Fun12(int param_1);
	static unsigned int or_Fun14(unsigned int uParam1);
	static unsigned int __cdecl or_Fun17(int param_1);
	static void __cdecl or_Fun18(int param_1);
	static void or_Fun24(unsigned int* param_1);
	static int** __cdecl or_Fun25(int param_1, int param_2);
	static void or_Fun27(int iParm1, undefined4* puParm2, undefined4* puParm3, undefined4* puParm4);
	static unsigned int __cdecl or_Fun28(int** param_1);
	static void or_Fun33();
	static void or_Fun34(int* piParm1);
	// End Render Functions`

	unsigned int* m_RenderLinkStruct;

	RMode m_RenderMode;
	HWND m_hMainWnd;

	SDL_Window* m_Window;
private:
	

};

OpenRen* g_OpenRen = NULL;

// Decompiled reference for renderLinkStruct!
#define DAT_1008cbcc g_OpenRen->m_RenderLinkStruct