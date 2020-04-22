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
struct InitStruct
{
	int magic;
	// I see width/height mentioned, so it must just have one of these boys
	RMode renderMode;

	HWND hMainWnd;
};


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
	

	//intptr_t* FunctionSpace2[37];
	/////////////////////////////////////////
	// DLL Function space
	// Could use a clean up..
	/////////////////////////////////////////
	uint32 (*Init)(InitStruct* pInitStruct);
	void (*Term)(void);
	void (*BindTexture)(intptr_t* pTextureData, int nFlag);
	void (*UnbindTexture)(intptr_t* pTextureData);
	intptr_t* (*CreateContext)(intptr_t* pRenderContextInit);
	void (*DeleteContext)(intptr_t* pContext);
	void (*Clear)(LTRect pRect, uint32 nFlags);
	uint32 (*Start3D)(void);
	uint32 (*End3D)(void);
	uint32 (*Is3DModeEnabled)(void);
	uint32 (*StartOptimized2D)(void);
	void (*EndOptimized2D)(void);
	uint32(*IsInOptimized2D)(void);
	uint32 (*SetOptimized2DBlend)(uint32 nBlend);
	uint32 (*GetOptimized2DBlend)(uint32& nBlend);
	uint32 (*SetOptimized2DColour)(uint32 nColour);
	uint32 (*GetOptimized2DColour)(uint32& nColour);
	uint32(*RenderScene)(intptr_t* pSceneDesc);
	void (*RenderCommand)(int argc, char** argv);
	void* (*GetHook)(char* szHookName);
	void (*SwapBuffers)(uint32 nFlags);
	uint32(*GetInfoFlags)(void);
	void (*SetScreenPixelFormat)(intptr_t* pPixelFormat);
	intptr_t* (*CreateSurface)(uint32 nWidth, uint32 nHeight);
	void (*DeleteSurface)(intptr_t* pSurface);
	void (*GetSurfaceDims)(intptr_t* pSurface, uint32* pWidth, uint32* pHeight, uint32* pPitch);
	void* (*LockSurface)(intptr_t* pSurface);
	void (*UnlockSurface)(intptr_t* pSurface);
	uint32(*OptimizeSurface)(intptr_t* pSurface);
	void (*UnoptimizeSurface)(intptr_t* pSurface);
	uint32 (*LockScreen)(int left, int top, int right, int bottom, void* pData, long* pPitch);
	void (*UnlockScreen)(void);
	uint32(*BlitToScreen)(intptr_t* pBlitRequest);
	uint32(*WarpToScreen)(intptr_t* pBlitRequest);
	void (*MakeScreenshot)(char* szName);
	void (*ReadConsoleVariables)(void);
	uint32(*BlitFromScreen)(intptr_t* pBlitRequest);

	// A don't clear marker is at 0x40
	int32 DontClear;

	int32 Unknown2[34];
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


class OpenRen {
	typedef int** hSurf;
public:
	OpenRen();
	~OpenRen();

	// Render Functions
	static uint32 or_Init(InitStruct* pInitStruct);
	static void or_Term();
	static void or_BindTexture(intptr_t* pTextureData, int nFlag);
	static void or_UnbindTexture(intptr_t* pTextureData);
	static intptr_t* or_CreateContext(intptr_t* pRenderContextInit);
	static void or_DeleteContext(intptr_t* pContext);
	static void or_Clear(LTRect pRect, uint32 nFlags);
	static uint32 or_Start3D();
	static uint32 or_End3D();
	static uint32 or_Is3DModeEnabled();
	static uint32 or_StartOptimized2D();
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
	static void or_SetScreenPixelFormat(intptr_t* pPixelFormat);
	static intptr_t* or_CreateSurface(uint32 nWidth, uint32 nHeight);
	static void or_DestroySurface(intptr_t* pSurface);
	static void or_GetSurfaceDims(intptr_t* pSurface, uint32* pWidth, uint32* pHeight, uint32* pPitch);
	static void* or_LockSurface(intptr_t* pSurface);
	static void or_UnlockSurface(intptr_t* pSurface);
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