static bool(__cdecl *Aimtarget_isTargetVisible)(int localclient, pCentity_t centity, unsigned int visBone) = (bool(__cdecl*)(int, pCentity_t, unsigned int))0x82125E70;
static bool(__cdecl *Dvar_GetBool)(const char* Dvar) = (bool(__cdecl *)(const char*))0x822BE0E8;
static int(__cdecl *Com_Error)(int, const char* Dvar) = (int(__cdecl *)(int, const char*))0x82272068;
static void(__cdecl *R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(__cdecl*)(const char*, int, int, float, float, float, float, float, float*, int))0x82401C30;
static void(__cdecl *R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int) = (void(__cdecl*)(float, float, float, float, float, float, float, float, float*, int))0x82401410;
static int(__cdecl *Material_RegisterHandle)(const char *name, int imageTrack) = (int(__cdecl*)(const char*, int))0x824006F0;
static int(__cdecl *R_RegisterFont)(const char * name, int imageTrack) = (int(__cdecl*)(const char*, int))0x823FFEE0;
static int(__cdecl *rSL_GetString)(const char* string, int, int) = (int(__cdecl *)(const char* string, int, int))0x8233B7A0;
static int(__cdecl *Com_GetClientDObj)(int handle, int localClientNum) = (int(__cdecl*)(int, int))0x822758E8;
static bool(__cdecl *CG_DObjGetWorldTagPos)(pCentity_t Centity, int dobj, unsigned int target, Vector3& pos) = (bool(__cdecl*)(pCentity_t, int, unsigned int, Vector3&))0x82161EA8;
static char*(__cdecl *Dvar_GetString)(const char* Dvar) = (char*(__cdecl *)(const char*))0x822BE230;
static int(__cdecl *Cbuf_AddText)(int LocalClientNumber, const char* Command) = (int(__cdecl *)(int LocalClientNumber, const char* Command))0x8226FF08;
static void(__cdecl *CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int material) = (void(__cdecl*)(int, float, float, float, float, float, float*, int))0x8215CEC0;
static void(__cdecl*BG_GetSpreadForWeapon)(playerState_t* PlayerState, int WeaponDef, float* min, float* max) = (void(__cdecl*)(playerState_t* PlayerState, int WeaponDef, float* min, float* max))0x82141650;
static void(__cdecl *CG_BulletEndPos)(int randSeed, const float spread, Vector3 *start, Vector3 *end, Vector3 *dir, Vector3 *forwardDir, Vector3 *rightDir, Vector3 *upDir, const float maxRange) = (void(__cdecl*)(int, const float, Vector3*, Vector3 *, Vector3 *, Vector3 *, Vector3 *, Vector3 *, const float))0x8219BB90;
static float(__cdecl *CG_GoodRandomFloat)(int* Dvar) = (float(__cdecl *)(int*))0x822046D0;
static void(__cdecl *CG_LocationalTrace)(trace_t* trace, Vector3* start, Vector3* end, int ignoreindex, int mask) = (void(__cdecl*)(trace_t*, Vector3*, Vector3*, int, int))0x821A2C58;

static int(__cdecl *R_TextWidth)(const char* text, int maxchars, int font) = (int(__cdecl*)(const char*, int, int))0x823FFF28;
static int(__cdecl *R_TextHeight)(int font) = (int(__cdecl*)(int))0x82400018;

int BG_GetWeaponDef(int WeaponID)
{
	return *(int*)(0x824C6CF8 + (WeaponID << 2));
}

void DrawLine(float X1, float Y1, float X2, float Y2, float* Colors, int  Shader, float Width)
{
	float X, Y, Angle, L1, L2, H1;
	H1 = Y2 - Y1;
	L1 = X2 - X1;
	L2 = sqrt(L1 * L1 + H1 * H1);
	X = X1 + ((L1 - L2) / 2);
	Y = Y1 + (H1 / 2);
	Angle = (float)atan(H1 / L1) * (180 / 3.14159265358979323846);
	CG_DrawRotatedPicPhysical(0xFFFFFFFF8274F580, X, Y, L2, Width, Angle, Colors, Shader);
}

void DrawText(const char *text, float x, float y, const char *fontName, float scale, float* color)
{
	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(fontName, 0), x, y, scale, scale, 0, color, 0);
}

void DrawShader(float x, float y, float width, float height, float* color, const char *material)
{
	R_AddCmdDrawStretchPic(x, y, width, height, 0, 0, 1, 1, color, Material_RegisterHandle(material, 0));
}

int TextWidth(const char *text, const char *font)
{
	return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0));
}

int TextHeight(const char* font)
{
	return R_TextHeight(R_RegisterFont(font, 0));
}

void SetTextCenteredWithBackGround(const char *text, const char* font, float x, float y, float xScale, float yScale, float *color, float *bcolor, bool bDrawShader = true)
{
	if (bDrawShader)
		DrawShader(((x - 2) - (TextWidth(text, font) / 2) * xScale), (y - (TextHeight(font) * xScale)), ((TextWidth(text, font) * xScale) + 4), TextHeight(font) * xScale, bcolor, "white");
	
	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(font, 0), (x - (TextWidth(text, font) / 2) * xScale), y, xScale, yScale, 0, color, 0);
}

int SL_GetString(const char *string, int) {
	return rSL_GetString(string, 0, 0);
}

void updatePlayerList() {
	for (int i = 0; i < 18; i++)
	{
		if (Dvar_GetBool("cl_ingame") && strcmp(cgArray_s->ClientInfo[i].Name, ""))
			MenuVars.Option_Text[6][i] = cgArray_s->ClientInfo[i].Name;
		else
			MenuVars.Option_Text[6][i] = "Not Connected";
	}
}

void UI_PlaySound(int, char*, int) {

}

Vector3 GetPlayerOrigin(int c) {
	return Centity_s[c].Origin;
}

bool WorldToScreen(Vector3 World, float *ScreenX, float *ScreenY)
{
	Vector3 Position = SubstractVector(World, cgArray_s->RefDef.viewOrigin);
	Vector3 Transform;

	Transform.x = DotProduct(Position, cgArray_s->RefDef.viewAxis[1]);
	Transform.y = DotProduct(Position, cgArray_s->RefDef.viewAxis[2]);
	Transform.z = DotProduct(Position, cgArray_s->RefDef.viewAxis[0]);

	if (Transform.z < 0.1f)
		return false;

	Vector2 Center = { cgArray_s->RefDef.Width / 2, cgArray_s->RefDef.Height / 2 };

	*ScreenX = Center.x * (1 - (Transform.x / cgArray_s->RefDef.Fov.x / Transform.z));
	*ScreenY = Center.y * (1 - (Transform.y / cgArray_s->RefDef.Fov.y / Transform.z));

	return true;
}

bool IsEnemy(int ClientNumber)
{
	return (cgArray_s->ClientInfo[cgArray_s->ClientNumber].Team != cgArray_s->ClientInfo[ClientNumber].Team) || cgArray_s->ClientInfo[ClientNumber].Team == 0;
}

void SetFOV(int)
{
	char _fov_cmd[128];
	_snprintf(_fov_cmd, 128, "cg_fov %f", fFOV);
	Cbuf_AddText(0, _fov_cmd);
}

void ToggleRecoil(int) {
	*(int*)0x821A0BFC = 0x60000000;
}

void ToggleSway(int) {
	*(int*)0x8214789C = 0x60000000;//0x8214789C - Weapon Sway
	*(int*)0x8214804C = 0x60000000;//0x8214804C- ADS Sway
}

void ToggleRCS(int) {

}

bool isEntityPlayer(int c) {
	return (Centity_s[c].isAlive == 0x40000000 && Centity_s[c].Valid);
}

Vector3 Vec, aVec;
Vector3 NullVec;

Vector3 GetTagPos(int EntNum, const char* Tag, bool bIsPoint = false) {
	int DObj = Com_GetClientDObj(EntNum, 0);
	if (!DObj)
		return NullVec;
	else
	{
		if (!CG_DObjGetWorldTagPos(&Centity_s[EntNum], DObj, SL_GetString(Tag, 0), Vec))
			printf("GetTagPos Couldnt find Tag [%s] on entity [%i]\n", Tag, EntNum);
		else {
			if (bPointCorrection && bIsPoint) {
				aVec = Vector3(Vec.x, Vec.y, Vec.z + 7);
				return Vec + ((aVec - Vec) / fPCorrection);
			}
			else
				return Vec;
		}
	}
}

void GetStructs()
{
	Centity_s = *(pCentity_t*)0x8268FC30;
	ClientActive = *(ClientActive_t**)0x826E8BD8;
	cgArray_s = *(cgArray_t**)0x8268CD98;
}

void pgStructs() {
	uicontext = *(UiContext*)0x84FAA578;
}

char ClampChar_r(const int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

float DEG2RAD(float DEG)
{
	return ((DEG * M_PI) / 180);
}

void FixMovement(Usercmd_t* pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove)
{
	float deltaView = CurAngle - OldAngle, f1, f2;

	if (OldAngle < 0.f)
		f1 = 360.0f + OldAngle;
	else
		f1 = OldAngle;

	if (CurAngle < 0.0f)
		f2 = 360.0f + CurAngle;
	else
		f2 = CurAngle;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);
	deltaView = 360.0f - deltaView;

	pCmd->fDir = ClampChar_r((int)(cosf(DEG2RAD(deltaView)) * fOldForward + cosf(DEG2RAD(deltaView + 90.f)) * fOldSidemove));
	pCmd->rDir = ClampChar_r((int)(sinf(DEG2RAD(deltaView)) * fOldForward + sinf(DEG2RAD(deltaView + 90.f)) * fOldSidemove));
}



bool bFrameLoop, bCycle, bRainbow;

DWORD dwGTTick;
DWORD dwGTIndex;

wchar_t wcOldGT[0x30];

char *szGT;
char *szCT;

void Cbuf_AddText_Va(char *szFormat, ...)
{
	va_list pArgList;
	va_start(pArgList, szFormat);
	CHAR buffer[0x1000];
	vsprintf_s(buffer, szFormat, pArgList);
	va_end(pArgList);

	((void(*)(...))0x8226FF08)(0, buffer);
}

void SetGT()
{
	Cbuf_AddText_Va("userinfo \"\\name\\%s\"", szGT);
}

const char* ReturnXShowKeyboardUI(LPCWSTR wseDefaultText, LPCWSTR wszTitleText, LPCWSTR wszDescriptionText, DWORD Length, int& err)
{
	XOVERLAPPED Overlapped;
	WCHAR KeyboardText[0x200];
	char Return[0x100];
	ZeroMemory(&Overlapped, sizeof(Overlapped));
	XShowKeyboardUI(0, 0, wseDefaultText, wszTitleText, wszDescriptionText, KeyboardText, Length, &Overlapped);


	while (!XHasOverlappedIoCompleted(&Overlapped))
		Sleep(50);
	err = Overlapped.dwExtendedError;
	wcstombs(Return, KeyboardText, Length);
	return Return;
}

void doNameThread()
{
	int error;
	const char *cmd = ReturnXShowKeyboardUI(L"", L"Change Name", L"Enter a new name", 0x20, error);

	if (error == 0) {
		Cbuf_AddText_Va("userinfo \"\\name\\%s\"", cmd);
	}
}

void doCmdThread()
{
	int error;
	const char *cmd = ReturnXShowKeyboardUI(L"", L"Custom Command", L"Enter a command", 0x20, error);

	if (error == 0) {
		Cbuf_AddText_Va("%s", cmd);
	}
}

void customName(const char *ct, const char *name) {
	Cbuf_AddText_Va("userinfo \"\\clanAbbrev\\%s\\name\\%s\"", ct, name);
}

void doSetName(int)
{
	ExCreateThread(0, 0, 0, 0, (LPTHREAD_START_ROUTINE)doNameThread, 0, 0);
}

void doCustomCmd(int)
{
	ExCreateThread(0, 0, 0, 0, (LPTHREAD_START_ROUTINE)doCmdThread, 0, 0);
}

void God(int) {
	Cbuf_AddText(0, "god");
}

void Noclip(int) {
	Cbuf_AddText(0, "noclip");
}

void GiveAll(int) {
	Cbuf_AddText(0, "give all");
}

void InfAmmo(int) {
	Cbuf_AddText(0, "player_sustainAmmo 1;");
}

void addBots(int) {
	Cbuf_AddText(0, "developer 1;developer_script 1;set scr_testclients 17;fast_restart");
}

void SuperUser(int) {
	Cbuf_AddText(0, "set developeruser 1;set superuser 1;");
}

static const char*(__cdecl *SEH_StringEd_GetString)(const char* str) = (const char*(__cdecl*)(const char*))0x82292BF8;
const char *GetWeaponName(int Weapon)
{
	int dwWeapon = *(int *)(0x824C6CF8 + (Weapon * 4));
	if (dwWeapon) {
		char *szRawName = (char *)(*(int*)(dwWeapon + 0x4));
		if (szRawName) {
			const char *szName = SEH_StringEd_GetString(szRawName);

			if (szName != NULL)
				return szName;
		}
	}
	return "NONE";
}

void flNormalize(float *x) {
	while (!(*x > -180 && *x < 180))
	{
		if (*x > 180)  *x -= 360;
		if (*x < -180) *x += 360;
	}
}

#define Point Vector3

namespace Bezier
{
	Point Lerp(const Point& a, const Point& b, const float t) {
		Point result;
		result.x = a.x + (b.x - a.x)*t;
		result.y = a.y + (b.y - a.y)*t;
		return result;
	}

	Point CubicBezier(const Point& a, const Point& b, const Point& c, const Point& d, const float t) {
		Point ab, bc, cd, abbc, bccd;
		Point result;

		ab = Lerp(a, b, t);
		bc = Lerp(b, c, t);
		cd = Lerp(c, d, t);
		abbc = Lerp(ab, bc, t);
		bccd = Lerp(bc, cd, t);

		result = Lerp(abbc, bccd, t);
		return result;
	}
}

bool bTriggerShoot;

void _Triggerbot()
{
	int i = ClosestPlayer;

	if (i == -1)
		return;

	Vector3 FeetOrigin = GetPlayerOrigin(i);
	Vector3 HeadOrigin = GetTagPos(i, "j_head");
	FeetOrigin.z -= 5;
	HeadOrigin.z += 10;
	Vector2 FeetLocation, HeadLocation;
	if (WorldToScreen(FeetOrigin, &FeetLocation.x, &FeetLocation.y) &&
		WorldToScreen(HeadOrigin, &HeadLocation.x, &HeadLocation.y))
	{
		float fHeight = FeetLocation.y - HeadLocation.y;
		float fWidth = fHeight / fTriggerSeed;
		Vector2 ScreenPos;

		for (int b = 0; b < 14; b++)
		{
			Vector2 bScreenPos;
			if (WorldToScreen(GetTagPos(i, hitBoxes[b]), &bScreenPos.x, &bScreenPos.y))
			{
				// DrawShader(bScreenPos.x - ((fWidth / 5) / 2), bScreenPos.y - ((fWidth / 5) / 2), (fWidth / 5), (fWidth / 5), colWHITE, "white");

				if (bScreenPos.x - ((fWidth / 5) / 2) < (cgArray_s->RefDef.Width / 2) &&
					bScreenPos.x + ((fWidth / 5) / 2) > (cgArray_s->RefDef.Width / 2) &&
					bScreenPos.y - ((fWidth / 5) / 2) < (cgArray_s->RefDef.Height / 2) &&
					bScreenPos.y + ((fWidth / 5) / 2) > (cgArray_s->RefDef.Height / 2))
					bTriggerShoot = true;
			}
		}
	}
}

float GetAngle(float e, float s) {
	if (e - s < 0)
		return -(e - s);
	return (e - s);
}

unsigned int dwBezierSeed;

float RandomFloat(float min, float max)
{
	// this  function assumes max > min, you may want 
	// more robust error checking for a non-debug build
	//assert(max > min);
	srand(dwBezierSeed);
	float random = ((float)rand()) / (float)RAND_MAX;

	// generate (in your case) a float between 0 and (4.5-.78)
	// then add .78, giving you a float between .78 and 4.5
	float range = max - min;
	return (random*range) + min;
}

float FloatMinMax(float min, float max)
{
	// this  function assumes max > min, you may want 
	// more robust error checking for a non-debug build
	//assert(max > min);
	float random = ((float)rand()) / (float)RAND_MAX;

	// generate (in your case) a float between 0 and (4.5-.78)
	// then add .78, giving you a float between .78 and 4.5
	float range = max - min;
	return (random*range) + min;
}

float flBezierTime;
bool bFirstBezierSet;
Vector3 vPoint[4];

void _SmoothAngle(Vector3 End, Vector3 Start, float Speed)
{
	if (!bFirstBezierSet)
	{
		flBezierTime = 0.0f;

		if (!bFirstBezierSet)
			bFirstBezierSet = true;
	}

	if (flBezierTime <= 1.0f)
		flBezierTime += ((fAimSpeed * 2) * 0.001);

	vPoint[0].x = Start.y;
	vPoint[0].y = Start.x;

	flNormalize(&vPoint[0].x);
	flNormalize(&vPoint[0].y);

	vPoint[3].x = End.y;
	vPoint[3].y = End.x;

	flNormalize(&vPoint[3].x);
	flNormalize(&vPoint[3].y);

	vPoint[1].x = RandomFloat(vPoint[0].x, vPoint[3].x);
	vPoint[1].y = RandomFloat(vPoint[0].y + (vPoint[3].y - vPoint[0].y) - fAimCurve, vPoint[0].y + (vPoint[3].y - vPoint[0].y) + fAimCurve);

	flNormalize(&vPoint[1].x);
	flNormalize(&vPoint[1].y);

	vPoint[2].x = RandomFloat(vPoint[1].x, vPoint[3].x);
	vPoint[2].y = RandomFloat(vPoint[0].y + (vPoint[3].y - vPoint[0].y) - fAimCurve, vPoint[0].y + (vPoint[3].y - vPoint[0].y) + fAimCurve);

	flNormalize(&vPoint[2].x);
	flNormalize(&vPoint[2].y);

	Vector3 vCur = Bezier::CubicBezier(vPoint[0], vPoint[1], vPoint[2], vPoint[3], flBezierTime);

	flNormalize(&vCur.x);
	flNormalize(&vCur.y);

	ClientActive->viewAngle.x = vCur.y;
	ClientActive->viewAngle.y = vCur.x;

	/*
	if (GetAngle(End.x, Start.x) > 3.5f)
	End.x += RandomFloat(3.0f, -3.0f);

	if (GetAngle(End.y, Start.y) > 3.5f)
	End.y += RandomFloat(3.0f, -3.0f);

	Vector3 Delta = End - Start;

	flNormalize(&Delta.x);
	flNormalize(&Delta.y);

	Vector3 Final = (Start + (Delta / Speed));

	flNormalize(&Final.x);
	flNormalize(&Final.y);

	ClientActive->viewAngle = Final;
	*/
}

void menuLeft(int)
{
	while (GetAsyncKeyState(XINPUT_GAMEPAD_A))
		flMenuX -= 0.0012;
}

void menuRight(int)
{
	while (GetAsyncKeyState(XINPUT_GAMEPAD_A))
		flMenuX += 0.0012;
}
void menuUp(int)
{
	while (GetAsyncKeyState(XINPUT_GAMEPAD_A))
		flMenuY -= 0.0012;
}

void menuDown(int)
{
	while (GetAsyncKeyState(XINPUT_GAMEPAD_A))
		flMenuY += 0.0012;
}
