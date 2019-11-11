static const char*(__cdecl *Dvar_GetString)(const char* Text) = (const char*(__cdecl *)(const char*))0x82563AF0;
static bool(__cdecl*Dvar_GetBool)(const char *) = (bool(__cdecl*)(const char*))0x825639B0;
static void(__cdecl*Cbuf_AddText)(int LocalClient, char* Command) = (void(__cdecl*)(int, char*))0x8244C738;
static int(__cdecl*SL_GetString)(const char *, int usr) = (int(__cdecl*)(const char*, int))0x824934A8;
static bool(__cdecl*CG_DObjGetWorldTagPos)(Centity_t*, int, unsigned int, Vector3&) = (bool(__cdecl*)(Centity_t*, int, unsigned int, Vector3&))0x82273BC8;
static int(__cdecl*Com_GetClientDObj)(int, int) = (int(__cdecl*)(int, int))0x824723D8;
static bool(__cdecl*CG_CanSeePlayer)(int, Centity_t*, int) = (bool(__cdecl*)(int, Centity_t*, int))0x8213A168;
static int(__cdecl*R_RegisterFont)(const char *, int) = (int(__cdecl*)(const char *, int))0x8264DBF0;
static int(__cdecl*Material_RegisterHandle)(const char *, int) = (int(__cdecl*)(const char *, int))0x8265A470;
static void(__cdecl*R_AddCmdDrawStretchPic)(float, float, float, float, float, float, float, float, float*, int) = (void(__cdecl*)(float, float, float, float, float, float, float, float, float*, int))0x8266AF28;
static void(__cdecl*R_AddCmdDrawText)(const char *, int, int, float, float, float, float, float, float*, int) = (void(__cdecl*)(const char *, int, int, float, float, float, float, float, float*, int))0x8266CEB8;
static void(__cdecl*CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, int) = (void(__cdecl*)(int, float, float, float, float, float, float*, int))0x82270138;
static void(__cdecl*FireBulletPenetrate)(int localClientNum, BulletFireParams *bp, int weaponIndex, int unk, Centity_t* attacker, int unk2, float* tracerStart, bool drawTracer) = (void(__cdecl*)(int localClientNum, BulletFireParams *bp, int weaponIndex, int unk, Centity_t* attacker, int unk2, float* tracerStart, bool drawTracer))0x822C7518;
static void(__cdecl*BG_GetSpreadForWeapon)(int LocalClient, int Weapon, float* min, float* max) = (void(__cdecl*)(int LocalClient, int Weapon, float* min, float* max))0x82255C90;
static int(__cdecl*R_TextWidth)(const char *text, int maxchars, int font) = (int(__cdecl*)(const char*, int, int))0x8264DC78; 
static bool(__cdecl *Aimtarget_isTargetVisible)(int localclient, pCentity_t centity, unsigned int visBone) = (bool(__cdecl*)(int, pCentity_t, unsigned int))0x8213A168;
static int(__cdecl *R_TextHeight)(int font) = (int(__cdecl*)(int))0x8264DD70;

void xCL_GetClientName(int Client, char* OutName, int OutNameSize)
{
	((void(*)(int, int, char*, int, int))0x822E80A8)(0, Client, OutName, OutNameSize, 0x38);
}

void updatePlayerList() {

	//int Name_Var = (int)malloc(0x360);
	for (int i = 0; i < 18; i++)
	{
		//CL_GetClientName(i, (char*)(Name_Var + (0x30 * i)), 0x30);

		if (strcmp(cgArray_s->Names[i].Name, ""))
			MenuVars.Option_Text[6][i] = cgArray_s->Names[i].Name;
		else
			MenuVars.Option_Text[6][i] = "Not Connected";
	}
}

void UI_PlaySound(int, const char*, int)
{

}

void DrawText(const char *text, float x, float y, const char *fontName, float scale, float *color)
{
	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(fontName, 0), x, y, scale, scale, 0, color, 0);
}

void DrawShader(float x, float y, float width, float height, float *color, const char *material)
{
	R_AddCmdDrawStretchPic(x, y, width, height, 0, 0, 1, 1, color, Material_RegisterHandle(material, 0));
}

int TextWidth(const char *text, const char *font)
{
	return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0));
}

void SetTextCentered(const char *text, const char *font, float x, float y, float xScale, float yScale, const float R, const float G, const float B, const float A)//"fonts/normalfont"
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

	CG_DrawRotatedPicPhysical(0x82BCDD10, X, Y, L2, Width, Angle, Colors, Shader);
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

int GetWeaponDef(int Weapon)
{
	return ((int(*)(...))0x8213EDE0)(Weapon, 0, Weapon);
}

int GetWeaponShader(int Weapon)
{
	return *(int *)(*(int *)(0x82A96FD0 + ((Weapon * 4) & 0x3FC)) + 0x84);
}

const char *GetRawWeaponName(int Weapon)
{
	//int dwWeapon = GetWeaponDef(Weapon);
	//if (dwWeapon) {
	//	char *szRawName = (char *)(*(int*)(*(int*)(dwWeapon)));
	//	if (szRawName)
	//		return szRawName;
	//}
	return "NONE";
}

bool GetStructs()
{
	if (!Dvar_GetBool("cl_ingame") || ((*(int*)0x82AD56FC) == 0) || ((*(int*)0x82BAC404) == 0) || ((*(int*)0x82AD11AC) == 0)) return false;
	cgArray_s = *(cgArray_t**)(0x82AD56FC);
	ClientActive = *(ClientActive_t**)(0x82BAC404);
	Centity_s = *(pCentity_t*)0x82AD11AC;
	return true;
}

void ToggleRecoil(int)
{
	*(int*)0x822C9344 = bNoRecoil ? 0x60000000 : 0x4BF8AE4D;
}

void ToggleSway(int)
{
	*(int*)0x82103CD8 = bNoSway ? 0x60000000 : 0x4BFFEA61;
	*(int*)0x8210468C = bNoSway ? 0x60000000 : 0x4BFFFB9D;
}

void ToggleRCS(int)
{
	*(int*)0x822542B0 = bRCS ? 0x60000000 : 0x40990028;
}

bool IsEnemy(int Client)
{
	if (!strcmp(Dvar_GetString("ui_gametype"), "dm")) return true;
	return (cgArray_s->ClientInfo[Client].Team != cgArray_s->ClientInfo[cgArray_s->ClientNumber].Team);
}
Vector3 GetPlayerOrigin(int c) {
	return Centity_s[c].Origin;
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

int cg_s(int Client)
{
	int Value = *(int *)(0x82AD56FC);
	if (Value == 0)
		return 0;


	return Value;
}

int cEntity(int Client)
{
	int Value = *(int *)(0x82AD11AC);
	if (Value == 0)
		return 0;
	return (Value + (Client * 0x1EC));
}

bool isEntityPlayer(int i) {

	int Cg = cg_s(0);

	int Temp = Cg + (*(int *)(Cg + 0x17C) * 0x59C);

	if (*(int *)(Temp + 0xB9434) == 0)// is a valid client, 0x822C5EB4
		return false;

	int cEnt = cEntity(i);
	if ((*(int *)(cEnt + 0x1C4) & 1) == 0)
		return false;

	Temp = *(int *)(cEnt + 0xC8);
	if (Temp != 1 && Temp != 0x12)
		return false;

	if (*(int *)(cEnt + 0xCC) & 0x20)
		return false;

	if (!Centity_s[i].WeaponID)
		return false;

	return true;
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

void EndGame(int)
{
	char buffer[128];
	_snprintf(buffer, 128, "cmd lui 9 1 %i", *(int*)(0x82B14200));
	Cbuf_AddText(0, buffer);
}

void SetFOV(int)
{
	char _fov_cmd[128];
	_snprintf(_fov_cmd, 128, "cg_fov %f", fFOV);
	Cbuf_AddText(0, _fov_cmd);
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

char *szGT;
char *szCT;
void Cbuf_AddText_Va(char *szFormat, ...)
{
	va_list pArgList;
	va_start(pArgList, szFormat);
	CHAR buffer[0x1000];
	vsprintf_s(buffer, szFormat, pArgList);
	va_end(pArgList);

	((void(*)(...))0x8244C738)(0, buffer);
}

wchar_t wcOldGT[0x30];
void SetGT()
{
	if (!szGT) {
		szGT = cgArray_s->Names[cgArray_s->ClientNumber].Name;
	}

	if (!szCT)
		szCT = "";

	if (strcmp(szGT, "")) {
		char nameBuffer[128];
		_snprintf(nameBuffer, 128, "clanAbbrev\\%s\\name\\%s", szCT, szGT);

		Cbuf_AddText_Va("userinfo \"\\rate\\20000\\snaps\\20\\%s\\xuid\\%s\\natType\\1\rank\\1\\prestige\\0\"", nameBuffer, 0x83F0A358 + 0x30);
	}
}

void doNameThread()
{
	bool bTempFlash = bFlashName;

	bFlashName = false;

	wchar_t wcGT[0x1F];
	XOVERLAPPED XOver;
	XShowKeyboardUI(0, VKBD_HIGHLIGHT_TEXT, wcOldGT, L"Edit Gamertag", L"Please type in a gamertag to set", wcGT, 0x1E, &XOver);

	while (!XHasOverlappedIoCompleted(&XOver));

	wcscpy_s(wcOldGT, wcGT);
	wcstombs(szGT, wcGT, 0x1F);

	SetGT();

	bFlashName = bTempFlash;
}

void doSetName(int)
{
	ExCreateThread(0, 0, 0, 0, (LPTHREAD_START_ROUTINE)doNameThread, 0, 0);
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