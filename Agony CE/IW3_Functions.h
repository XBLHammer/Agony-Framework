static bool(__cdecl *Aimtarget_isTargetVisible)(int localclient, pCentity_t centity, unsigned int visBone) = (bool(__cdecl*)(int, pCentity_t, unsigned int))0x82346880;
static bool(__cdecl *CG_DObjGetWorldTagPos)(pCentity_t CEntity, int DObj, unsigned int tagID, Vector3& out) = (bool(__cdecl *)(Centity_t*, int, unsigned int, Vector3&))0x82316088;
static int(__cdecl *SL_GetStringOfSize)(const char* Text, int User, int Length, int Type) = (int(__cdecl *)(const char*, int, int, int))0x8221F268;
static void(__cdecl *R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(__cdecl*)(const char*, int, int, float, float, float, float, float, float*, int))0x8216C0B8;
static void(__cdecl*CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, int) = (void(__cdecl*)(int, float, float, float, float, float, float*, int))0x82318A88;
static void(__cdecl*R_AddCmdDrawStretchPic)(float, float, float, float, float, float, float, float, float*, int) = (void(__cdecl*)(float, float, float, float, float, float, float, float, float*, int))0x8216BAE8;
static int(__cdecl*R_TextWidth)(const char *text, int maxchars, int font) = (int(__cdecl*)(const char*, int, int))0x8216EB00;
static int(__cdecl *DB_FindXAssetHeader)(int Type, const char* Name) = (int(__cdecl *)(int, const char*))0x822A0298;
static bool(__cdecl *Dvar_GetBool)(const char* Dvar) = (bool(__cdecl *)(const char*))0x821D15D8;
static void(__cdecl*Cbuf_AddText)(int LocalClient, char* Angles) = (void(__cdecl*)(int, char*))0x82239FD0;
static void(__cdecl*CL_AddReliableCommand)(int LocalClient, char* Angles) = (void(__cdecl*)(int, char*))0x822CF268;
static const char*(__cdecl*SEH_StringEd_GetString)(const char *pszReference) = (const char*(__cdecl *)(const char *))0x821FA8A8;
static void(__cdecl*BG_GetSpreadForWeapon)(int playerState, int Weapon, float* min, float* max) = (void(__cdecl*)(int playerState, int Weapon, float* min, float* max))0x8232C478;
static void(__cdecl* FireBulletPenetrate) (int localClientNum, BulletFireParams* btr, int weaponDef, pCentity_t ent, float *tracerStart, bool drawTracer) = (void(__cdecl *)(int localClientNum, BulletFireParams* btr, int weaponDef, pCentity_t ent, float *tracerStart, bool drawTracer))0x822EC4D0;

short SL_GetString(const char* String, int usr)
{
	return SL_GetStringOfSize(String, 0, strlen(String) + 1, 8);
}

static void(__cdecl *AimTarget_GetTagPos)(pCentity_t entity, unsigned tagIndex, Vector3* pos) = (void(__cdecl *)(pCentity_t entity, unsigned tagIndex, Vector3* pos))0x823464B8;

#define clientObjMap 0x82AF3908
#define objBuf 0x82AC1900

int Com_GetClientDObj(int handle, int localClientNum)
{
	short something = *(short*)(((((((localClientNum << 3) + localClientNum) << 7) + handle)) << 1) + 0x82AF3908);
	if (!something)
		return 0;
	return ((something * 0x64) + 0x82AC1900);
}

Vector3 NullVec;
Vector3 Vec, aVec;

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

const char *GetClientName(int client) {
	char _Name[0x20];
	((void(*)(int, char*, int, int))0x822C9238)(client, _Name, 0x20, 0x26);
	return _Name;
}

int R_TextHeight(int font)
{
	return *(int*)(font + 4);
}

void UI_PlaySound(int, char *, int) {

}

int Material_RegisterHandle(const char* Material, int r4)
{
	return DB_FindXAssetHeader(0x04, Material);
}

int R_RegisterFont(const char* Font, int r4)
{
	return DB_FindXAssetHeader(0x14, Font);
}

void DrawText(const char *text, float x, float y, const char *fontName, float scale, float *color)
{
	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(fontName, 1), x, y, 1, 1, 0, color, 0);
}

void DrawShader(float x, float y, float width, float height, float *color, const char *material)
{
	int bullShit = Material_RegisterHandle(material, 0);
	R_AddCmdDrawStretchPic(x, y, width, height, 0, 0, 1, 1, color, bullShit);
}

int TextWidth(const char *text, const char *font)
{
	return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 1));
}

void SetTextCentered(const char *text, const char *font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)//"fonts/HudBigFont"
{
	const float Color[4] = { R, G, B, A };
	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(font, 0), (x - (TextWidth(text, font) / 2 * xScale)) - 1, y - 1, xScale, yScale, 0, colBLACK, 0);
	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(font, 0), (x - (TextWidth(text, font) / 2 * xScale)), y, xScale, yScale, 0, defaultText, 0);
}

void DrawLine(float X1, float Y1, float X2, float Y2, float *Colors, int  Shader, float Width)
{
	float X, Y, Angle, L1, L2, H1;
	H1 = Y2 - Y1;
	L1 = X2 - X1;
	L2 = sqrt(L1 * L1 + H1 * H1);
	X = X1 + ((L1 - L2) / 2);
	Y = Y1 + (H1 / 2);
	Angle = (float)atan(H1 / L1) * (180 / 3.14159265358979323846);

	CG_DrawRotatedPicPhysical(0xFFFFFFFF8246F308, X, Y, L2, Width, Angle, Colors, Shader);
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

int BG_GetWeaponDef(short Weapon) {
	return *(int*)(0x823B9F60 + (Weapon * 4));
}

const char *GetWeaponName(short Weapon) {
	int Struct = BG_GetWeaponDef(Weapon);
	if (Struct) {
		const char *szWeapon = SEH_StringEd_GetString((char*)(*(int*)(Struct + 0x04)));
		if (szWeapon)
			return szWeapon;
	}
	return "NONE";
}

void updatePlayerList() {

}

/*


82346880 AimTarget_IsTargetVisible
822E9D70 CG_BulletEndpos
8232C478 BG_GetSpreadForWeapon
822E8AA8 CG_GoodRandomFloat
822E9758 RandomBulletDir
82316088 CG_DObjGetWorldTagPos
822DA6C8 CL_WritePacket
822DCAE8 CL_CreateNewCommands
8221F268 SL_GetStringOfSize
8216C0B8 R_AddCmdDrawText
82318A88 CG_DrawRotatedPicPhysical
8216BAE8 R_AddCmdDrawStretchPic
82346880 AimTarget_IsTargetVisible
8235D7D0 CG_TraceCapsule
8235D638 CG_Trace
8216EB00 R_TextWidth
821FA8A8 SEH_StringEd_GetString
82239FD0 Cbuf_AddText
821D4C10 Dvar_GetInt
821D15D8 Dvar_GetBool
822A0298 DB_FindXAssetHeader

823F5054 Centity
size : 0x1D0

	823F28A0 cgArray


	int Material_RegisterHandle(const char* material)
{
	return DB_FindXAssetHeader(material, 4);
}

int R_RegisterFont(const char* font)
{
	return DB_FindXAssetHeader(material, 0x14);
}

#define _loc_translate__ 0x849B1570

const char* SEH_StringEd_GetString(const char *pszReference)
{
	int r11 = *(int*)(_loc_translate__);
	if (!r11)
		return 0;
	if (!*(char*)(r11 + 0xC))
		return 0;
	if (!pszReference[0])
		return 0;
	if (!pszReference[1])
		return 0;
	return
}

*/


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

bool WorldToScreen(Vector3 World, float *ScreenX, float *ScreenY)
{
	Vector3 Position = SubstractVector(World, cgArray_s->RefDef.viewOrigin);
	Vector3 Transform;

	Transform.x = DotProduct(Position, cgArray_s->RefDef.viewAxis[1]);
	Transform.y = DotProduct(Position, cgArray_s->RefDef.viewAxis[2]);
	Transform.z = DotProduct(Position, cgArray_s->RefDef.viewAxis[0]);

	if (Transform.z < 0.1f)
		return false;

	Vector2 Center = { cgArray_s->RefDef.Width / 2.0f, cgArray_s->RefDef.Height / 2.0f };

	*ScreenX = Center.x * (1 - (Transform.x / cgArray_s->RefDef.Fov.x / Transform.z));
	*ScreenY = Center.y * (1 - (Transform.y / cgArray_s->RefDef.Fov.y / Transform.z));

	return true;
}

void ToggleRecoil(int) {
	*(int*)0x8232B7E0 = bNoRecoil ? 0x4E800020 : 0x7D8802A6;
}

void ToggleSway(int) {
	
}

void ToggleRCS(int) {
	*(int*)0x8232B7E0 = bRCS ? 0x4E800020 : 0x7D8802A6;
}

void SetFOV(int) {
	char _fov_cmd[128];
	_snprintf(_fov_cmd, 128, "cg_fov %f", fFOV);
	Cbuf_AddText(0, _fov_cmd);
}

void addBots(int) {
	Cbuf_AddText(0, "developer 1;developer_script 1;set scr_testclients 17;fast_restart");
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

void NoWillToLive(int) {
	Cbuf_AddText(0, "kill");
}

bool IsEnemy(int c) {
	return (cgArray_s->ClientInfo[c].Team != cgArray_s->ClientInfo[cgArray_s->ClientNumber].Team) || cgArray_s->ClientInfo[c].Team == 0;
}

bool isEntityPlayer(int c) {
	return (Centity_s[c].Type == 1 && Centity_s[c].Alive && cgArray_s->ClientInfo[c].infoValid && Centity_s[c].State);
}

Vector3 GetPlayerOrigin(int c) {
	return Centity_s[c].Origin;
}

bool bBezierSeedSet;
float flBezierTime;
bool bFirstBezierSet;
Vector3 vPoint[4];
unsigned int dwBezierSeed;

void Cbuf_AddText_Va(char *szFormat, ...)
{
	va_list pArgList;
	va_start(pArgList, szFormat);
	CHAR buffer[0x1000];
	vsprintf_s(buffer, szFormat, pArgList);
	va_end(pArgList);

	((void(*)(...))0x822CF268)(0, buffer);
}

char *szGT;
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
}

void EdgeAngleByIndex(int index, float *AngleX, float *AngleY)
{
	switch (index)
	{
	default:
		if (AngleX)
			*AngleX = 0.0f;

		if (AngleY)
			*AngleY = 0.0f;
		break;

	case 0:
		if (AngleX)
			*AngleX += 30.0f;

		if (AngleY)
			*AngleY += 0.0f;
		break;

	case 1:
		if (AngleX)
			*AngleX += 30.0f;

		if (AngleY)
			*AngleY -= 30.0f;
		break;

	case 2:
		if (AngleX)
			*AngleX += 0.0f;

		if (AngleY)
			*AngleY -= 30.0f;
		break;

	case 3:
		if (AngleX)
			*AngleX -= 30.0f;

		if (AngleY)
			*AngleY -= 30.0f;
		break;

	case 4:
		if (AngleX)
			*AngleX -= 30.0f;

		if (AngleY)
			*AngleY -= 0.0f;
		break;

	case 5:
		if (AngleX)
			*AngleX -= 30.0f;

		if (AngleY)
			*AngleY += 30.0f;
		break;

	case 6:
		if (AngleX)
			*AngleX -= 0.0f;

		if (AngleY)
			*AngleY += 30.0f;
		break;

	case 7:
		if (AngleX)
			*AngleX += 30.0f;

		if (AngleY)
			*AngleY += 30.0f;
		break;
	}
}


int GetAAClient()
{
	int viableClient = -1;

	float nearestDistance = 99999999;

	for (int i = 0; i < 18; i++)
	{
		if (i == cgArray_s->ClientNumber)
			continue;

		if (!isEntityPlayer(i))
			continue;

		if (!IsEnemy(i))
			continue;

		float Distance = GetDistance(GetPlayerOrigin(cgArray_s->ClientNumber), GetPlayerOrigin(i));

		if (Distance < nearestDistance)
		{
			nearestDistance = Distance;
			viableClient = i;
		}
	}
	return viableClient;
}

void InfAmmo(int) {
	Cbuf_AddText(0, "player_sustainAmmo 1;perk_bulletPenetrationMultiplier 999;perk_bulletdamage 999;");
}

void Disconnect(int) {
	Cbuf_AddText(0, "disconnect");
}

void SetJump(int) {
	Cbuf_AddText(0, "jump_height 999;bg_fallDamageMaxHeight 9999;bg_fallDamageMinHeight 9998;");
}

void StopJump(int) {
	Cbuf_AddText(0, "reset jump_height;bg_fallDamageMaxHeight 9999;bg_fallDamageMinHeight 9998;");
}

void SetOnline(int) {
	Cbuf_AddText(0, "onlinegame 1;xblive_privatematch 0;scr_forcerankedmatch 1;");
}

void SetGod(int) {
	CL_AddReliableCommand(0, "god");
}

void SetNoclip(int) {
	CL_AddReliableCommand(0, "noclip");
}

bool CloseToMe()
{
	for (int i = 0; i < 18; i++)
	{
		if (i == cgArray_s->ClientNumber)
			continue;

		if (!isEntityPlayer(i))
			continue;

		if (!IsEnemy(i))
			continue;

		if (GetDistance(GetPlayerOrigin(i), cgArray_s->RefDef.viewOrigin) < 7.5)
			return true;
	}
	return false;
}