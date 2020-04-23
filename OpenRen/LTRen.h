#pragma once
//
// LTRen.h
// 
// A collection of Lithtech rendering structs.
// This file is meant to be the starting point on building your own Lithtech 1/2 compatiable renderer dll
//
//


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



// NOLF's RenderStruct
// Other Lithtech 2.1/2.2 games might have a similar layout.
struct DLLRenderStruct {
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
	uint32(*IncObjectFrameCode)(void);
	uint32(*GetObjectFrameCode)(void);
	uint32(*IncCurTextureFrameCode)(void);
	uint32(*rAlloc)(intptr_t* pParam, ...);
	uint32(*rFree)(intptr_t* pParam, ...);

	uint32 Width;
	uint32 Height;
	int IsInit;

	int Unknown1[9];

	/////////////////////////////////////////
	// DLL Function space
	// Could use a clean up..
	/////////////////////////////////////////
	uint32(*Init)(InitStruct* pInitStruct);
	void (*Term)(void);
	void (*BindTexture)(intptr_t* pTextureData, int nFlag);
	void (*UnbindTexture)(intptr_t* pTextureData);
	intptr_t* (*CreateContext)(intptr_t* pRenderContextInit);
	void (*DeleteContext)(intptr_t* pContext);
	void (*Clear)(LTRect pRect, uint32 nFlags);
	uint32(*Start3D)(void);
	uint32(*End3D)(void);
	uint32(*Is3DModeEnabled)(void);
	uint32(*StartOptimized2D)(void);
	void (*EndOptimized2D)(void);
	uint32(*IsInOptimized2D)(void);
	uint32(*SetOptimized2DBlend)(uint32 nBlend);
	uint32(*GetOptimized2DBlend)(uint32& nBlend);
	uint32(*SetOptimized2DColour)(uint32 nColour);
	uint32(*GetOptimized2DColour)(uint32& nColour);
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
	uint32(*LockScreen)(int left, int top, int right, int bottom, void* pData, long* pPitch);
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


struct Context
{
	short		m_Unk;
};
struct File
{
	intptr_t* pUnk1;
	LTLink Link;
	intptr_t* pUnk2;
	uint16 nUnk;       
	uint16 NameLength;      
	uint8 nUnk2;     
	uint8 nUnk3;       
	char* szFileName;    
};

//
// Texture Data
//
struct SharedTexture {

	// funcs
	intptr_t* FuncBlock[2];


	intptr_t* pData1;
	intptr_t* pCachedTexture;
	//LTLink Link;

	// LT Link doesn't want to work here
	intptr_t* prevChain;
	intptr_t* nextChain;
	intptr_t* pChainData;

	intptr_t* pData3;
	intptr_t* pData4;
	File* pFile;
	int TexType;


};


// This gets re-aligned to 16 bytes..
struct DTXExtraData {
	char TextureGroup;
	char MipMapsToUse;
	char BPP;
	char MipMapOffset;
	char MipMapTexCoordOffset;
	char TexturePriority;
	float TextureScale;
	uint16 TextureAngle;
};

// Thanks io_scene_abc 
/*
BPP_8P = 0
BPP_8 = 1
BPP_16 = 2
BPP_32 = 3
BPP_S3TC_DXT1 = 4
BPP_S3TC_DXT3 = 5
BPP_S3TC_DXT5 = 6
BPP_32P = 7
*/
struct DTXHeader {
	uint32 ResourceType;
	uint32 Version;
	uint16 Width;
	uint16 Height;
	uint16 MipmapCount;
	uint16 SectionCount;
	uint32 Flags;
	uint32 UserFlags;
	char ExtraData[12];
	//DTXExtraData ExtraData;
	char CommandString[128];
};

struct MipMapData {
	uint32 nWidth;
	uint32 nHeight;
	intptr_t* pTextureData;
	int nSize;
	int nUnk1;
	int nUnk2;
};

struct TextureData {
	intptr_t* pData1;
	intptr_t* pData2;
	DTXHeader dtxHeader;
	LTLink pLink;
	uint32 nTextureSize;  // in bytes!
	uint32 nUnk;
	SharedTexture* pSharedTexture;
	intptr_t* pData8;
	intptr_t* pTextureData;
	MipMapData MipMaps[8];
};