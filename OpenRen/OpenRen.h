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

typedef void (*fnConsolePrint)(char* pMsg, ...);


// PC Struct = 0x54
// Mac Struct = 0x150
// Must be a lot of opengl stuff shoved in there. 
// Actually PC Struct gets cleared differently.
// Mac uses memset, so that might be the actual size!
struct DLLRenderStruct {
	/*
	intptr_t* Padding[5];
	void (*ConsolePrint)(char* pMsg, ...);
	intptr_t* AfterPadding[64];
	*/

	// Functions are from MAC debug symbols :D
	// These are implemented in Lithtech.exe!
	intptr_t* (*pProcessAttachment)(intptr_t* pObject, intptr_t* pAttachment);
	void (*GetSharedTexture)(char* szFileName);
	intptr_t* (*GetTexture)(intptr_t* pTextureData);
	void (*FreeTexture)(intptr_t* pTextureData);
	void (*RunConsoleString)(char* szString);

	// Has a vsprintf, so yolo
	void (*ConsolePrint)(char* szString, ...);
	intptr_t* (*GetParameter)(char* szString);
	float (*GetParameterValueFloat)(intptr_t* pParam);
	char* (*GetParameterValueString)(intptr_t* pParam);
	void (*RendererPing)(void);
	uint32 (*IncObjectFrameCode)(void);
	uint32 (*GetObjectFrameCode)(void);
	uint32 (*IncCurTextureFrameCode)(void);
	uint32 (*rAlloc)(intptr_t* pParam, ...);
	uint32 (*rFree)(intptr_t* pParam, ...);

	//intptr_t* Unknown[0x40];
	//intptr_t* FunctionSpace1[15];
	
	// Confirmed
	uint32 Width;
	uint32 Height;
	int IsInit;
	
	int Unknown1[9];
	
	// Our render functions!
	// Order here counts per game, so these may be shuffled around.
	//uint32 (*Init)(intptr_t* pInitStruct);
	//void (*Term)(void);


	intptr_t* FunctionSpace2[37];
	// A don't clear marker is at 0x40
	int32 DontClear;

	int32 Unknown2[34];
};

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
	static void or_BindTexture(intptr_t* pTextureData, int nFlag);
	static void or_UnbindTexture(intptr_t* pTextureData);
	static intptr_t* or_CreateContext(unsigned int* puParm1);
	static void or_DeleteContext(intptr_t* pContext);
	static void or_Clear(LTRect pRect, uint32 nFlags);
	static unsigned int or_Start3D();
	static unsigned int or_End3D();
	static unsigned int or_Is3DModeEnabled();
	static unsigned int or_StartOptimized2D();
	static void or_EndOptimized2D();
	static uint32 or_SetOptimized2DBlend(uint32 nBlend);
	static uint32 or_GetOptimized2DBlend(uint32& nBlend);
	static uint32 or_SetOptimized2DColour(uint32 nColour);
	static uint32 or_GetOptimized2DColour(uint32& nColour);
	static uint32 or_IsInOptimized2D();
	static uint32 or_OptimizeSurface(intptr_t* pSurface);
	static void or_UnoptimizeSurface(intptr_t* pSurface);
	static uint32 or_RenderScene(intptr_t* pSceneDesc);
	static void or_RenderCommand(int argc, char** argv); //(void* param_1, int param_2, byte** param_3);
	static void* or_GetHook(char* pHook);
	static void or_SwapBuffers(uint32 nFlags);
	static uint32 or_GetInfoFlags();
	static void or_SetScreenPixelFormat(unsigned int* param_1);
	static intptr_t* or_CreateSurface(int width, int height);
	static void or_DestroySurface(intptr_t* pSurface);
	static void or_GetSurfaceDims(intptr_t* pSurface, uint32* pWidth, uint32* pHeight, uint32* pPitch);
	static void* or_LockSurface(intptr_t pSurface);
	static void or_UnlockSurface(intptr_t pSurface);
	static uint32 or_LockScreen(int left, int top, int right, int bottom, void* pData, long* pPitch); //(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4* param_5, undefined4* param_6);
	static void or_UnlockScreen();
	static void or_MakeScreenshot(char* szName);
	static void or_ReadConsoleVariables();
	static uint32 or_BlitToScreen(intptr_t* pBlitRequest);
	static uint32 or_BlitFromScreen(intptr_t* pBlitRequest);
	static uint32 or_WarpToScreen(intptr_t* pBlitRequest);
	static void or_VoidStub();
	static unsigned int or_UintStub();
	// End Render Functions`

	bool m_Is3DModeEnabled;

	DLLRenderStruct* m_RenderLinkStruct;
	//uint32* m_RenderLinkStruct;

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