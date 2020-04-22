// OpenRen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "OpenRen.h"

#include <math.h>
#include <fstream>


struct Context
{
	short		m_Unk;
};

// SDL Logging
std::fstream g_SDLLogFile;

// DLL Export Functions
extern "C"
{
	DllExport int entry(unsigned int param_1, int param_2, unsigned int param_3);
	DllExport void __cdecl FreeModeList(void* param_1);
	DllExport RMode* GetSupportedModes(void);
	DllExport void __cdecl RenderDLLSetup(unsigned int param_1);
};

void SDLLog(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	return;
	// Open up SDL Log File
	g_SDLLogFile.open("OpenRen.log", std::ios::out | std::ios::app);
	g_SDLLogFile << message << "\n";
	g_SDLLogFile.close();
}

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
	RMode* supportedModes = (RMode*)param_1;

	while (supportedModes != NULL)
	{
		RMode* nextMode = supportedModes->m_pNext;
		delete(supportedModes);
		supportedModes = nextMode;
	}

	return;
}

RMode* GetSupportedModes(void)
{
	// Boot up OpenRen if we haven't already!
	if (!g_OpenRen) {
		g_OpenRen = new OpenRen();
	}

	RMode* supportedModes = NULL;

	supportedModes = (RMode*)malloc(sizeof(RMode));

	// Oops, we can't memory!
	if (!supportedModes)
	{
		SDL_Log("We couldn't allocate the supported modes array!");
		return 0;
	}

	// Clear the struct with a default
	// If for some reason we can't get any display info, this will be a default!
	memset(supportedModes->m_RenderDLL, 0, 256);
	memset(supportedModes->m_InternalName, 0, 128);
	memset(supportedModes->m_Description, 0, 128);
	supportedModes->m_bHardware = 1;
	supportedModes->m_Width = 640;
	supportedModes->m_Height = 480;
	supportedModes->m_BitDepth = 32;
	supportedModes->m_pNext = NULL;

	// Startup SDL2!
	SDL_Init(SDL_INIT_VIDEO);

#if 1
	int i, displayModeCount;
	SDL_DisplayMode mode;
	bool isFirst = true;

	RMode* thisMode = supportedModes;

	std::string renderDll = RENDERER_DLL_NAME;

	// For each display...
	for (int displayIndex = 0; displayIndex < SDL_GetNumVideoDisplays(); ++displayIndex) {

		displayModeCount = SDL_GetNumDisplayModes(displayIndex);

		if (displayModeCount < 1) {
			SDL_Log("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
			continue;
		}

		// Setup the display names
		std::string description = "Display " + std::to_string(displayIndex + 1);
		std::string internalName = SDL_GetVideoDriver(displayIndex);

		// For each resolution...
		for (i = 0; i < displayModeCount; ++i) {
			// Save this mode for later
			RMode* lastMode = thisMode;

			if (SDL_GetDisplayMode(displayIndex, i, &mode) != 0) {
				SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
				continue;
			}

			// Skip duplicates
			if (mode.w == lastMode->m_Width && mode.h == lastMode->m_Height) {
				continue;
			}

			// Allocate the new RMode if we're not the first iteration
			if (!isFirst) {
				thisMode = (RMode*)malloc(sizeof(RMode));
			}

			memset(thisMode->m_RenderDLL, 0, 256);
			memset(thisMode->m_InternalName, 0, 128);
			memset(thisMode->m_Description, 0, 128);
			
			thisMode->m_Width = mode.w;
			thisMode->m_Height = mode.h;
			thisMode->m_BitDepth = 32;
			thisMode->m_bHardware = 1; // Sure?
			thisMode->m_pNext = NULL;

			renderDll.copy(thisMode->m_RenderDLL, 256);
			internalName.copy(thisMode->m_InternalName, 128);
			description.copy(thisMode->m_Description, 128);

			if (!isFirst) {
				// Link this mode
				lastMode->m_pNext = thisMode;
			}

			// We did it folks!
			isFirst = false;
		}

	}

#endif

	return supportedModes;
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

	g_OpenRen->m_RenderLinkStruct = (DLLRenderStruct*)param_1;

#if 1
	g_OpenRen->m_RenderLinkStruct->Init = OpenRen::or_Init;
	g_OpenRen->m_RenderLinkStruct->Term = OpenRen::or_Term;
	g_OpenRen->m_RenderLinkStruct->BindTexture = OpenRen::or_BindTexture;
	g_OpenRen->m_RenderLinkStruct->UnbindTexture = OpenRen::or_UnbindTexture;
	g_OpenRen->m_RenderLinkStruct->CreateContext = OpenRen::or_CreateContext;
	g_OpenRen->m_RenderLinkStruct->DeleteContext = OpenRen::or_DeleteContext;
	g_OpenRen->m_RenderLinkStruct->Clear = OpenRen::or_Clear;
	g_OpenRen->m_RenderLinkStruct->Start3D = OpenRen::or_Start3D;
	g_OpenRen->m_RenderLinkStruct->End3D = OpenRen::or_End3D;
	g_OpenRen->m_RenderLinkStruct->Is3DModeEnabled = OpenRen::or_Is3DModeEnabled;
	g_OpenRen->m_RenderLinkStruct->StartOptimized2D = OpenRen::or_StartOptimized2D;
	g_OpenRen->m_RenderLinkStruct->EndOptimized2D = OpenRen::or_EndOptimized2D;
	g_OpenRen->m_RenderLinkStruct->IsInOptimized2D = OpenRen::or_IsInOptimized2D;
	g_OpenRen->m_RenderLinkStruct->SetOptimized2DBlend = OpenRen::or_SetOptimized2DBlend;
	g_OpenRen->m_RenderLinkStruct->GetOptimized2DBlend = OpenRen::or_GetOptimized2DBlend;
	g_OpenRen->m_RenderLinkStruct->SetOptimized2DColour = OpenRen::or_SetOptimized2DColour;
	g_OpenRen->m_RenderLinkStruct->GetOptimized2DColour = OpenRen::or_GetOptimized2DColour;
	g_OpenRen->m_RenderLinkStruct->RenderScene = OpenRen::or_RenderScene;
	g_OpenRen->m_RenderLinkStruct->RenderCommand = OpenRen::or_RenderCommand;
	g_OpenRen->m_RenderLinkStruct->GetHook = OpenRen::or_GetHook;
	g_OpenRen->m_RenderLinkStruct->SwapBuffers = OpenRen::or_SwapBuffers;
	g_OpenRen->m_RenderLinkStruct->GetInfoFlags = OpenRen::or_GetInfoFlags;
	g_OpenRen->m_RenderLinkStruct->SetScreenPixelFormat = OpenRen::or_SetScreenPixelFormat;
	g_OpenRen->m_RenderLinkStruct->CreateSurface = OpenRen::or_CreateSurface;
	g_OpenRen->m_RenderLinkStruct->DeleteSurface = OpenRen::or_DestroySurface;
	g_OpenRen->m_RenderLinkStruct->GetSurfaceDims = OpenRen::or_GetSurfaceDims;
	g_OpenRen->m_RenderLinkStruct->LockSurface = OpenRen::or_LockSurface;
	g_OpenRen->m_RenderLinkStruct->UnlockSurface = OpenRen::or_UnlockSurface;
	g_OpenRen->m_RenderLinkStruct->OptimizeSurface = OpenRen::or_OptimizeSurface;
	g_OpenRen->m_RenderLinkStruct->UnoptimizeSurface = OpenRen::or_UnoptimizeSurface;
	g_OpenRen->m_RenderLinkStruct->LockScreen = OpenRen::or_LockScreen;
	g_OpenRen->m_RenderLinkStruct->UnlockScreen = OpenRen::or_UnlockScreen;
	g_OpenRen->m_RenderLinkStruct->BlitToScreen = OpenRen::or_BlitToScreen;
	g_OpenRen->m_RenderLinkStruct->WarpToScreen = OpenRen::or_WarpToScreen;
	g_OpenRen->m_RenderLinkStruct->MakeScreenshot = OpenRen::or_MakeScreenshot;
	g_OpenRen->m_RenderLinkStruct->ReadConsoleVariables = OpenRen::or_ReadConsoleVariables;
	g_OpenRen->m_RenderLinkStruct->BlitFromScreen = OpenRen::or_BlitFromScreen;
#endif

#if 0
#if 1
	// 0-index debugging based, sorry!

#ifdef OR_NOLF
	*(undefined4*)(param_1 + 0x6c) = (unsigned int)(*OpenRen::or_Init);
	*(undefined4*)(param_1 + 0x70) = (unsigned int)(*OpenRen::or_Term);
	*(undefined4*)(param_1 + 0x74) = (unsigned int)(*OpenRen::or_BindTexture);//2;
	*(undefined4*)(param_1 + 0x78) = (unsigned int)(*OpenRen::or_UnbindTexture);//3;
	*(undefined4*)(param_1 + 0x7c) = (unsigned int)(*OpenRen::or_CreateContext);//4;
	*(undefined4*)(param_1 + 0x80) = (unsigned int)(*OpenRen::or_DeleteContext);
	*(undefined4*)(param_1 + 0x84) = (unsigned int)(*OpenRen::or_Clear);//6;
	*(undefined4*)(param_1 + 0x88) = (unsigned int)(*OpenRen::or_Start3D);//7;
	*(undefined4*)(param_1 + 0x8c) = (unsigned int)(*OpenRen::or_End3D);//8;
	*(undefined4*)(param_1 + 0x90) = (unsigned int)(*OpenRen::or_Is3DModeEnabled);//9;
	*(undefined4*)(param_1 + 0x94) = (unsigned int)(*OpenRen::or_StartOptimized2D);//10;
	*(undefined4*)(param_1 + 0x98) = (unsigned int)(*OpenRen::or_EndOptimized2D);//11;
	*(undefined4*)(param_1 + 0xa0) = (unsigned int)(*OpenRen::or_SetOptimized2DBlend);//12;
	*(undefined4*)(param_1 + 0xa4) = (unsigned int)(*OpenRen::or_GetOptimized2DBlend);//13;
	*(undefined4*)(param_1 + 0xa8) = (unsigned int)(*OpenRen::or_SetOptimized2DColour);//14;
	*(undefined4*)(param_1 + 0xac) = (unsigned int)(*OpenRen::or_GetOptimized2DColour);//15;
	*(undefined4*)(param_1 + 0x9c) = (unsigned int)(*OpenRen::or_IsInOptimized2D);//16
	*(undefined4*)(param_1 + 0xdc) = (unsigned int)(*OpenRen::or_OptimizeSurface);//17;
	*(undefined4*)(param_1 + 0xe0) = (unsigned int)(*OpenRen::or_UnoptimizeSurface);//18;
	*(undefined4*)(param_1 + 0xb0) = (unsigned int)(*OpenRen::or_RenderScene);//19;
	*(undefined4*)(param_1 + 0xb4) = (unsigned int)(*OpenRen::or_RenderCommand);//20
	*(undefined4*)(param_1 + 0xb8) = (unsigned int)(*OpenRen::or_GetHook);//21;
	*(undefined4*)(param_1 + 0xbc) = (unsigned int)(*OpenRen::or_SwapBuffers);//22;
	*(undefined4*)(param_1 + 0xc0) = (unsigned int)(*OpenRen::or_GetInfoFlags);//23
	*(undefined4*)(param_1 + 0xc4) = (unsigned int)(*OpenRen::or_SetScreenPixelFormat);//24;
	*(undefined4*)(param_1 + 200) =  (unsigned int)(*OpenRen::or_CreateSurface);//25;
	*(undefined4*)(param_1 + 0xcc) = (unsigned int)(*OpenRen::or_DestroySurface);//26;
	*(undefined4*)(param_1 + 0xd0) = (unsigned int)(*OpenRen::or_GetSurfaceDims);//27;
	*(undefined4*)(param_1 + 0xd4) = (unsigned int)(*OpenRen::or_LockSurface);//28;
	*(undefined4*)(param_1 + 0xd8) = (unsigned int)(*OpenRen::or_UnlockSurface);//29;
	*(undefined4*)(param_1 + 0xe4) = (unsigned int)(*OpenRen::or_LockScreen);//30;
	*(undefined4*)(param_1 + 0xe8) = (unsigned int)(*OpenRen::or_UnlockScreen);//31;
	*(undefined4*)(param_1 + 0xf4) = (unsigned int)(*OpenRen::or_MakeScreenshot);//32;
	*(undefined4*)(param_1 + 0xf8) = (unsigned int)(*OpenRen::or_ReadConsoleVariables);//33;
	*(undefined4*)(param_1 + 0xec) = (unsigned int)(*OpenRen::or_BlitToScreen);//34;
	*(undefined4*)(param_1 + 0xfc) = (unsigned int)(*OpenRen::or_BlitFromScreen);//35;
	*(undefined4*)(param_1 + 0xf0) = (unsigned int)(*OpenRen::or_WarpToScreen);//36;
#elif OR_AVP2
	// TODO: Remap memory! Init, and term seem right at least :)
	*(undefined4*)(param_1 + 0x70) = (unsigned int)(*OpenRen::or_Init);// = 0x10010b22;
	*(undefined4*)(param_1 + 0x74) = (unsigned int)(*OpenRen::or_Term);
	*(undefined4*)(param_1 + 0x78) = (unsigned int)(*OpenRen::or_Fun2);
	*(undefined4*)(param_1 + 0x7c) = 3;
	*(undefined4*)(param_1 + 0x80) = 4;
	*(undefined4*)(param_1 + 0x84) = 5;
	*(undefined4*)(param_1 + 0x88) = 6;
	*(undefined4*)(param_1 + 0x8c) = (unsigned int)(*OpenRen::or_VoidStub);//7;
	*(undefined4*)(param_1 + 0x90) = 8;
	*(undefined4*)(param_1 + 0x94) = (unsigned int)(*OpenRen::or_Fun9);//9;
	*(undefined4*)(param_1 + 0x98) = (unsigned int)(*OpenRen::or_Fun10);//10;
	*(undefined4*)(param_1 + 0x9c) = (unsigned int)(*OpenRen::or_Fun11);//11;
	*(undefined4*)(param_1 + 0xa0) = (unsigned int)(*OpenRen::or_Fun12);//12;
	*(undefined4*)(param_1 + 0xa8) = 13;
	*(undefined4*)(param_1 + 0xac) = 14;
	*(undefined4*)(param_1 + 0xb0) = 15;
	*(undefined4*)(param_1 + 0xb4) = 16;
	*(undefined4*)(param_1 + 0xa4) = 17;
	*(undefined4*)(param_1 + 0xe4) = (unsigned int)(*OpenRen::or_UintStub);//18;
	*(undefined4*)(param_1 + 0xe8) = 19;
	*(undefined4*)(param_1 + 0xb8) = 20;
	*(undefined4*)(param_1 + 0xbc) = 21;
	*(undefined4*)(param_1 + 0xc0) = 22;
	*(undefined4*)(param_1 + 0xc4) = (unsigned int)(*OpenRen::or_VoidStub);//23;
	*(undefined4*)(param_1 + 200) = 24;
	*(undefined4*)(param_1 + 0xcc) = (unsigned int)(*OpenRen::or_SetScreenPixelFormat);//25;
	*(undefined4*)(param_1 + 0xd0) = (unsigned int)(*OpenRen::or_CreateSurface);;
	*(undefined4*)(param_1 + 0xd4) = (unsigned int)(*OpenRen::or_VoidStub);//27;
	*(undefined4*)(param_1 + 0xd8) = (unsigned int)(*OpenRen::or_GetSurfaceDims);//28;
	*(undefined4*)(param_1 + 0xdc) = (unsigned int)(*OpenRen::or_LockSurface);//29;
	*(undefined4*)(param_1 + 0xe0) = (unsigned int)(*OpenRen::or_UnlockSurface);//30;
	*(undefined4*)(param_1 + 0xec) = 31;
	*(undefined4*)(param_1 + 0xf0) = 32;
	*(undefined4*)(param_1 + 0xfc) = 33; // Screenshot related
	*(undefined4*)(param_1 + 0x100) = (unsigned int)(*OpenRen::or_Fun33);//34;
	*(undefined4*)(param_1 + 0xf4) = (unsigned int)(*OpenRen::or_VoidStub);//35;
	*(undefined4*)(param_1 + 0x104) = (unsigned int)(*OpenRen::or_DrawToScreen);//36;
	*(undefined4*)(param_1 + 0xf8) = 37;
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
#endif
}

uint32 OpenRen::or_Init(InitStruct* pInitStruct)
{
	if (g_OpenRen->m_Window) {
		return 0;
	}

	// Magic from the decompiled d3d.ren
	pInitStruct->magic = RENDERER_MAGIC_VALUE;

	SDL_Init(SDL_INIT_VIDEO);

	uint32 Width = g_OpenRen->m_RenderLinkStruct->Width;
	uint32 Height = g_OpenRen->m_RenderLinkStruct->Height;

	g_OpenRen->m_Window = SDL_CreateWindow("Test", 32, 32, Width, Height, SDL_WINDOW_OPENGL);

	// temp!
	g_OpenRen->m_Renderer = SDL_CreateRenderer(g_OpenRen->m_Window, -1, 0);

	SDL_SetRenderDrawColor(g_OpenRen->m_Renderer, 255, 128, 0, 255);
	SDL_RenderClear(g_OpenRen->m_Renderer);
	SDL_RenderPresent(g_OpenRen->m_Renderer);
	SDL_SetRenderDrawColor(g_OpenRen->m_Renderer, 0, 128, 255, 255);

	g_OpenRen->m_ScreenSurface = SDL_CreateRGBSurfaceWithFormat(0, Width, Height, 32, SDL_PIXELFORMAT_RGB888);

	// Setup the logging functions
	SDL_LogSetOutputFunction(&SDLLog, NULL);

	// Clear file
	//g_SDLLogFile.open("Debug.log", STD ios::out | STD ios::trunc);
	//g_SDLLogFile.close();

	SDL_Log("-- Open Renderer initialized!");


	//((fnConsolePrint)(g_OpenRen->m_RenderLinkStruct + 0x14))((char*)"Hello World");

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

void OpenRen::or_Term()
{
	SDL_Log("-- Open Renderer is going away now!");

	SDL_DestroyWindow(g_OpenRen->m_Window);
	g_OpenRen->m_Window = nullptr;

	SDL_Quit();
}

struct CreateObjectStruct {
	char unknown[12];
	unsigned int* unknownPtr;
	unsigned int* nextPtr; // Linked List
};

/*
struct forthObject {
	unsigned int* firstPtr;
	unsigned int* secondPtr;
	unsigned int* thirdPtr;
	unsigned int* forthPtr;
	unsigned int* fifthPtr;
	unsigned int* sixthPtr;
	unsigned int type; // ?
	unsigned int* seventhPtr;
	unsigned int* eighthPtr;
};
*/
struct forthObject {
	LTLink link;
	//unsigned int* originPtr; // Ptr to the first `fn8` result 
	//unsigned int* latestPtr; // Ptr to the latest `fn8` result
	/*
	unsigned int* thirdPtr;
		*/
	unsigned int* firstPtr;
	unsigned int* SecondPtr;

	unsigned short something; // FF FF, so either max uShort or -1. 
	unsigned short filenameLength;

	//unsigned int sixthPtr;
	unsigned short type; // So far it's been `3`
	unsigned short type2; // I don't think `3` is a full uint.
	char* filenamePtr;
	unsigned int* empty; // This actually gets filled with something else when the next CreateObject rolls around. :thinking:
	
};

struct CreateObjectParam1 {
	unsigned int* unknown[4];
	LTLink link;
	/*
	unsigned int* llFirstPtr; // Linked list
	unsigned int* llLastPtr; 
	unsigned int* thirdPtr;
	*/
	unsigned int* unknown2[2];
	forthObject* fileObj;//unsigned int* forthptr;
	unsigned int* unknown3;
};

struct fn8Object {
	LTLink link;
	/*
	unsigned int* firstPtr;
	unsigned int* secondPtr;
	unsigned int* unknownPtr;
	*/
	unsigned int unknownInt[2];
	unsigned int* thirdPtr;
	unsigned int* forthPtr;

	/*
		unsigned int unknownInt2;
		unsigned int height;
		unsigned int forthPtr;
		unsigned int fifthPtr;
		unsigned int sixthPtr;
		unsigned int unknownInt3;
	*/
};

//0x74
// Without this, CreateObject crashes!
void OpenRen::or_BindTexture(intptr_t* pTextureData, int nFlag)
{
	SDL_Log("Calling BindTexture");

	// RenderDLLStruct broke the hack stuff below
	return;
	/*
	// 
	CreateObjectParam1* pStruct = (CreateObjectParam1*)iParm1;

	//std::string filename = pStruct->fileObj->filenamePtr;

	size_t sizeOfLinkedList = sizeof(LTLink);

	// We need some better visibility here
	static std::vector<CreateObjectParam1*> listOStructs;
	listOStructs.push_back(pStruct);

	typedef int* func1(int*, unsigned char*);
	typedef void func2(int);

	// ????
	unsigned char charArray[8];
	memset(charArray, 0, 8);
	
	// Define some engine linked functions from our RenderLink
	int unknownFunction1Ptr = *(undefined4*)(g_OpenRen->m_RenderLinkStruct + 8);
	int unknownFunction2Ptr = *(undefined4*)(g_OpenRen->m_RenderLinkStruct + 0xc);

	func1* fn8 = (func1*)unknownFunction1Ptr;
	func2* fn0xc = (func2*)unknownFunction2Ptr;

	if (iParm2 != 0) {
		// Create a...thing
		fn8Object* test = (fn8Object*)fn8(ptr, charArray);
	}

	// Do something with a param!
	fn0xc(iParm1);

	//SDL_CreateRGBSurfaceWithFormatFrom(test->)

	bool debug = true;

	return;
	*/
}

//0x78
// Without this, DestroyObject crashes!
void OpenRen::or_UnbindTexture(intptr_t* pTextureData)
{
	SDL_Log("Calling UnbindTexture");
	return;
}

//0x7c
// Lightmap related?
intptr_t* OpenRen::or_CreateContext(intptr_t* pRenderContextInit)
{
	SDL_Log("Calling or_CreateContext");

	Context* pContext;

	pContext = (Context*)malloc(sizeof(Context));

	if (!pContext)
	{
		return nullptr;
	}

	pContext->m_Unk = 0xFFFF;

	return (intptr_t * )pContext;

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

	return nullptr;
}

void OpenRen::or_DeleteContext(intptr_t* pContext)
{
	SDL_Log("Calling DeleteContext");

	if (!pContext)
	{
		return;
	}

	free(pContext);
}

//0x84
// Big function, might be draw related?
// Gets called if or_Fun9 returns 0
void OpenRen::or_Clear(LTRect pRect, uint32 nFlags)
{
	SDL_Log("Calling Clear");
}

//0x88
uint32 OpenRen::or_Start3D()
{
	SDL_Log("Calling Start3D");

	g_OpenRen->m_Is3DModeEnabled = true;
	return 1;
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
}

//0x8c
// End3D related?
uint32 OpenRen::or_End3D()
{
	SDL_Log("Calling End3D");

	g_OpenRen->m_Is3DModeEnabled = false;

	return 1;
}

//0x90
uint32 OpenRen::or_Is3DModeEnabled()
{
	SDL_Log("Calling Is 3D Enabled %d ?",g_OpenRen->m_Is3DModeEnabled);
#if 0
	// Basically 0?
	return DAT_1008d7c8;
#endif
	return (unsigned int)g_OpenRen->m_Is3DModeEnabled;
}

//0x94
// Most likely StartOptimized2D
uint32 OpenRen::or_StartOptimized2D()
{
	SDL_Log("Calling StartOptimized2D");
	return 1;
}

//0x98
// Most likely EndOptimized2D
void OpenRen::or_EndOptimized2D()
{
	SDL_Log("Calling EndOptimized2D");
	return;
}

//0xa0
// Possibly draw related. gets called when or_Fun9 returns non-zero.
// Looks like a switch statement
uint32 OpenRen::or_SetOptimized2DBlend(uint32 nBlend)
{
	SDL_Log("Calling SetOptimized2DBlend");
#if 1


#endif
	return 1;
}

uint32 OpenRen::or_GetOptimized2DBlend(uint32 &nBlend)
{
	SDL_Log("Calling GetOptimized2DBlend");

	nBlend = 0;

	return 1;
}

//0xa8
// Draw related
uint32 OpenRen::or_SetOptimized2DColour(uint32 nColour)
{
	SDL_Log("Calling SetOptimized2DColour");
#if 0
	DAT_10089448 = uParm1 & 0xffffff | 0xff000000;
#endif
	// 255?
	unsigned int temp = nColour & 0xffffff | 0xff000000;

	// Always returns 1
	return 1;
}

uint32 OpenRen::or_GetOptimized2DColour(uint32& nColour)
{
	SDL_Log("Calling GetOptimized2DColour");

	return 1;
}

uint32 OpenRen::or_IsInOptimized2D()
{
	return 1;
}

//0xdc
// Optimize Surface?
// When not linked, crashes on `g_pLTClient->OptimizeSurface`
// Big function eep! -- Takes in Surface Pointer
uint32 OpenRen::or_OptimizeSurface(intptr_t* pSurface)
{
	SDL_Log("Calling OptimizeSurface");

	return 1;
}

void OpenRen::or_UnoptimizeSurface(intptr_t* pSurface)
{
	SDL_Log("Calling UnoptimizeSurface");
}

/*
struct RenderStruct {
	int type; // version didn't make sense, those are the only two i've got :shrug:
	unsigned int* ptrParty[6]; // 6 pointers, gosh golly! They're all zeros
	char unknown[196];
	int objCount; // Confirmed
};
*/


/*
struct unknownPtr2Struct {
	//unsigned int* ptrParty[19];
	unsigned int* objects;
	unsigned short maxShorts[2];
	unsigned int* ptrPartyLarge[2];
	unsigned int type;
	unsigned int* ptrPartyLarge2[6]; // Seems to be Start3D
};
*/

/*
struct objectData {
	unsigned int* objConstant; // This is within lithtech.exe, it's pretty constant between all the examples i've seen.
	unsigned int ptrParty[33];
	unsigned int objectFlag1;
	unsigned int objectFlag2;
	unsigned int ptrParty2[3];
	LTRotation rotation;
	LTVector scale;
	unsigned int unknownInt;
	unsigned int objectType;
	unsigned int ptrParty3[12];
	LTVector positionMin;
	LTVector positionMax;
	unsigned int ptrParty4[33];
	LTVector position;
	LTVector unknownVector;
};
*/

struct ptr1 {
	unsigned int* ptrParty[2];
	CheapLTLink ltCheapLink1;
	CheapLTLink ltCheapLink2;
};


struct fileEntry {
	unsigned int* empty;
	LTLink link;
	unsigned int* rezRelated;
	unsigned short maxShort;
	unsigned short fileNameLength;
	unsigned int* unknownLowNumber;
	unsigned char* fileName;
	unsigned int* modelRelatedArea;
};

struct filesArr {
	fileEntry files[4];
};


struct objectData {
	unsigned int* objConstant; // This is within lithtech.exe, it's pretty constant between all the examples i've seen.
	ptr1 pointer1;
	objectData* thisRef;
	//unsigned int* ptrParty[2];
	//LTLink link1;
	unsigned int* filler1;
	LTLink link2;
	unsigned int* filler2;
	LTLink link3;
	unsigned int* filler3;
	LTLink link4;
	unsigned int* zero[2];
	unsigned char colour[4]; // Colour?
	unsigned int* ptr1;
	CheapLTLink cheapLink1;
	unsigned int* filler4;
	LTLink link5;
	unsigned int* ptrParty1point5[4];
	unsigned int objectFlag1;
	unsigned int objectFlag2;
	unsigned int* ptrParty2[3];
	LTRotation rotation;
	LTVector scale;
	unsigned int* unknownInt;
	unsigned int objectType;
	unsigned int* ptrParty3[12];
	LTVector positionMin;
	LTVector positionMax;
	unsigned int* ptrParty4[33];
	LTVector position;
	LTVector unknownVector;
	unsigned int* unknownEnd1[2];
	filesArr* files;
	unsigned int* unknownEnd[33];
};


struct objectStruct {
	objectData* objects[15]; // Based off objCount!
};

struct RenderStruct {
	int type; // version didn't make sense, those are the only two i've got :shrug:
	unsigned int* ptrParty[6]; // 6 pointers, gosh golly! They're all zeros
	char unknown[52];
	float vector[3]; // Maybe vector? 3 1.0 floats
	char unknown2[12];
	float deltaTime; // 90% sure
	//unsigned int largeNumber;
	char unknown3[48];
	unsigned int* unknownPtr1; // Goes to a 4-byte zero'd out value
	char unknown4[12];
	unsigned int width;
	unsigned int height;
	//unsigned int largeNumber2;
	//unsigned short shortNumber1;
	//unsigned short shortNumber2;
	float vector2[3];
	char unknown5[24];
	float unknownFloat2;
	objectStruct* objects;
	//unsigned int* objects[52]; // Max interface objs + 2!
	//unsigned int** objects; // Goes to a 8-byte value
	int objCount; // Confirmed
};


//0xb0
// Probably RenderObjects related, it's a big function!
uint32 OpenRen::or_RenderScene(intptr_t* pSceneDesc)
{
	SceneDesc* sceneDesc = (SceneDesc*)pSceneDesc;
	RenderStruct* renderStruct = (RenderStruct*)pSceneDesc;

	unsigned int offset = offsetof(RenderStruct, objects);


	// Decompiled code pushes to EBP from stack
	// So I think it's just a param ptr.
	// Also this code doesn't work !
	// Reference only !!
#if 0
	__asm PUSH EBP
	unsigned int var = 0;
	__asm MOV EBP, var
#endif

	int* objPtr = (int*)0x1008bf68;
	int* StructPtr = (int*)0x1008bf6c;

	// Probably used to signal video playback. 
	// Ptr is in binkw32.dll!
	int* binkPtr = (int*)0x1002d9b2;

	//unsigned int* test = *pParam1 + 0x50

	unsigned int* mysteryPointer = (unsigned int*)(pSceneDesc + 0x140);

#if 0
	DAT_1008d520 = 0;
	DAT_1008d4bc = 0;
	DAT_1008d4c0 = 0;
	DAT_1008d4c4 = 0;
	*(undefined4*)(DAT_1008cbcc + 0x4c) = 0;
	*(undefined4*)(DAT_1008cbcc + 0x48) = 0;
	(**(code * *)(*DAT_1008d988 + 0x50))();
	if (DAT_1008d594 == 0) {
		DAT_1008ef80 = &LAB_1002b0c0;
		FUN_10029894();
		DAT_1008ef80 = (undefined*)0x0;
}
#endif

	SDL_Log("Calling RenderObjects?");

	//free(renderStruct->objects);

	return 0;
}

void OpenRen::or_RenderCommand(int argc, char** argv)//(void* param_1, int param_2, byte** param_3)
{
	if (argc == 0)
	{
		return;
	}

	SDL_Log("[RenderCommand]: Args %s", argv[0]);
}

void* OpenRen::or_GetHook(char* pHook)
{
	SDL_Log("[GetHook] %s", pHook);
	return nullptr;
}

//0xbc
// 99% it's FlipScreen, so we'll just name it so.
void OpenRen::or_SwapBuffers(uint32 nFlags)
{
	SDL_Log("Calling Flip");
	SDL_RenderClear(g_OpenRen->m_Renderer);

	if (g_OpenRen->m_ScreenSurface == NULL) {
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_OpenRen->m_Renderer, g_OpenRen->m_ScreenSurface);

	SDL_RenderCopy(g_OpenRen->m_Renderer, texture, NULL, NULL);

	SDL_RenderPresent(g_OpenRen->m_Renderer);

	if (texture != NULL) {
		SDL_DestroyTexture(texture);
	}

	SDL_FillRect(g_OpenRen->m_ScreenSurface, NULL, 0x000000);

	return;
}

uint32 OpenRen::or_GetInfoFlags()
{
	return 0;
}




// Something to do with display format?

struct pixelFormat {
	unsigned int unknown;
	unsigned int mode; 
	unsigned int first[4];
	unsigned int second[4];
	unsigned int third[4];
	// Dunno what's next!
};

//0xc4
//Fun24
void OpenRen::or_SetScreenPixelFormat(intptr_t* pPixelFormat)
{
	SDL_Log("Calling SetScreenPixelFormat");
	// Fills it according to the memory dumps I've seen.
	pixelFormat* pf = (pixelFormat*)pPixelFormat;

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

//200
// Font or Surface Init?
//Fun25
intptr_t* OpenRen::or_CreateSurface(uint32 nWidth, uint32 nHeight)
{
	SDL_Log("Calling CreateSurface");
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, nWidth, nHeight, 32, SDL_PIXELFORMAT_RGB888);

	g_OpenRen->m_SurfaceCache.push_back(surface);

	return (intptr_t*)surface;
}
//0xcc
// Most likely DestroySurface
void OpenRen::or_DestroySurface(intptr_t* pSurface)
{
	SDL_Log("Calling DestroySurface");

	SDL_Surface* surface = (SDL_Surface*)pSurface;

	SDL_FreeSurface(surface);
	pSurface = nullptr;

	return;
}

//0xd0
// Called after or_Fun25 (SurfaceInit)
// Might be a lock? Param 1 is a pointer address, 2 is width, 3 is height, and 4 is pitch?
//Fun27
void OpenRen::or_GetSurfaceDims(intptr_t* pSurface, uint32* pWidth, uint32* pHeight, uint32* pPitch)
{
	SDL_Log("Calling GetSurfaceDims");
	if (pSurface == nullptr) {
		return;
	}
	SDL_Surface* surface = (SDL_Surface*)pSurface;

	if (surface == nullptr) {
		return;
	}

	// Maybe it's surface info? Odd how it already has the info filled in :thinking:
	*pWidth = surface->w;
	*pHeight = surface->h;
	*pPitch = surface->pitch;

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
// Lock Surface!
void* OpenRen::or_LockSurface(intptr_t* pSurface)
{
	//SDL_Log("Calling LockSurface");
	SDL_Surface* surface = (SDL_Surface*)pSurface;

	if (surface == NULL) {
		return 0;
	}

	return (void*)surface->pixels;
}

//0xd8
void OpenRen::or_UnlockSurface(intptr_t* pSurface)
{
	//SDL_Log("Calling UnlockSurface");
	if (pSurface == NULL) {
		return;
	}

	SDL_Surface* surface = (SDL_Surface*)pSurface;
}

uint32 OpenRen::or_LockScreen(int left, int top, int right, int bottom, void* pData, long* pPitch)
{
	SDL_Log("Calling LockScreen");
	return 0;
}

void OpenRen::or_UnlockScreen()
{
	SDL_Log("Calling UnlockScreen");
}

void OpenRen::or_MakeScreenshot(char* szName)
{
	SDL_Log("Calling MakeScreenshot");
	return;
}

//FUN_10021f40 console?

//0xf8
void OpenRen::or_ReadConsoleVariables()
{
	SDL_Log("Calling Function 33 (Console?)");
#if 0
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
	float fadePercentage; // 0..1
	unsigned int unknown2;
	unsigned int colourKey;
};

//0xec
// Related to DrawSurfaceToSurface
// Draw to Screen?
// Fun34
uint32 OpenRen::or_BlitToScreen(intptr_t* pBlitRequest)
{
	//SDL_Log("Calling BlitToScreen");
#if 0
	// 3d mode?
	if (DAT_1008d7c8 != 0) {
		// Throw = "Warning: drawing a nonoptimized surface while in 3D mode."
	}

#endif
	
	drawStruct* ds = (drawStruct*)pBlitRequest;

	unsigned int* unknownPtr = (unsigned int*)ds->unknown[1];
	unsigned int* unknownPtr2 = (unsigned int*)ds->unknown2;

	SDL_Surface* surface = (SDL_Surface*) ds->surfacePtr;

	// These come pre-clipped!
	LTRect* src = (LTRect*)ds->srcPtr;
	LTRect* dst = (LTRect*)ds->dstPtr;

	SDL_Rect sdlSrc = { src->left, src->top, src->right, src->bottom };
	SDL_Rect sdlDst = { dst->left, dst->top, dst->right, dst->bottom };

	// SDL doesn't want left or bottom, it wants width and height!
	sdlSrc.w -= sdlSrc.x;
	sdlSrc.h -= sdlSrc.y;
	sdlDst.w -= sdlDst.x;
	sdlDst.h -= sdlDst.y;

	if (ds->fadePercentage != 1.0f) {
		SDL_SetSurfaceAlphaMod(surface, ds->fadePercentage * 255);
		SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
	}

	unsigned int colourKeyLT = ds->colourKey;

	// SDL uses a per format rgb, LT probably just uses 8 bits? Convert it!
	int r, g, b;
	GETRGB(colourKeyLT, r, g, b);

	SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, r, g, b));

	int result = SDL_BlitScaled(surface, &sdlSrc, g_OpenRen->m_ScreenSurface, &sdlDst);

	if (result != 0) {
		const char* error = SDL_GetError();
	}

	if (ds->fadePercentage != 1.0f) {
		SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
	}

	return 1;
}

uint32 OpenRen::or_BlitFromScreen(intptr_t* pBlitRequest)
{
	return 1;
}

uint32 OpenRen::or_WarpToScreen(intptr_t* pBlitRequest)
{
	return 1;
}

void OpenRen::or_VoidStub()
{
	return;
}

unsigned int OpenRen::or_UintStub()
{
	return 0;
}