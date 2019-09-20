// OpenRen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

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



extern "C"
{
	DllExport int entry(unsigned int param_1, int param_2, unsigned int param_3);
	DllExport void __cdecl FreeModeList(void* param_1);
	DllExport RMode* GetSupportedModes(void);
	DllExport void __cdecl RenderDLLSetup(int param_1);
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
void __cdecl RenderDLLSetup(int param_1)
{
#if 1
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