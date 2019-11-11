#include "stdafx.h"
#include "Agony.h"
#include "MenuData.h"
#include "MenuStruct.h"

#define M_PI     3.14159265358979323846f
#define PITCH     0
#define YAW      1
#define ROLL     2
typedef vec_t vec4_t[4];
#define POW(x)     ((x) * (x))
#define M_PI     3.14159265358979323846f
#define M_E      2.71828182845904523536f
#define DotProduct(x,y)   ((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c) ((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)  ((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)   ((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define VectorScale(v, s, o) ((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define VectorDistance(a,b)  (sqrt(POW(a[0]-b[0]) + POW(a[1]-b[1]) + POW(a[2]-b[2])))
#define VectorMA(v, s, b, o) ((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorCmp(a,b)   (((a)[0]==(b)[0])&&((a)[1]==(b)[1])&&((a)[2]==(b)[2]))
#define ANGLE2SHORT(x)   ((int)((x)*65536/360) & 65535)
#define VectorClear(a)   { (a)[0]=0.0f; (a)[1]=0.0f; (a)[2]=0.0f; }
#define DistanceBox(a,b,c)  ((c*84.0f/(refdef->width*100.0f)) * 18.0f / (VectorDistance(a,b)/55.0f))
#define ScreenDistance(a,b)  (sqrt(POW(a[0]-b[0]) + POW(a[1]-b[1])))
#define VectorLength(a)         sqrt(POW((a)[0])+POW((a)[1])+POW((a)[2]))
#define VectorDivide(v, s, o)((o)[0]=(v)[0]/=(s),(o)[1]=(v)[1]/=(s),(o)[2]=(v)[2]/=(s))
#define VectorNormalize(a)      {vec_t l=VectorLength(a);(a)[0]/=l;(a)[1]/=l;(a)[2]/=l;}
#define VectorTransform(a,b,c){(c)[0]=DotProduct((a),(b)[0])+(b)[0][3];(c)[1]=DotProduct((a),(b)[1])+(b)[1][3];(c)[2]=DotProduct((a),(b)[2])+(b)[2][3];}
#define RAD2DEG( a ) ( ( (a) * 180.0f ) / M_PI )
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

void PresetINI(const char *);
void ReadINI(int);
void WriteINI(int);

void SetRageConfig(int);
void SetHvHConfig(int);
void SetAssaultConfig(int);
void SetRunNGunConfig(int);
void SetSniperConfig(int);
void SetRiotConfig(int);

#include "IW3MP.h"
#include "WAWMP.h"
#include "IW4MP.h"
#include "BO1MP.h"
#include "IW5MP.h"
#include "BO2MP.h"
#include "GHOMP.h"
#include "AWMP.h"
#include "BO3MP.h"
#include "BO3_Aimbot.h"

#include "SaveLoad.h"

char oldInputState[16];
DWORD InputStateAddr;

typedef struct _DETOUR_XEX_IMPORT_DESCRIPTOR {
	DWORD Size;
	DWORD NameTableSize;
	DWORD ModuleCount;
} DETOUR_XEX_IMPORT_DESCRIPTOR, *PDETOUR_XEX_IMPORT_DESCRIPTOR;

DWORD GetModuleImport(HANDLE HModule, HANDLE HImportedModule, DWORD Ordinal) {

	PDETOUR_XEX_IMPORT_DESCRIPTOR importTable;
	DWORD dwModuleCountIndex = 0;
	DWORD dwModuleIndex = 0;
	CHAR szModuleName[0x100];
	CHAR szHImportedModule[0x100];

	DWORD dwImportAddress = (DWORD)GetProcAddress((HMODULE)HImportedModule, (LPCSTR)Ordinal);

	if (dwImportAddress == NULL || HModule == NULL)
		return 0;

	importTable = (PDETOUR_XEX_IMPORT_DESCRIPTOR)
		RtlImageXexHeaderField((void*)*(DWORD *)((DWORD)HModule + 0x58), 0x000103FF);

	if (importTable == NULL)
		return 0;

	WideCharToMultiByte(CP_UTF8, NULL, (wchar_t*)*(DWORD*)((DWORD)HImportedModule + 0x30), -1, szHImportedModule, 0x100, NULL, NULL);

	for (DWORD dwModuleCount = 0; dwModuleCount < importTable->ModuleCount; dwModuleCount++)
	{
		DWORD i = dwModuleCountIndex;

		DWORD dwPointer = (DWORD)importTable + 0x0C + importTable->NameTableSize + dwModuleIndex;

		DWORD dwModuleSectionSize = *(DWORD *)dwPointer;

		dwPointer += 0x24 + 4;

		dwModuleIndex += dwModuleSectionSize;

		dwModuleSectionSize -= 0x24 + 4;

		dwModuleCountIndex += strlen((char*)((DWORD)importTable + 0x0C + i));

		strcpy(szModuleName, (char*)((DWORD)importTable + 0x0C + i));


		if (!strcmp(szModuleName, szHImportedModule))
		{

			for (DWORD dwSize = 0; dwSize < dwModuleSectionSize; dwSize += 8)
			{
				DWORD dwTempAddr = *(DWORD *)*(DWORD *)(dwPointer + dwSize);
				if (dwTempAddr == dwImportAddress)
					return *(DWORD *)(dwPointer + dwSize + 4);
			}
		}
	}
	return 0;
}

DWORD GetAddr(DWORD dwModuleBaseAddr, int Ordinal)
{
	HANDLE hModule;
	XexPcToFileHeader((PVOID)dwModuleBaseAddr, (PLDR_DATA_TABLE_ENTRY*)&hModule);
	HANDLE hImportedModule = (HANDLE)GetModuleHandle("xam.xex");
	return GetModuleImport(hModule, hImportedModule, Ordinal);
}

bool bLoaded;
bool gay;
void TamperedInit() {
	IW4MP::H_DrawIndexedPrimitiveDetour = new Detour<HRESULT>;
	IW4MP::H_R_DrawIndexedPrimitiveDetour = new Detour<HRESULT>;
	IW4MP::H_Menu_PaintAllDetour = new Detour<HRESULT>;
	IW4MP::H_DrawTextDetour = new Detour<HRESULT>;
	IW4MP::CL_ConsolePrintDetour = new Detour<HRESULT>;
	//IW4MP::StretchPicDetour = new Detour<void>;
	IW4MP::R_DrawStretchPicDetour = new Detour<void>;

	while (!bKillLoop)
	{
		Sleep(10);

		if (XamGetCurrentTitleId() == 0x41560817)
		{
			if (cstrcmp((char*)0x82012364, "viewModelHacks")) {
				if (bInitialized == FALSE)
				{
					IW4MP::BuildMenu();

					Sleep(3000);

					//2B 0B 00 FF
					*(int*)0x822AE400 = 0x2B030000; //AimTarget_GetTagPos

					*(int*)0x82134510 = 0x4E800020; //Autowall
					*(int*)0x821A4A58 = 0x4E800020; //Autowall

					*(int*)0x820EF12C = 0x3BA00001; //UAV
					*(byte*)0x82104093 = 0x01; //Laser

					ReadINI(0);

					if (!bPrecached)
						IW4MP::PrecacheAssets();

					*(char*)(*(int*)(0x825CED7C) + 0x08) = 0x01;

					//Scoreboard Ping
					*(int*)0x820C588C = 0x60000000;

					PatchInJump((PDWORD)0x820F4930, (DWORD)IW4MP::H_R_SetFrameFog, false);
					PatchInJump((PDWORD)0x82351728, (DWORD)IW4MP::H_R_EndFrame, false);

					HookFunctionStart((PDWORD)0x82140728, (PDWORD)IW4MP::H_CL_CreateNewCommandsStub, NULL, (DWORD)IW4MP::H_CL_CreateNewCommands);
					HookFunctionStart((PDWORD)0x82140320, (PDWORD)IW4MP::H_CL_WritePacketStub, NULL, (DWORD)IW4MP::H_CL_WritePacket);
					//HookFunctionStart((PDWORD)0x8234F998, (PDWORD)IW4MP::H_DrawPicStub, NULL, (DWORD)IW4MP::R_DrawStretchPic);

					IW4MP::H_DrawIndexedPrimitiveDetour->SetupDetour(0x82388028, IW4MP::H_DrawIndexedPrimitive);
					IW4MP::H_R_DrawIndexedPrimitiveDetour->SetupDetour(0x820AF1D0, IW4MP::H_R_DrawIndexedPrimitive);
					IW4MP::H_Menu_PaintAllDetour->SetupDetour(0x82285F08, IW4MP::H_Menu_PaintAll);
					IW4MP::H_DrawTextDetour->SetupDetour(0x82350258, IW4MP::H_DrawText);
					IW4MP::CL_ConsolePrintDetour->SetupDetour(0x8213BF80, IW4MP::CL_ConsolePrint);
					IW4MP::R_DrawStretchPicDetour->SetupDetour(0x821384D8, IW4MP::R_DrawStretchPic);

					InputStateAddr = GetAddr(0x82000000, 0x191);

					if (InputStateAddr != 0) {
						memcpy(oldInputState, (void*)InputStateAddr, 16);
						HookFunctionStart((PDWORD)GetAddr(0x82000000, 0x191), (PDWORD)IW4MP::XamInputGetStateHook_Stub, NULL, (DWORD)IW4MP::XamInputGetStateHook); //0x8216D8C8
					}

					short versionNamePatch1;
					int verionNameOffset = (int)"^1Eclipse Framework 1.0.1                                                                     ";

					if (verionNameOffset & 0x8000) // If bit 16 is 1
						versionNamePatch1 = (((verionNameOffset >> 16) & 0xFFFF) + 1); // lis %r11, dest>>16 + 1
					else
						versionNamePatch1 = ((verionNameOffset >> 16) & 0xFFFF); // lis %r11, dest>>16
					short versionNamePatch2 = (verionNameOffset & 0xFFFF);
					WriteMemory((LPVOID)0x8226DB6A, 2, (LPCVOID)&versionNamePatch1);
					WriteMemory((LPVOID)0x8226DB76, 2, (LPCVOID)&versionNamePatch2);

					XNotify(L"[Eclipse Framework] (MW2 Edition)");

					bInitialized = TRUE;
				}

				IW4MP::Agony_Monitor();
			}
		}
		else if (XamGetCurrentTitleId() == 0x41560855)
		{
			if (bInitialized == FALSE)
			{
				BO1::BuildMenu();

				/*if (!gay)
				{
					multiBoxbo1[0] = BO1::SL_GetString("j_spineupper", 0);
					multiBoxbo1[1] = BO1::SL_GetString("j_head", 0);
					multiBoxbo1[2] = BO1::SL_GetString("j_ankle_ri", 0);
					multiBoxbo1[3] = BO1::SL_GetString("j_ankle_le", 0);
					multiBoxbo1[4] = BO1::SL_GetString("j_spinelower", 0);
					multiBoxbo1[5] = BO1::SL_GetString("j_knee_ri", 0);
					multiBoxbo1[6] = BO1::SL_GetString("j_knee_le", 0);
					multiBoxbo1[7] = BO1::SL_GetString("j_neck", 0);

					gay = true;
				}*/

				Sleep(3000);

				//ReadINI(0);

				PatchInJump((DWORD *)0x8222B5D8, (DWORD)BO1::paintallHook, false);
				HookFunctionStart((PDWORD)0x82239508, (PDWORD)BO1::H_CL_WritePacketStub, NULL, (DWORD)BO1::H_CL_WritePacket);

				InputStateAddr = GetAddr(0x82000000, 0x191);

				if (InputStateAddr != 0) {
					memcpy(oldInputState, (void*)InputStateAddr, 16);
					HookFunctionStart((PDWORD)GetAddr(0x82000000, 0x191), (PDWORD)BO1::XamInputGetStateHook_Stub, NULL, (DWORD)BO1::XamInputGetStateHook); //0x8216D8C8
				}

				XNotify(L"[Eclipse Framework] (BO1 Edition)");

				bInitialized = TRUE;
			}

			BO1::Agony_Monitor();
		}
		else if (XamGetCurrentTitleId() == 0x4156081C)
		{
			if (bInitialized == FALSE)
			{
				WAW::BuildMenu();

				Sleep(3000);

				HookFunctionStart((PDWORD)0x822B2F38, (PDWORD)WAW::Menu_PaintAllStub, NULL, (DWORD)WAW::Menu_PaintAll);
				HookFunctionStart((PDWORD)0x821B0F30, (PDWORD)WAW::CL_WritePacketStub, NULL, (DWORD)WAW::CL_WritePacket);
				PatchInJump((DWORD*)0x8215B9D0, (DWORD)WAW::H_CG_DrawNightVisionOverlay, false);

				InputStateAddr = GetAddr(0x82000000, 0x191);

				if (InputStateAddr != 0) {
					memcpy(oldInputState, (void*)InputStateAddr, 16);
					HookFunctionStart((PDWORD)GetAddr(0x82000000, 0x191), (PDWORD)WAW::XamInputGetStateHook_Stub, NULL, (DWORD)WAW::XamInputGetStateHook); //0x8216D8C8
				}

				XNotify(L"[Eclipse Framework] (WAW Edition)");

				bInitialized = TRUE;
			}

			WAW::Agony_Monitor();
			ReadINI(0);
		}
		else if (XamGetCurrentTitleId() == 0x415608FC)
		{
			if (bInitialized == FALSE)
			{
				GHO::BuildMenu();

				Sleep(3000);

				//ReadINI(0);

				PatchInJump((DWORD *)0x8253E140, (DWORD)GHO::H_R_SetFrameFog, false);
				HookFunctionStart((PDWORD)0x822D4918, (PDWORD)GHO::H_CL_WritePacketStub, NULL, (DWORD)GHO::H_CL_WritePacket);

				InputStateAddr = GetAddr(0x82000000, 0x191);

				if (InputStateAddr != 0) {
					memcpy(oldInputState, (void*)InputStateAddr, 16);
					HookFunctionStart((PDWORD)GetAddr(0x82000000, 0x191), (PDWORD)GHO::XamInputGetStateHook_Stub, NULL, (DWORD)GHO::XamInputGetStateHook);//0x8216D8C8
				}

				XNotify(L"[Eclipse Framework] (Ghosts Edition. Not Supported.)");
				bInitialized = TRUE;
			}

			GHO::Agony_Monitor();
		}
		else if (XamGetCurrentTitleId() == 0x415608C3)
		{
			if (bInitialized == FALSE)
			{
				BO2::BuildMenu();

				Sleep(3000);

				//no flinch
				*(int*)0x826C7A64 = *(int*)0x8223FE80 = 0x60000000;

				//Patch the anti-rapid fire
				*(short*)0x8225E038 = 0x4800;

				//Radar patch
				*(int*)0x821B8FD4 = *(int*)0x821B90C8 = 0x60000000;

				//Unlimited class items
				BYTE byte[] = { 0x3b, 0x40, 0xcb, 0xe7 };
				memcpy((PVOID)0x826A5FBC, byte, 4);
				__int64 Autowall[3];
				//stop the bullet effects and sounds
				Autowall[0] = *(__int64*)0x82257C48;
				Autowall[1] = *(__int64*)0x82257D28;
				Autowall[2] = *(__int64*)0x82257D54;
				*(__int64*)0x82257C48 = 0x6000000048000028;
				*(int*)0x82257D28 = 0x60000000;
				*(int*)0x82257D54 = 0x60000000;

				*(long long*)0x8224D060 = 0x386000014E800020;
				*(long long*)0x821FA7F8 = 0x386000004E800020;

				*(int*)0x822DF558 = 0x4E800020;
				*(int*)0x82258520 = 0x4E800020;

				*(DWORD*)0x822585F8 = 0x60000000;
				*(DWORD*)0x82258D60 = 0x60000000;
				*(DWORD*)0x82258D68 = 0x60000000;
				*(DWORD*)0x82258D6C = 0x60000000;

				*(int*)0x822DF558 = 0x4E800020;
				*(int*)0x82258520 = 0x4E800020;


				ReadINI(0);

				PatchInJump((DWORD *)0x82262978, (DWORD)BO2::H_R_SetFrameFog, false);
				HookFunctionStart((PDWORD)0x8226C9C8, (PDWORD)BO2::H_CL_WritePacketStub, NULL, (DWORD)BO2::H_CL_WritePacket);

				InputStateAddr = GetAddr(0x82000000, 0x191);

				if (InputStateAddr != 0) {
					memcpy(oldInputState, (void*)InputStateAddr, 16);
					HookFunctionStart((PDWORD)GetAddr(0x82000000, 0x191), (PDWORD)BO2::XamInputGetStateHook_Stub, NULL, (DWORD)BO2::XamInputGetStateHook); //0x8216D8C8
				}

				XNotify(L"[Eclipse Framework] (BO2 Edition)");

				bInitialized = TRUE;
			}

			BO2::Agony_Monitor();
		}
		else if (XamGetCurrentTitleId() == 0x41560914)
		{
			if (bInitialized == FALSE)
			{
				AW::BuildMenu();

				Sleep(3000);

				ReadINI(0);

				PatchInJump((PDWORD)0x823884D8, (DWORD)AW::H_R_SetFrameFog, false);
				HookFunctionStart((PDWORD)0x823884D8, (PDWORD)AW::H_CL_WritePacketStub, NULL, (DWORD)AW::H_CL_WritePacket);

				InputStateAddr = GetAddr(0x82000000, 0x191);

				if (InputStateAddr != 0) {
					memcpy(oldInputState, (void*)InputStateAddr, 16);
					HookFunctionStart((PDWORD)GetAddr(0x82000000, 0x191), (PDWORD)AW::XamInputGetStateHook_Stub, NULL, (DWORD)AW::XamInputGetStateHook); //0x8216D8C8
				}

				XNotify(L"[Eclipse Framework] (AW)");

				bInitialized = TRUE;
			}

			AW::Agony_Monitor();
		}
		else if (XamGetCurrentTitleId() == 0x415608CB)
		{
			if (bInitialized == FALSE)
			{
				IW5MP::fillFunctionAddresses(false);
				IW5MP::BuildMenu();

				Sleep(3000);

				//ReadINI(0);

				DetourFunction((PDWORD)0x82444510, (DWORD)IW5MP::H_R_SetFrameFog);
				HookFunctionStart((PDWORD)0x823091D0, (PDWORD)IW5MP::Menu_PaintAllStub, NULL, (DWORD)IW5MP::Menu_PaintAll);
				HookFunctionStart((PDWORD)0x8216D8C8, (PDWORD)IW5MP::H_CL_CreateNewCommandsStub, NULL, (DWORD)IW5MP::H_CL_CreateNewCommands);
				HookFunctionStart((PDWORD)0x8216DAF0, (PDWORD)IW5MP::H_CL_WritePacketStub, NULL, (DWORD)IW5MP::H_CL_WritePacket);
				//DetourFunction((PDWORD)0x8257FF4C, (DWORD)IW5MP::XamInputGetStateHook);

				/*InputStateAddr = GetAddr(0x82000000, 0x191);

				if (InputStateAddr != 0) {
				memcpy(oldInputState, (void*)InputStateAddr, 16);
				HookFunctionStart((PDWORD)GetAddr(0x82000000, 0x191), (PDWORD)IW5MP::XamInputGetStateHook_Stub, NULL, (DWORD)IW5MP::XamInputGetStateHook); //0x8216D8C8
				}*/

				XNotify(L"[Eclipse Framework] (MW3)");

				bInitialized = TRUE;
			}

			IW5MP::Agony_Monitor();
		}
		else if (XamGetCurrentTitleId() == 0x415607E6)
		{
			if (bInitialized == FALSE)
			{
				IW3MP::BuildMenu();

				Sleep(3000);

				ReadINI(0);

				PatchInJump((DWORD *)0x821E7558, (DWORD)IW3MP::Menu_PaintAll, false);
				HookFunctionStart((PDWORD)0x822DA6C8, (PDWORD)IW3MP::CL_WritePacketStub, NULL, (DWORD)IW3MP::CL_WritePacket);

				InputStateAddr = GetAddr(0x82000000, 0x191);

				if (InputStateAddr != 0) {
					memcpy(oldInputState, (void*)InputStateAddr, 16);
					HookFunctionStart((PDWORD)GetAddr(0x82000000, 0x191), (PDWORD)IW3MP::XamInputGetStateHook_Stub, NULL, (DWORD)IW3MP::XamInputGetStateHook); //0x8216D8C8
				}

				XNotify(L"[Eclipse Framework] (COD 4 Edition)");

				bInitialized = TRUE;
			}
			IW3MP::Agony_Monitor();
		}
		else if (XamGetCurrentTitleId() == 0x5841125A)
		{
			if (bInitialized == FALSE)
			{
				XNotify(L"[Eclipse Framework] (CS:GO Edition)");

				bInitialized = TRUE;
			}
		}
	}
	DWORD Thr_Exit;
	ExitThread(Thr_Exit);
}

BOOL WINAPI DllMain(HANDLE hInstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		//printf("[Tampered CE] Module loading.\n");
		HANDLE bThread; DWORD bThreadID;
		ExCreateThread(&bThread, 0, &bThreadID, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)TamperedInit, NULL, 0x2);
		XSetThreadProcessor(bThread, 4);
		ResumeThread(bThread);
		CloseHandle(bThread);
		break;
	case DLL_PROCESS_DETACH:
		bKillLoop = true;

		//printf("[Tampered CE] Module unloading.\n");

		if (XamGetCurrentTitleId() != 0xFFFE07D1)
			memcpy((void*)InputStateAddr, oldInputState, 16);

		if (XamGetCurrentTitleId() == 0x41560817)
		{
			// R_SetFrameFog -- 7D 88 02 A6 91 81 FF F8  FB C1 FF E8 FB E1 FF F0
			*(QWORD*)(0x820F4930 + 0x00) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x820F4930 + 0x08) = 0xFBC1FFE8FBE1FFF0;

			// R_EndFrame -- 7D 88 02 A6 91 81 FF F8  94 21 FF A0 4B FF DF 6D
			*(QWORD*)(0x82351728 + 0x00) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x82351728 + 0x08) = 0x9421FFA04BFFDF6D;

			// CL_CreateNewCommands -- 7D 88 02 A6 91 81 FF F8  FB E1 FF F0 94 21 FF A0
			*(QWORD*)(0x82140728 + 0x00) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x82140728 + 0x08) = 0xFBE1FFF09421FFA0;

			// CL_WritePacket -- 7D 88 02 A6 48 26 33 B5  E9 81 F0 00 94 21 EF 00
			*(QWORD*)(0x82140320 + 0x00) = 0x7D8802A6482633B5;
			*(QWORD*)(0x82388028 + 0x00) = 0x7C8A237881640004;
			*(QWORD*)(0x82388028 + 0x08) = 0x8063000038A00000;

			// R_DrawStretchPic -- 7D 88 02 A6 91 81 FF F8  FB E1 FF F0 39 81 FF F0
			*(QWORD*)(0x821384D8 + 0x00) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x821384D8 + 0x08) = 0xFBE1FFF03981FFF0;

			IW4MP::H_DrawIndexedPrimitiveDetour->TakeDownDetour();
			*(QWORD*)(0x82140320 + 0x08) = 0xE981F0009421EF00;

			//R_DrawIndexedPrimitive -- 7C 8A 23 78 81 64 00 04  80 63 00 00 38 A0 00 00
			IW4MP::H_R_DrawIndexedPrimitiveDetour->TakeDownDetour();
			IW4MP::H_Menu_PaintAllDetour->TakeDownDetour();
			IW4MP::H_DrawTextDetour->TakeDownDetour();
			IW4MP::CL_ConsolePrintDetour->TakeDownDetour();
			IW4MP::R_DrawStretchPicDetour->TakeDownDetour();
			//IW4MP::CG_LocationalTraceDetour->TakeDownDetour();

			// R_DrawXModelSkinnedCached -- 7D 88 02 A6 91 81 FF F8  FB C1 FF E8 FB E1 FF F0
			*(QWORD*)(0x823982C0 + 0x00) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x823982C0 + 0x08) = 0xFBC1FFE8FBE1FFF0;

			//7D 88 02 A6 91 81 FF F8  FB C1 FF E8 FB E1 FF F0
			*(QWORD*)(0x8234F998 + 0x0) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x8234F998 + 0x8) = 0xFBC1FFE8FBE1FFF0;

			// Menu_PaintAll -- 7D 88 02 A6 48 11 D7 E1  DB E1 FF D8 94 21 FF 70
			//*(QWORD*)(0x82285F08 + 0x00) = 0x7D8802A64811D7E1;
			//*(QWORD*)(0x82285F08 + 0x08) = 0xDBE1FFD89421FF70;
		}
		else if (XamGetCurrentTitleId() == 0x415608FC)
		{
			*(QWORD*)(0x8253E140 + 0x00) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x8253E140 + 0x08) = 0xFBC1FFE8FBE1FFF0;

			*(QWORD*)(0x822D68C0 + 0x00) = 0x7D8802A648504649;
			*(QWORD*)(0x822D68C0 + 0x08) = 0xE981F0009421EED0;

			*(QWORD*)(0x822D67E8 + 0x00) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x822D67E8 + 0x08) = 0xFBC1FFE8FBE1FFF0;

			//0x822D4918
			//3D 60 82 BB 1D 23 01 F8  39 4B C4 08 3D 60 82 BB
			*(QWORD*)(0x822D4918 + 0x00) = 0x3D6082BB1D2301F8;
			*(QWORD*)(0x822D4918 + 0x08) = 0x394BC4083D6082BB;

			//0x824ED7E0
			//7D 88 02 A6 48 2E D7 2D  94 21 FF 50 3D 60 83 C0
			*(QWORD*)(0x824ED7E0 + 0x00) = 0x7D8802A6482ED72D;
			*(QWORD*)(0x824ED7E0 + 0x08) = 0x9421FF503D6083C0;
		}
		else if (XamGetCurrentTitleId() == 0x41560914)
		{
			*(QWORD*)(0x823884D8 + 0x00) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x823884D8 + 0x08) = 0xFBC1FFE8FBE1FFF0;

			*(QWORD*)(0x825B7358 + 0x00) = 0x7D8802A64BC3CB9D;
			*(QWORD*)(0x825B7358 + 0x08) = 0xE981F0009421EEC0;

			*(QWORD*)(0x825B79D8 + 0x00) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x825B79D8 + 0x08) = 0xFBC1FFE8FBE1FFF0;
		}
		else if (XamGetCurrentTitleId() == 0x41560855)
		{
			*(int*)(0x8223B3C8) = 0x7D8802A6;
			*(int*)(0x8223B3C8 + 0x4) = 0x48477439;
			*(int*)(0x8223B3C8 + 0x8) = 0x9421F6C0;
			*(int*)(0x8223B3C8 + 0xC) = 0x39610094;

			*(int*)(0x821B6A78) = 0x7D8802A6;
			*(int*)(0x821B6A78 + 0x4) = 0x9181FFF8;
			*(int*)(0x821B6A78 + 0x8) = 0xFBE1FFF0;
			*(int*)(0x821B6A78 + 0xC) = 0x9421FF70;
		}
		else if (XamGetCurrentTitleId() == 0x415608C3)
		{
			char buffer[16] = { 0x7D, 0x88, 0x02, 0xA6, 0x48, 0x37, 0xB9, 0xA5, 0x94, 0x21, 0xFF, 0x10, 0x3D, 0x40, 0x82, 0xAA };
			memcpy((void*)0x8259A5E0, (void*)buffer, 16);

			char buffer1[16] = { 0x7D, 0x88, 0x02, 0xA6, 0x91, 0x81, 0xFF, 0xF8, 0xFB, 0xC1, 0xFF, 0xE8, 0xFB, 0xE1, 0xFF, 0xF0 };
			memcpy((void*)0x821C5CA0, (void*)buffer1, 16);

			char buffer2[16] = { 0x7D, 0x88, 0x02, 0xA6, 0x48, 0x6A, 0x95, 0xA1, 0x94, 0x21, 0xF6, 0xC0, 0x3D, 0x60, 0x82, 0xAA };
			memcpy((void*)0x8226C9C8, (void*)buffer2, 16);

			char buffer3[16] = { 0x7D, 0x88, 0x02, 0xA6, 0x91, 0x81, 0xFF, 0xF8, 0xFB, 0xC1, 0xFF, 0xE8, 0xFB, 0xE1, 0xFF, 0xF0 };
			memcpy((void*)0x825C5330, (void*)buffer3, 16);

			//0x82262978
			//3D 60 82 C1 C0 03 00 38  39 4B 44 C0 D0 0A 12 8C
			*(QWORD*)(0x82262978 + 0x0) = 0x3D6082C1C0030038;
			*(QWORD*)(0x82262978 + 0x8) = 0x394B44C0D00A128C;

			//7D 88 02 A6 48 00 7D DD  94 21 FF 70 83 C4 00 04
			*(QWORD*)(0x8290E1A8 + 0x0) = 0x7D8802A648007DDD;
			*(QWORD*)(0x8290E1A8 + 0x8) = 0x9421FF7083C40004;

			//7D 88 02 A6 48 7A AD 89  94 21 FF 30 7C 92 23 78
			*(QWORD*)(0x8216B1D0 + 0x0) = 0x7D8802A6487AAD89;
			*(QWORD*)(0x8216B1D0 + 0x8) = 0x9421FF307C922378;
		}
		else if (XamGetCurrentTitleId() == 0x4156081C)
		{
			*(__int64*)(0x8215B9D0 + 0x0) = 0x7D8802A69181FFF8;
			*(__int64*)(0x8215B9D0 + 0x8) = 0xFBE1FFF09421FF70;

			*(__int64*)(0x821B0D40 + 0x0) = 0x7D8802A69181FFF8;
			*(__int64*)(0x821B0D40 + 0x8) = 0xFBC1FFE8FBE1FFF0;

			//7D 88 02 A6 48 28 D6 E5  94 21 F6 D0 7C 7F 1B 78
			*(__int64*)(0x821B0F30 + 0x0) = 0x7D8802A64828D6E5;
			*(__int64*)(0x821B0F30 + 0x8) = 0x9421F6D07C7F1B78;

			//7D 88 02 A6 48 00 6B 19  94 21 FF 80 F8 61 00 90
			*(__int64*)(0x82437B20 + 0x0) = 0x7D8802A648006B19;
			*(__int64*)(0x82437B20 + 0x8) = 0X9421FF80F8610090;

			//7D 88 02 A6 48 18 B6 DD  DB A1 FF 80 DB C1 FF 88
			*(__int64*)(0x822B2F38 + 0x0) = 0x7D8802A64818B6DD;
			*(__int64*)(0x822B2F38 + 0x8) = 0xDBA1FF80DBC1FF88;

			//WAW::H_DrawIndexedPrimitiveDetour->TakeDownDetour();
			//WAW::R_DrawXModelSkinnedCachedDetour->TakeDownDetour();
		}
		else if (XamGetCurrentTitleId() == 0x415607E6)
		{
			//7D 88 02 A6 4B F3 9D 99  DB A1 FF B8 DB C1 FF C0
			*(QWORD*)(0x821E7558 + 0x0) = 0x7D8802A64BF39D99;
			*(QWORD*)(0x821E7558 + 0x8) = 0xDBA1FFB8DBC1FFC0;
			//7D 88 02 A6 4B E4 6C 01  94 21 F6 E0 7C 7F 1B 78
			*(QWORD*)(0x822DA6C8 + 0x0) = 0x7D8802A64BE46C01;
			*(QWORD*)(0x822DA6C8 + 0x8) = 0x9421F6E07C7F1B78;
			//7D 88 02 A6 91 81 FF F8  FB C1 FF E8 FB E1 FF F0
			*(QWORD*)(0x822DCAE8 + 0x0) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x822DCAE8 + 0x8) = 0xFBC1FFE8FBE1FFF0;
			//7D 88 02 A6 91 81 FF F8  94 21 FF 90 7C 66 1B 78
			*(QWORD*)(0x8231A488 + 0x0) = 0x7D8802A69181FFF8;
			*(QWORD*)(0x8231A488 + 0x8) = 0x9421FF907C661B78;
			//7D 88 02 A6 4B FE C1 AD  94 21 FF 60 F8 61 00 B0
			*(QWORD*)(0x82135140 + 0x0) = 0x7D8802A64BFEC1AD;
			*(QWORD*)(0x82135140 + 0x8) = 0x9421FF60F86100B0;
		}
		Sleep(2000);
		return true;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}