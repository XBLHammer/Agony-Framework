#include "stdafx.h"

#include "kernel.h"

#include "Detour.h"

// Variables
bool bKillThread;
BOOL bInitialized = FALSE;
XINPUT_STATE InputState;

VOID __declspec(naked) GLPR_FUN(VOID)
{
	__asm {
		std     r14, -0x98(sp)
		std     r15, -0x90(sp)
		std     r16, -0x88(sp)
		std     r17, -0x80(sp)
		std     r18, -0x78(sp)
		std     r19, -0x70(sp)
		std     r20, -0x68(sp)
		std     r21, -0x60(sp)
		std     r22, -0x58(sp)
		std     r23, -0x50(sp)
		std     r24, -0x48(sp)
		std     r25, -0x40(sp)
		std     r26, -0x38(sp)
		std     r27, -0x30(sp)
		std     r28, -0x28(sp)
		std     r29, -0x20(sp)
		std     r30, -0x18(sp)
		std     r31, -0x10(sp)
		stw     r12, -0x8(sp)
		blr
	}
}

HRESULT returnResult;
DWORD WriteMemory(LPVOID address, DWORD size, LPCVOID data)
{
	DWORD outInt;
#ifdef _DEBUG
	returnResult = DmSetMemory(address, size, data, &outInt);
#endif
#ifdef NDEBUG
	returnResult = memcpy(address, data, size) == address ? ERROR_SUCCESS : TYPE_E_UNDEFINEDTYPE;
	outInt = size;
#endif

	return outInt;
}

VOID DetourFunction(PDWORD FunctionAddress, DWORD DestinationFunction)
{
	if (DestinationFunction & 0x8000)
	{
		FunctionAddress[0] = 0x3D600000 + (((DestinationFunction >> 16) & 0xFFFF) + 1);
	}
	else
	{
		FunctionAddress[0] = 0x3D600000 + ((DestinationFunction >> 16) & 0xFFFF);
	}
	FunctionAddress[1] = 0x396B0000 + (DestinationFunction & 0xFFFF);
	FunctionAddress[2] = 0x7D6903A6;
	FunctionAddress[3] = 0x4E800420;
}

DWORD RelinkGPLR(int offset, PDWORD saveStubAddr, PDWORD orgAddr)
{
	DWORD saver[0x30];

	memcpy(saver, GLPR_FUN, 0x30 * 4);

	DWORD inst = 0, repl = 0;
	int i;
	// if the msb is set in the instruction, set the rest of the bits to make the int negative
	if (offset & 0x2000000)
		offset = offset | 0xFC000000;
	memcpy(&repl, &orgAddr[((DWORD)offset) / 4], 4);
	for (i = 0; i < 20; i++)
	{
		if (repl == saver[i])
		{
			int newOffset = (int)((PDWORD)(GLPR_FUN)+(DWORD)i) - (int)saveStubAddr;
			inst = 0x48000001 | (newOffset & 0x3FFFFFC);
		}
	}
	return inst;
}


DWORD ResolveFunction(PCHAR ModuleName, DWORD Ordinal)
{
	HANDLE ModuleHandle; DWORD Address;
	XexGetModuleHandle(ModuleName, &ModuleHandle);
	XexGetProcedureAddress(ModuleHandle, Ordinal, &Address);
	return Address;
}

VOID PatchInJump(DWORD* addr, DWORD dest, BOOL linked) {
	DWORD temp[4];

	if (dest & 0x8000) // If bit 16 is 1
		temp[0] = 0x3D600000 + (((dest >> 16) & 0xFFFF) + 1); // lis     %r11, dest>>16 + 1
	else
		temp[0] = 0x3D600000 + ((dest >> 16) & 0xFFFF); // lis     %r11, dest>>16

	temp[1] = 0x396B0000 + (dest & 0xFFFF); // addi    %r11, %r11, dest&0xFFFF
	temp[2] = 0x7D6903A6; // mtctr    %r11

	if (linked)
		temp[3] = 0x4E800421; // bctrl
	else
		temp[3] = 0x4E800420; // bctr

	memcpy(addr, temp, 0x10);
}

VOID HookFunctionStart(PDWORD addr, PDWORD saveStub, PDWORD oldData, DWORD dest)
{
	DWORD temp[0x10];
	DWORD addrtemp[0x10];
	memcpy(addrtemp, addr, 0x10 * 4);

	if ((saveStub != NULL) && (addr != NULL))
	{
		int i;
		DWORD addrReloc = (DWORD)(&addr[4]);// replacing 4 instructions with a jump, this is the stub return address
		if (addrReloc & 0x8000) { // If bit 16 is 1
								  //setmemdm( &saveStub[0], (0x3D600000 + (((addrReloc >> 16) & 0xFFFF) + 1)));
			temp[0] = 0x3D600000 + (((addrReloc >> 16) & 0xFFFF) + 1); // lis %r11, dest>>16 + 1printf("  - one\r\n");
		}
		else {
			//setmemdm( &saveStub[0], (0x3D600000 + (((addrReloc >> 16) & 0xFFFF) + 1)));
			temp[0] = 0x3D600000 + ((addrReloc >> 16) & 0xFFFF); // lis %r11, dest>>16
		}

		temp[1] = 0x396B0000 + (addrReloc & 0xFFFF); // addi %r11, %r11, dest&0xFFFF
		temp[2] = 0x7D6903A6; // mtctr %r11
							  // instructions [3] through [6] are replaced with the original instructions from the function hook
							  // copy original instructions over, relink stack frame saves to local ones
		if (oldData != NULL)
		{
			for (i = 0; i<4; i++)
				oldData[i] = addrtemp[i];
		}
		for (i = 0; i<4; i++)
		{
			if ((addrtemp[i] & 0x48000003) == 0x48000001) // branch with link
			{
				temp[i + 3] = RelinkGPLR((addrtemp[i] & ~0x48000003), &saveStub[i + 3], &addr[i]);
			}
			else
			{
				temp[i + 3] = addrtemp[i];
			}
		}

		temp[7] = 0x4E800420; // bctr
		memcpy(saveStub, temp, 8 * 4);
		PatchInJump(addr, dest, FALSE);
	}
}

typedef struct _HV_IMAGE_IMPORT_TABLE {
	BYTE NextImportDigest[0x14]; // 0x0 sz:0x14
	DWORD ModuleNumber; // 0x14 sz:0x4
	DWORD Version[2]; // 0x18 sz:0x8
	BYTE Unused; // 0x20 sz:0x1
	BYTE ModuleIndex; // 0x21 sz:0x1
	WORD ImportCount; // 0x22 sz:0x2
} HV_IMAGE_IMPORT_TABLE, *PHV_IMAGE_IMPORT_TABLE; // size 36
C_ASSERT(sizeof(HV_IMAGE_IMPORT_TABLE) == 0x24);

typedef struct _XEX_IMPORT_TABLE_ORG {
	DWORD TableSize; // 0x0 sz:0x4
	HV_IMAGE_IMPORT_TABLE ImportTable; // 0x4 sz:0x24
} XEX_IMPORT_TABLE_ORG, *PXEX_IMPORT_TABLE_ORG; // size 40
C_ASSERT(sizeof(XEX_IMPORT_TABLE_ORG) == 0x28);

DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, PCHAR ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {
	DWORD address = (DWORD)ResolveFunction(ImportedModuleName, Ordinal);
	if (address == NULL) {
		return S_FALSE;
	}

	VOID* headerBase = Module->XexHeaderBase;
	PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(headerBase, 0x000103FF);
	if (importDesc == NULL) {
		return S_FALSE;
	}

	DWORD result = 2;
	CHAR* stringTable = (CHAR*)(importDesc + 1);
	XEX_IMPORT_TABLE_ORG* importTable = (XEX_IMPORT_TABLE_ORG*)(stringTable + importDesc->NameTableSize);

	for (DWORD x = 0; x < importDesc->ModuleCount; x++) {
		DWORD* importAdd = (DWORD*)(importTable + 1);
		for (DWORD y = 0; y < importTable->ImportTable.ImportCount; y++) {
			DWORD value = *((DWORD*)importAdd[y]);
			if (value == address) {
				memcpy((DWORD*)importAdd[y], &PatchAddress, 4);
				DWORD newCode[4];
				PatchInJump(newCode, PatchAddress, FALSE);
				memcpy((DWORD*)importAdd[y + 1], newCode, 16);
				result = S_OK;
			}
		}

		importTable = (XEX_IMPORT_TABLE_ORG*)(((BYTE*)importTable) + importTable->TableSize);
	}

	return result;
}

typedef enum {
	XNOTIFYUI_TYPE_FRIENDONLINE = 0,
	XNOTIFYUI_TYPE_GAMEINVITE = 1,
	XNOTIFYUI_TYPE_FRIENDREQUEST = 2,
	XNOTIFYUI_TYPE_GENERIC = 3, // mail icon
	XNOTIFYUI_TYPE_MULTIPENDING = 4,
	XNOTIFYUI_TYPE_PERSONALMESSAGE = 5,
	XNOTIFYUI_TYPE_SIGNEDOUT = 6,
	XNOTIFYUI_TYPE_SIGNEDIN = 7,
	XNOTIFYUI_TYPE_SIGNEDINLIVE = 8,
	XNOTIFYUI_TYPE_SIGNEDINNEEDPASS = 9,
	XNOTIFYUI_TYPE_CHATREQUEST = 10,
	XNOTIFYUI_TYPE_CONNECTIONLOST = 11,
	XNOTIFYUI_TYPE_DOWNLOADCOMPLETE = 12,
	XNOTIFYUI_TYPE_SONGPLAYING = 13, // music icon
	XNOTIFYUI_TYPE_PREFERRED_REVIEW = 14, // happy face icon
	XNOTIFYUI_TYPE_AVOID_REVIEW = 15, // sad face icon
	XNOTIFYUI_TYPE_COMPLAINT = 16, // hammer icon
	XNOTIFYUI_TYPE_CHATCALLBACK = 17,
	XNOTIFYUI_TYPE_REMOVEDMU = 18,
	XNOTIFYUI_TYPE_REMOVEDGAMEPAD = 19,
	XNOTIFYUI_TYPE_CHATJOIN = 20,
	XNOTIFYUI_TYPE_CHATLEAVE = 21,
	XNOTIFYUI_TYPE_GAMEINVITESENT = 22,
	XNOTIFYUI_TYPE_CANCELPERSISTENT = 23,
	XNOTIFYUI_TYPE_CHATCALLBACKSENT = 24,
	XNOTIFYUI_TYPE_MULTIFRIENDONLINE = 25,
	XNOTIFYUI_TYPE_ONEFRIENDONLINE = 26,
	XNOTIFYUI_TYPE_ACHIEVEMENT = 27,
	XNOTIFYUI_TYPE_HYBRIDDISC = 28,
	XNOTIFYUI_TYPE_MAILBOX = 29, // mailbox icon
								 // missing a few
								 XNOTIFYUI_TYPE_EXCLAIM = 34, // exclamation mark icon
								 XNOTIFYUI_TYPE_GARBAGE = 68, // garbage can icon
} XNOTIFYQUEUEUI_TYPE;

VOID(__cdecl *XNotifyQueueUI)(DWORD dwType, DWORD dwUserIndex, DWORD dwPriority, LPCWSTR pwszStringParam, ULONGLONG qwParam) = (VOID(__cdecl *)(DWORD, DWORD, DWORD, LPCWSTR, ULONGLONG))ResolveFunction("xam.xex", 0x290);
VOID XNotifyThread(PWCHAR NotifyText)
{
	XNotifyQueueUI(14, 0, 2, NotifyText, NULL);
}
VOID XNotify(PWCHAR NotifyText)
{
	if (KeGetCurrentProcessType() != USER_PROC)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)XNotifyThread, (LPVOID)NotifyText, 0, NULL);
	}
	else { XNotifyThread(NotifyText); }
}

VOID(__cdecl *XNotifyQueueUI1)(DWORD dwType, DWORD dwUserIndex, DWORD dwPriority, LPCWSTR pwszStringParam, ULONGLONG qwParam) = (VOID(__cdecl *)(DWORD, DWORD, DWORD, LPCWSTR, ULONGLONG))ResolveFunction("xam.xex", 0x290);
VOID XNotifyThread1(PWCHAR NotifyText)
{
	XNotifyQueueUI1(XNOTIFYUI_TYPE_COMPLAINT, 0, 2, NotifyText, NULL);
}
VOID XNotify1(PWCHAR NotifyText)
{
	if (KeGetCurrentProcessType() != USER_PROC)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)XNotifyThread1, (LPVOID)NotifyText, 0, NULL);
	}
	else { XNotifyThread(NotifyText); }
}
DWORD(__cdecl *XamGetCurrentTitleId)() = (DWORD(__cdecl *)())ResolveFunction("xam.xex", 0x1CF);

bool GetAsyncKeyState(int button)
{
	XInputGetState(0, &InputState);

	if (button == 0) return true;

	else if (button == 0x1337) return (InputState.Gamepad.bLeftTrigger / 30) > 0;
	else if (button == 0x1338) return (InputState.Gamepad.bRightTrigger / 30) > 0;

	return (InputState.Gamepad.wButtons & button);
}

bool cstrcmp(char * a, char *b) {
	return !(strcmp(a, b));
}

bool bKillLoop;

float colorWhiteTrans[4] = { 1.0f, 1.0f, 1.0f, 0.6f };
float colorYellowTrans[4] = { 1.0f, 1.0f, 0.0f, 0.8f };
float colorRedTrans[4] = { 1.0f, 0.0f, 0.0f, 0.8f };
float colorOrangeTrans[4] = { 1.0f, 0.5f, 0.0f, 0.8f };
float colorCyanTrans[4] = { 0.0f, 0.8f, 1.0f, 0.8f };
float colorBlueTrans[4] = { 0.0f, 0.0f, 1.0f, 0.8f };
float colorGreenTrans[4] = { 0.0f, 1.0f, 0.0f, 0.8f };
float colorBlackTrans[4] = { 0.0f, 0.0f, 0.0f, 0.8f };
float colorPurpleTrans[4] = { 0.45f, 0.0f, 0.611f, 0.8f };
float colorTestTrans[4] = { 0.5f, 0.8f, 0.6f, 0.4f };

typedef float vec_t;
class Vector3
{
public:
	// Construction/destruction
	float x, y, z;
	inline Vector3(void) { }
	inline Vector3(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	inline Vector3(double X, double Y, double Z) { x = (float)X; y = (float)Y; z = (float)Z; }
	inline Vector3(int X, int Y, int Z) { x = (float)X; y = (float)Y; z = (float)Z; }
	inline Vector3(float X, float Y, int Z) { x = (float)X; y = (float)Y; z = (int)Z; }
	inline Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
	inline Vector3(float rgfl[3]) { x = rgfl[0]; y = rgfl[1]; z = rgfl[2]; }
	inline void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);
	// Operators
	inline Vector3 operator-(void) const { return Vector3(-x, -y, -z); }
	inline int operator==(const Vector3& v) const { return x == v.x && y == v.y && z == v.z; }
	inline int operator!=(const Vector3& v) const { return !(*this == v); }
	inline Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
	inline Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
	inline Vector3 operator*(float fl) const { return Vector3(x*fl, y*fl, z*fl); }
	inline Vector3 operator/(float fl) const { return Vector3(x / fl, y / fl, z / fl); }
	void operator += (const Vector3& add) { x += add.x; y += add.y; z += add.z; }
	void operator += (const float add) { x += add; y += add; z += add; }
	void operator -= (const Vector3& sub) { x -= sub.x; y -= sub.y; z -= sub.z; }
	void operator *= (const float mul) { x *= mul; y *= mul; z *= mul; }
	void operator /= (const float mul) { x /= mul; y /= mul; z /= mul; }

	// Methods
	inline void CopyToArray(float* rgfl) const { rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; }
	inline float Length(void) const { return (float)sqrtf(x*x + y*y + z*z); }
	inline float LengthXY(void) const { return (float)sqrtf(x*x + y*y); }
	operator float *() { return &x; } // Vector3s will now automatically convert to float * when needed
	operator const float *() const { return &x; } // Vector3s will now automatically convert to float * when needed
	inline Vector3 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector3(x * flLen, y * flLen, z * flLen);
	}

	vec_t* Base();
	vec_t const* Base() const;
	inline float Length2D(void) const { return (float)sqrtf(x*x + y*y); }

	inline bool NormalizeAngle()
	{
		if (x != x || y != y || z != z) return false;

		if (x > 180) x -= 360.f;
		if (x < -180) x += 360.f;
		if (y > 180) y -= 360.f;
		if (y < -180) y += 360.f;

		return x >= -180.f && x <= 180.f && y >= -180.f && y <= 180.f;
	}

	inline bool ClampAngle()
	{
		if (x > 85.f) x = 85.f;
		if (x < -85.f) x = -85.f;

		z = 0.f;

		return x >= -85.f && x <= 85.f && y >= -180.f && y <= 180.f;
	}

	inline Vector3 AddFloat(float f) {
		return Vector3(x + f, y + f, z + f);
	}

	float NormalizeInPlace();
	float Dot(const Vector3& vOther) const;
};

inline Vector3 operator*(float fl, const Vector3& v) { return v * fl; }

inline void Vector3::Init(vec_t ix, vec_t iy, vec_t iz)
{
	x = ix; y = iy; z = iz;
}

inline vec_t const* Vector3::Base() const
{
	return (vec_t const*)this;
}

inline vec_t* Vector3::Base()
{
	return (vec_t*)this;
}

inline float Vector3::NormalizeInPlace()
{
	Vector3& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;

	return iradius;
}

inline float Vector3::Dot(const Vector3& vOther) const
{
	const Vector3& a = *this;

	return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}

class Vector3Aligned : public Vector3
{
public:
	Vector3Aligned()
	{
		x = y = z = 0;
	}

	Vector3Aligned(const Vector3& in)
	{
		x = in.x;
		y = in.y;
		z = in.z;
	}

	float w;
};

struct Vector2
{
	// Construction/destruction
	float x, y;
};

int XNADDRA(int client)
{
	int num = XamGetCurrentTitleId();
	int currentTitle = num;
	int num2 = num;
	int result;
	if (num2 <= 1096157379u)
	{
		if (num2 <= 1096157207u)
		{
			if (num2 == 1096157158u)
			{
				return 2185484032u + client * 184u;
			}
			if (num2 == 1096157207u)
			{
				return 2187914946u + client * 192u;
			}
		}
		else
		{
			if (num2 == 1096157269u)
			{
				return 2191492176u + client * 512u;
			}
			if (num2 == 1096157379u)
			{
				return 2194326432u + client * 328u;
			}
		}
	}
	else if (num2 <= 1096157436u)
	{
		if (num2 == 1096157387u)
		{
			return 2188513004u + client * 344u;
		}
		if (num2 == 1096157436u)
		{
			return 2193348148u + client * 448u;
		}
	}
	else
	{
		if (num2 == 1096157460u)
		{
			return 2193090112u + client * 848u;
		}
		if (num2 == 1096157469u)
		{
			return 3298693576u + client * 264u;
		}
	}
}


int GetIP(int address)
{
	int num = XamGetCurrentTitleId();
	int currentTitle = num;
	int num2 = num;
	int result;
	if (num2 <= 1096157379u)
	{
		if (num2 <= 1096157207u)
		{
			if (num2 == 1096157158u)
			{
				return address + 88u;
			}
			if (num2 == 1096157207u)
			{
				return address + 66u;
			}
		}
		else
		{
			if (num2 == 1096157269u)
			{
				return address + 96u;
			}
			if (num2 == 1096157379u)
			{
				return address + 124u;
			}
		}
	}
	else if (num2 <= 1096157436u)
	{
		if (num2 == 1096157387u)
		{
			return address + 184u;
		}
		if (num2 == 1096157436u)
		{
			return address + 232u;
		}
	}
	else
	{
		if (num2 == 1096157460u)
		{
			return address + 668u;
		}
	}
}

#pragma region Colors

float colRED[4] = { 1, 0, 0, 0.6 };
float colBLUE[4] = { 0, 0, 1, 0.8f };
float colGREEN[4] = { 0, 1, 0, 1 };
float colYELLOW[4] = { 1, 1, 0, 1 };
//float colCYAN[4] = { 0, .45, 1, 1 };
float colCYAN[4] = { 0.0f, 0.8f, 1.0f, 0.8f };
float colBONE[4] = { 0, 1, 1, 1 };
float colPURPLE[4] = { 1, 0, 1, 1 };
float colWHITE[4] = { 1, 1, 1, 1 };
float colBLACK[4] = { 0, 0, 0, 0.7 };
float colGRAY[4] = { 0.25, 0.25, 0.25, 0.85 };
float colDGRAY[4] = { 0.15, 0.15, 0.15, 0.85 };

float colORANGE[4] = { 1, .65, 0, 1 };
float colREDs[4] = { 1, 0, 0, .6 };
float colBLUEs[4] = { 0, 0, 1, .6 };
float colGREENs[4] = { 0, 1, 0, .6 };
float colYELLOWs[4] = { 1, 1, 0, .6 };
float colCYANs[4] = { 0, 1, 1, .6 };
float colPURPLEs[4] = { 1, 0, 1, .6 };
float colBLACKs[4] = { 0, 0, 0, .6 };
float colORANGEs[4] = { 1, .65, 0, .6 };
float colWHITEs[4] = { 1, 1, 1, .65 };
float colSHADER[4] = { 0, 0, 0, .25 };
float sRed[4] = { 1, 0, 0, .35 };
float sGreen[4] = { 0, 1, 0, .35 };
float sBlue[4] = { 0, 0, 1, .35 };
float sYellow[4] = { 1, 1, 0, .35 };
float sCyan[4] = { 0, 1, 1, .35 };
float sPurple[4] = { 1, 0, 1, .35 };
float sOrange[4] = { 1, .65, 0, .35 };
float radarLine[4] = { 1, 1, 1, 0.4 };

#pragma endregion

#define M_PI 3.14159265358979323846f
#define NAN	_CSTD _FNan._Float

Vector3 Difference(Vector3 Target, Vector3 Entity)
{
	Vector3 Return;
	Return.x = Target.x - Entity.x;
	Return.y = Target.y - Entity.y;
	Return.z = Target.z - Entity.z;
	return Return;
}

float DotProduct(Vector3 hax, Vector3 Vector)
{
	return (hax.x * Vector.x) + (hax.y * Vector.y) + (hax.z * Vector.z);
}

Vector3 SubstractVector(Vector3 Vec1, Vector3 Vec2)
{
	Vector3 Output;
	Output.x = Vec1.x - Vec2.x;
	Output.y = Vec1.y - Vec2.y;
	Output.z = Vec1.z - Vec2.z;
	return Output;
}

Vector3 VectorAdd(Vector3 veca, Vector3 vecb)
{
	Vector3 Ret;
	Ret.x = veca.x + vecb.x;
	Ret.y = veca.y + vecb.y;
	Ret.z = veca.z + vecb.z;
	return Ret;
}

Vector3 VectorScale(Vector3 in, float scale) {
	Vector3 Ret;
	Ret.x = in.x * scale;
	Ret.y = in.y * scale;
	Ret.z = in.z * scale;
	return Ret;
}

Vector3 AnglesToForward_0(Vector3 Angles)
{
	float angle, sr, sp, sy, cr, cp, cy, PiDiv;
	PiDiv = M_PI / 180.0f;
	angle = Angles.y * PiDiv;
	sy = sinf(angle);
	cy = cosf(angle);
	angle = Angles.x * PiDiv;
	sp = sinf(angle);
	cp = cosf(angle);
	Vector3 Forward;
	Forward.x = (cp * cy);
	Forward.y = (cp * sy);
	Forward.z = (-sp);
	return Forward;
}

Vector3 AnglesToForward(Vector3 Angles, float Distance = 250.0f)
{
	float angle, sp, sy, cp, cy, PiDiv;
	PiDiv = M_PI / 180.0f;
	angle = Angles.y * PiDiv;
	sy = sinf(angle);
	cy = cosf(angle);
	angle = Angles.x * PiDiv;
	sp = sinf(angle);
	cp = cosf(angle);
	Vector3 Forward;
	Forward.x = (cp * cy * Distance);
	Forward.y = (cp * sy * Distance);
	Forward.z = (-sp * Distance);
	return Forward;
}

void angleVectors(Vector3 &angles, Vector3 *forward, Vector3 *right, Vector3 *up) {
	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = angles.y * (M_PI * 2.0f / 360.0f);
	sy = sinf(angle);
	cy = cosf(angle);
	angle = angles.x * (M_PI * 2.0f / 360.0f);
	sp = sinf(angle);
	cp = cosf(angle);
	angle = angles.z * (M_PI * 2.0f / 360.0f);
	sr = sinf(angle);
	cr = cosf(angle);

	if (forward) {
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right) {
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up) {
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

float dx, dy, dz;
float GetDistance(Vector3 c1, Vector3 c2)
{
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return (sqrt((float)((dx * dx) + (dy * dy) + (dz * dz))) / 55.0f);
}

/* Tan (radians) reversed */
float Tan(float input)
{
	float v1 = input;
	float v2 = sinf(v1);
	float v3 = cosf(v1);
	if (v3 != 0)
	{
		return v2 / v3;
	}
	else return NAN;
}

/* Vector normalizing */
float length(float x, float y, float z)
{
	return sqrt(x*x + y*y + z*z);
}

void normalize(float *x, float *y, float *z)
{
	float l = 1 / length(*x, *y, *z);
	*x *= l; *y *= l; *z *= l;
}

void TransformSeed(int *seed)
{
	/* Transforms input to usable value */
	*seed = 214013 * (214013 * (214013 * (214013 * *seed + 2531011) + 2531011) + 2531011) + 2531011;
}

int TransformSeed_v2(int seed) {
	return 0x343FD * (0x343FD * (0x343FD * (0x343FD * seed + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3;
}

/* AngleToShort conversions */
#define	ANGLE2SHORT(x)	(((int)((x) * 65536.0f / 360.0f)) & 65535)
#define	SHORT2ANGLE(x)	((x) * (360.0/65536.0f))

void AngleNormalize(float* angle)
{
	if (angle[0] > 89.0f && angle[0] <= 180.0f)
	{
		angle[0] = 89.0f;
	}
	if (angle[0] > 180.f)
	{
		angle[0] -= 360.f;
	}
	if (angle[0] < -89.0f)
	{
		angle[0] = -89.0f;
	}
	if (angle[1] > 180.f)
	{
		angle[1] -= 360.f;
	}
	if (angle[1] < -180.f)
	{
		angle[1] += 360.f;
	}
	if (angle[2] != 0.0f)
	{
		angle[2] = 0.0f;
	}
}


char *BO1HitBoxes[14] = {
	"tag_eye",
	"j_neck",
	"j_spine4",
	"j_mainroot",
	"j_knee_le",
	"j_knee_ri",
	"j_ankle_le",
	"j_ankle_ri",
	"j_shoulder_le",
	"j_shoulder_ri",
	"j_elbow_le",
	"j_elbow_ri",
	"j_wrist_le",
	"j_wrist_ri"
};

char *hitBoxes[14] = {
	"tag_eye",
	"j_neck",
	"j_spine4",
	"j_mainroot",
	"j_knee_le",
	"j_knee_ri",
	"j_ankle_le",
	"j_ankle_ri",
	"j_shoulder_le",
	"j_shoulder_ri",
	"j_elbow_le",
	"j_elbow_ri",
	"j_wrist_le",
	"j_wrist_ri"
};

#define GetPointer(X) *(int*)(X)
char blr[4] = { 0x4E, 0x80, 0x00, 0x20 };
char nop[4] = { 0x60, 0x00, 0x00, 0x00 };

bool ResetAngles;
Vector3 OldAngles;

int iLagTime = 0;

float ySpin = 0;
bool ySwitch = false;

float spinAngle = 0;
float rollAngle = 0;

int ClosestPlayer = -1;
Vector3 Angles, Position, vec, FinalAngles;


/* Converting world position to an angle */
Vector3 vectoangles(Vector3 Angles)
{
	float forward;
	float yaw, pitch;
	float PI = 3.1415926535897931;
	if (Angles.x == 0 && Angles.y == 0)
	{
		yaw = 0;
		if (Angles.z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (Angles.x != -1) yaw = (float)(atan2((double)Angles.y, (double)Angles.x) * 180.00 / PI);
		else if (Angles.y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;

		forward = (float)sqrt((double)(Angles.x * Angles.x + Angles.y * Angles.y));
		pitch = (float)(atan2((double)Angles.z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	Vector3 AnglesVector(-pitch, yaw, 0);
	return AnglesVector;
}

Vector3 vectoangles2(Vector3 Angles, Vector3 Angles2)
{
	float forward;
	float yaw, pitch;
	float PI = 3.1415926535897931;
	if (Angles.x == 0 && Angles.y == 0)
	{
		yaw = 0;
		if (Angles.z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (Angles.x != -1) yaw = (float)(atan2((double)Angles.y, (double)Angles.x) * 180.00 / PI);
		else if (Angles.y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;

		forward = (float)sqrt((double)(Angles.x * Angles.x + Angles.y * Angles.y));
		pitch = (float)(atan2((double)Angles.z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	Vector3 AnglesVector(-pitch, yaw, 0);
	return AnglesVector;
}