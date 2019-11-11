
static int(__cdecl *Material_RegisterHandle)(const char *name, int imageTrack) = (int(__cdecl*)(const char*, int))0x8234E4F0;
static int(__cdecl *R_RegisterFont)(const char * name, int imageTrack) = (int(__cdecl*)(const char*, int))0x8234DC90;
static void(__cdecl *R_AddCmdDrawText)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(__cdecl*)(const char*, int, int, float, float, float, float, float, float*, int))0x82350258;
static void(__cdecl *R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int) = (void(__cdecl*)(float, float, float, float, float, float, float, float, float*, int))0x8234F998;
static bool(__cdecl *xAimtarget_isTargetVisible)(int localclient, pCentity_t centity, unsigned int visBone) = (bool(__cdecl*)(int, pCentity_t, unsigned int))0x820C5B88;
static int(__cdecl *Com_GetClientDObj)(int Client, int mask) = (int(__cdecl *)(int, int))0x8222FD58;
static bool(__cdecl *CG_DObjGetWorldTagPos)(Centity_t* CEntity, int DObj, unsigned int tagID, Vector3& out) = (bool(__cdecl *)(Centity_t*, int, unsigned int, Vector3&))0x820FB9E8;
static void(__cdecl *CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int material) = (void(__cdecl*)(int, float, float, float, float, float, float*, int))0x820F7900;
static void(__cdecl*Cbuf_AddText)(int LocalClient, char* Angles) = (void(__cdecl*)(int, char*))0x82224A28;
static bool(__cdecl *Dvar_GetBool)(const char* Dvar) = (bool(__cdecl *)(const char*))0x8229EF58;
static bool(__cdecl *Key_isDown)(int localClientNum, int Key) = (bool(__cdecl *)(int, int))0x82141308;
static int(__cdecl *SL_GetString)(const char* string, unsigned int user) = (int(__cdecl *)(const char* string, unsigned int user))0x822422D8;
static void(__cdecl *AimTarget_GetTasPos)(pCentity_t entity, unsigned tagIndex, Vector3* pos) = (void(__cdecl *)(pCentity_t entity, unsigned tagIndex, Vector3* pos))0x820C5830;
static int(__cdecl *CL_GetCurrentCmdNumber)(int LocalClientNumber) = (int(__cdecl *)(int LocalClientNumber))0x82137D48;
static char*(__cdecl* Dvar_GetString)(const char* Dvar) = (char*(__cdecl *)(const char* Dvar))0x8229F118;
static int(__cdecl *SND_PlayLocalSoundAliasByName)(int localClientNum, const char *aliasname, int system) = (int(__cdecl *)(int, const char *, int))0x8232B640;
static int(__cdecl *A_BG_GetWeaponDef)(int Weapon) = (int(__cdecl *)(int))0x820E22C0;
static int(__cdecl *BG_GetWeaponVariantDef)(int Weapon) = (int(__cdecl *)(int))0x820E22D8;
static void(__cdecl* FireBulletPenetrate) (int localClientNum, BulletFireParams* btr, int weaponID, pCentity_t ent, int minus_1_param, float *tracerStart, bool drawTracer) = (void(__cdecl *)(int localClientNum, BulletFireParams* btr, int weaponID, pCentity_t ent, int minus_1_param, float *tracerStart, bool drawTracer))0x82134648;
static void(__cdecl*BG_GetSpreadForWeapon)(cgArray_t* PlayerState, int cgArray, float* min, float* max) = (void(__cdecl*)(cgArray_t* PlayerState, int cgArray, float* min, float* max))0x820E33F0;
static void(__cdecl*CG_PlayRumbleOnClient)(int LocalClientNumber, char* rumbleName) = (void(__cdecl *)(int LocalClientNumber, char* rumbleName))0x82116458;
static int(__cdecl*R_TextWidth)(const char *text, int maxchars, int font) = (int(__cdecl*)(const char*, int, int))0x8234DD00;
static void(__cdecl*CG_LocationalTrace)(trace_t *results, Vector3 *start, Vector3 *end, int passEntityNum, int contentMask) = (void(__cdecl*)(trace_t *results, Vector3 *start, Vector3 *end, int passEntityNum, int contentMask))0x82136E88;
static void(__cdecl*cUI_PlaySound)(int context, const char *snd, int alias) = (void(__cdecl *)(int, const char *, int))0x8232B640;
static const char*(__cdecl*SEH_StringEd_GetString)(const char *pszReference) = (const char*(__cdecl *)(const char *))0x822612E8;

static const char*(__cdecl *UI_GetMapName)(const char* mapname) = (const char*(__cdecl *)(const char*))0x82272A10;
static const char*(__cdecl *UI_GetGameTypeName)(const char* mapname) = (const char*(__cdecl *)(const char*))0x82272C40;

int CSL_GetString(const char *tag, int usr) {
	//int ret = 
	//printf("SL_GetString: %s - %i\n", tag, ret);
	return SL_GetString(tag, usr);
}

void updatePlayerList() {
	for (int i = 0; i < 18; i++)
	{
		if (Dvar_GetBool("cl_ingame") && strcmp(cgArray_s->ClientInfo[i].Name, ""))
			MenuVars.Option_Text[6][i] = cgArray_s->ClientInfo[i].Name;
		else
			MenuVars.Option_Text[6][i] = "Searching...";
	}
}

typedef void(*SV_GameSendServerCommand_t)(int clientNum, int type, const char *text);
SV_GameSendServerCommand_t SV = (SV_GameSendServerCommand_t)0x82254940;
void PlaySound(int clientIndex, const char * Soundname)
{
	typedef const char * (*G_SoundAliasIndex_t)(const char *name); G_SoundAliasIndex_t G_SoundAliasIndex = (G_SoundAliasIndex_t)0x8220D048;
	char buf[50];
	const char *index = G_SoundAliasIndex(Soundname);
	sprintf(buf, "p %i", index);
	SV(clientIndex, 0, (const char *)buf);
}

void UI_PlaySound(int, const char*, int) {

}

int BG_GetWeaponDef(int WeaponID)
{
	int WeaponDef = (0x8255A320 + (WeaponID << 2));
	if (MmIsAddressValid((PVOID)WeaponDef))
		return *(int*)WeaponDef;

	return 0;
}

void DrawText(const char *text, float x, float y, const char *fontName, float scale, float *color, int Style = 0)
{
	R_AddCmdDrawText(text, 0x7FFFFFFF, !strcmp(fontName, "fonts/smallfont") ? FONT_SMALLFONT : R_RegisterFont(fontName, 1), x, y, scale, scale, 0, color, Style);
}

void DrawShader(float x, float y, float width, float height, float *color, const char *material)
{
	R_AddCmdDrawStretchPic(x, y, width, height, 0, 0, 1, 1, color, !strcmp(material, "white") ? MATERIAL_WHITE : Material_RegisterHandle(material, 3));
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

	CG_DrawRotatedPicPhysical(0x82690F48, X, Y, L2, Width, Angle, Colors, Shader);
}

void DrawSpecialText(const char *xtext, float xx, float xy, const char *xfont, float xfontSize)
{
	DrawText(xtext, xx - 1, xy - 1, xfont, xfontSize, Fade);
	DrawText(xtext, xx + 1, xy + 1, xfont, xfontSize, Fade);
	DrawText(xtext, xx, xy, xfont, xfontSize, defaultText);
}

void DrawCircle(float CenterX, float CenterY, float Radius, float *color)
{
	float theta = 0;
	float step = 2 * M_PI / 20;

	float sX = CenterX + Radius;
	float sY = CenterY;

	while (!(theta >= 360)) {
		float x = CenterX + Radius * cos(theta);
		float y = CenterY - 0.1 * Radius * sin(theta);

		DrawLine(sX, sY, x, y, color, Material_RegisterHandle("white", 0), 1);
		sX = x; sY = y;

		theta += step;
	}
}

static int(__cdecl *R_TextHeight)(int font) = (int(__cdecl*)(int))0x8234DDF0;
int TextHeight(const char* font)
{
	return R_TextHeight(R_RegisterFont(font, 0));
}

void SetTextCenteredWithBackGround(const char *text, const char* font, float x, float y, float xScale, float yScale, float *color, float *bcolor, bool bDrawShader = true)
{
	if (bDrawShader)
		DrawShader(((x - 2) - (TextWidth(text, font) / 2) * xScale), (y - (TextHeight(font) * xScale)), ((TextWidth(text, font) * xScale) + 4), TextHeight(font) * xScale, TextBackground, "white");

	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(font, 0), (x - (TextWidth(text, font) / 2) * xScale), y, xScale, yScale, 0, color, 0);
}

void SetTextWithBackground(const char *text, float x, float y, const char* font, float xScale, float *color, bool bDrawShader = true)
{
	if (bDrawShader)
		DrawShader((x - 2), (y - (TextHeight(font) * xScale)), ((TextWidth(text, font) * xScale) + 4), TextHeight(font) * xScale, TextBackground, "white");

	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(font, 0), x, y, xScale, xScale, 0, color, 0);
}

#define a_weaponVariantDef 0x82557750

int GetWeaponShader(int Weapon)
{
	int Structure = *(int *)(a_weaponVariantDef + (Weapon * 4));
	if (Structure)
		return *(int *)(Structure + 0x48);
}

const char *GetRawWeaponName(int Weapon)
{
	int dwWeapon = *(int *)(a_weaponVariantDef + (Weapon * 4));
	if (dwWeapon) {
		char *szRawName = (char *)(*(int*)(dwWeapon + 0x08));
		if (szRawName)
			return szRawName;
	}
	return "NONE";
}

const char *GetWeaponName(int Weapon)
{
	int dwWeapon = *(int *)(a_weaponVariantDef + (Weapon * 4));
	if (dwWeapon) {
		char *szRawName = (char *)(*(int*)(dwWeapon + 0x08));
		if (szRawName) {
			const char *szName = SEH_StringEd_GetString(szRawName);

			if (szName != NULL)
				return szName;
		}
	}
	return "NONE";
}

bool bStructs;

void GetStructs()
{
	if (!*(int*)0x825B8638 || !*(int*)0x82682354 || !*(int*)0x825BE150) return;
	cgArray_s = *(cgArray_t**)0x825B8638;
	Centity_s = *(pCentity_t*)0x825BE150;
	ClientActive = *(clientactive_t**)0x82682354;
	bStructs = true;
}

void pgStructs() {
	uicontext = *(UiContext*)0x83647860;
}

void ToggleRecoil(int)
{
	if (bNoRecoil)
	{
		*(int*)0x820E6594 = 0x60000000;
		*(int*)0x820E6588 = 0x60000000;
		*(int*)0x820E657C = 0x60000000;
		*(int*)0x820E6570 = 0x60000000;
		*(int*)0x82135BE0 = 0x3CBD0000;
	}
	else
	{
		*(int*)0x820E6594 = 0x3CBD0000;
		*(int*)0x820E6588 = 0x4BFFFD69;
		*(int*)0x820E657C = 0x4BFFFBC5;
		*(int*)0x820E6570 = 0x4BFFF989;
		*(int*)0x82135BE0 = 0x3CBD0007;
	}
}

bool blaser = true;
void ToggleLaser(int)
{
	if (blaser)
	{
		*(byte*)0x82104093 = 0x01;
	}
	else
	{
		*(byte*)0x82104093 = 0x00;
	}
}

DWORD dwPicState;
Detour<void> *R_DrawStretchPicDetour;
void R_DrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, void *material)
{
	const char* MatColor = *(char**)material;
	if (!strcmp(MatColor, "minimap_scanlines") ||
		!strcmp(MatColor, "hud_compass_alpha") ||
		!strcmp(MatColor, "stencil_base") ||
		!strcmp(MatColor, "stencil_fill") ||
		!strcmp(MatColor, "scanlines_stencil") ||
		!strcmp(MatColor, "ballistic_overlay") ||
		!strcmp(MatColor, "ac130_overlay_grain"))
	{
		return;
	}

	if (!strcmp(MatColor, "white") && (x == 105 || x == 254))
		return;

	if (bfademw2)
	{
		color = fclFlashMain;

		switch (dwPicState) {
		case 0:

			if (fclFlashMain[0] < 1) {
				fclFlashMain[0] += 0.0000100;
				fclFlashMain[2] -= 0.0000100;
			}
			else
				dwPicState = 1;

			break;
		case 1:
			if (fclFlashMain[1] < 1) {
				fclFlashMain[1] += 0.0000100;
				fclFlashMain[0] -= 0.0000100;
			}
			else
				dwPicState = 2;
			break;
		case 2:
			if (fclFlashMain[2] < 1) {
				fclFlashMain[2] += 0.0000100;
				fclFlashMain[1] -= 0.0000100;
			}
			else
				dwPicState = 0;
			break;
		}

		DbgPrint("Material: %s\n", *(const char**)material);
		R_DrawStretchPicDetour->CallOriginal(x, y, w, h, s0, t0, s1, t1, color, material);
	}
	else
	{
		R_DrawStretchPicDetour->CallOriginal(x, y, w, h, s0, t0, s1, t1, color, material);
	}
}

void ToggleUAV(int)
{
	if (bUAV)
	{
		*(int*)0x820EF12C = 0x3BA00001;
	}
	else
	{
		*(int*)0x820EF12C = 0x3BA00000;
	}
}


void ToggleRCS(int)
{
	*(int*)0x820E325C = bRCS ? 0x60000000 : 0x4099001C;
}

void ToggleSway(int)
{
	if (bNoSway)
	{
		*(int*)0x820E5B38 = 0x60000000;
		*(int*)0x820E657C = 0x60000000;
	}
	else
	{
		*(int*)0x820E5B38 = 0x4BFFEAA9;
		*(int*)0x820E657C = 0x4BFFFBC5;
	}
}

void*(*CG_GameMessage)(int localclient, const char* Message) = (void*(*)(int, const char*))0x821071D0;

bool IsEnemy(int ClientNumber) {
	return (!bSwitchTarget ? (IW4MP::cgArray_s->ClientInfo[IW4MP::cgArray_s->ClientNumber].Team != IW4MP::cgArray_s->ClientInfo[ClientNumber].Team) :
		(IW4MP::cgArray_s->ClientInfo[IW4MP::cgArray_s->ClientNumber].Team == IW4MP::cgArray_s->ClientInfo[ClientNumber].Team)) ||
		IW4MP::cgArray_s->ClientInfo[ClientNumber].Team == 0;
}

bool IsEnemyp(int ClientNumber) {
	return (!bSwitchTarget ? (IW4MP::cgArray_s->ClientInfo[IW4MP::cgArray_s->ClientNumber].Team != IW4MP::cgArray_s->ClientInfo[ClientNumber].Team) :
		(IW4MP::cgArray_s->ClientInfo[IW4MP::cgArray_s->ClientNumber].Team == IW4MP::cgArray_s->ClientInfo[ClientNumber].Team)) ||
		IW4MP::cgArray_s->ClientInfo[ClientNumber].Team == 0;
}


Vector3 GetPlayerOrigin(int c) {
	return IW4MP::Centity_s[c].Origin;
}

Vector3 NullVec;
Vector3 Vec, aVec;

Vector3 GetTagPos(int EntNum, const char* Tag = NULL, short sTag = NULL, bool bIsPoint = false) {
	int DObj = Com_GetClientDObj(EntNum, 0);
	if (!DObj)
		return NullVec;
	else
	{
		if (!IW4MP::CG_DObjGetWorldTagPos(&IW4MP::Centity_s[EntNum], DObj, Tag != NULL ? SL_GetString(Tag, 0) : sTag, Vec))
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

bool Aimtarget_isTargetVisible(int localClient, IW4MP::pCentity_t ent, unsigned int aimTag, Vector3 *vAimOut = NULL) {
	Vector3 Pos;

	int DObj = IW4MP::Com_GetClientDObj(ent->Handle, 0);

	if (DObj && IW4MP::CG_DObjGetWorldTagPos(ent, DObj, aimTag, Pos))
	{
		IW4MP::trace_t trace;
		IW4MP::CG_LocationalTrace(&trace, &IW4MP::cgArray_s->RefDef.viewOrigin, &Pos, IW4MP::cgArray_s->ClientNumber, 0x803003);

		if (*vAimOut)
			*vAimOut = Pos;

		return (trace.fraction > 0.945);
	}
}

Vector3 _GetTagPos(int ClientNumber, const char* Tag)
{
	Vector3 ret;
	IW4MP::AimTarget_GetTasPos(&IW4MP::Centity_s[ClientNumber], SL_GetString(Tag, 0), &ret);
	return ret;
}

bool isEntityPlayer(int i) {
	return (IW4MP::Centity_s[i].Alive & 1 && IW4MP::Centity_s[i].Type == IW4MP::ET_PLAYER && IW4MP::cgArray_s->ClientInfo[i].Valid && IW4MP::cgArray_s->ClientInfo[i].Team < 3);
}

bool WorldToScreen(Vector3 World, float *ScreenX, float *ScreenY)
{
	Vector3 Position = SubstractVector(World, IW4MP::cgArray_s->RefDef.viewOrigin);
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
	char buffer[50];
	_snprintf(buffer, sizeof(buffer), "cmd mr %i %i %s", *(int*)(0x415E0 + 0x825E2200), -1, "endround");
	Cbuf_AddText(0, buffer);
	//	XNotify(L"Game Ended :)");
}


void SetFOV(int)
{
	char _fov_cmd[128];
	_snprintf(_fov_cmd, 128, "cg_fov %f", fFOV);
	Cbuf_AddText(0, _fov_cmd);
}


void UpdateFOV()
{
	char _fov_cmd[128];
	_snprintf(_fov_cmd, 128, "cg_fov %f", fFOV);
	Cbuf_AddText(0, _fov_cmd);
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

	((void(*)(...))0x82224A28)(0, buffer);
}

typedef void(*SV_MapRestart)();
SV_MapRestart FastRestart = (SV_MapRestart)0x822015B0;

static int(__cdecl *SV_AddTestClient)() = (int(__cdecl *)())0x822546F8;
static void(__cdecl *SV_ExecuteClientCommand)(void *cl, const char *s, int clientOK, int) = (void(__cdecl *)(void *, const char *, int, int))0x822531C8;

int GetPlayerState(int ClientIndex)
{
	return(0x830CBF80 + (ClientIndex * 0x3700));
}

int Gentity_S(int ClientIndex)
{
	return (0x82F03600 + (ClientIndex * 0x280));
}

bool bProcessClient;
int addedTestClient;
void AddBotClient(int) {
	bProcessClient = true;
}

int addeclient = 0;
void _AddBot()
{
	int ent = SV_AddTestClient();
	addedTestClient = *(int*)ent;
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

void SetGT()
{
	Cbuf_AddText_Va("userinfo \"\\rate\\20000\\snaps\\20\\name\\%s\\xuid\\%s\\natType\\1\rank\\1\\prestige\\0\"", szGT, 0x838BA820 + 0x30);
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
		Cbuf_AddText_Va("userinfo \"\\rate\\20000\\snaps\\20\\name\\%s\\xuid\\%s\\natType\\1\rank\\1\\prestige\\0\"", cmd, 0x838BA820 + 0x30);
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
	Cbuf_AddText_Va("userinfo \"\\rate\\20000\\snaps\\20\\clanAbbrev\\%s\\name\\%s\\xuid\\%s\\natType\\1\rank\\1\\prestige\\0\"", ct, name, 0x838BA820 + 0x30);
}

void doSetName(int)
{
	ExCreateThread(0, 0, 0, 0, (LPTHREAD_START_ROUTINE)doNameThread, 0, 0);
}

void doCustomCmd(int)
{
	ExCreateThread(0, 0, 0, 0, (LPTHREAD_START_ROUTINE)doCmdThread, 0, 0);
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

void EdgeAngleByIndex(int index, float *AngleX, float *AngleY)
{
	switch (index)
	{
	case 0:
		if (AngleX)
			*AngleX += 20.0f;

		if (AngleY)
			*AngleY += 0.0f;
		break;

	case 1:
		if (AngleX)
			*AngleX += 0.0f;

		if (AngleY)
			*AngleY += 20.0f;
		break;


	case 2:
		if (AngleX)
			*AngleX -= 20.0f;

		if (AngleY)
			*AngleY -= 0.0f;
		break;


	case 3:
		if (AngleX)
			*AngleX -= 0.0f;

		if (AngleY)
			*AngleY -= 20.0f;
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

void PrecacheAssets() {
	//printf("[Tampered CE] Precaching assets.\n");

	MATERIAL_WHITE = Material_RegisterHandle("white", 0);
	FONT_SMALLFONT = R_RegisterFont("fonts/smallFont", 0);

	autowallBox[0] = SL_GetString("j_head", 0);
	autowallBox[1] = SL_GetString("j_knee_ri", 0);
	autowallBox[2] = SL_GetString("j_knee_le", 0);
	autowallBox[3] = SL_GetString("j_ankle_ri", 0);
	autowallBox[4] = SL_GetString("j_ankle_le", 0);
	autowallBox[5] = SL_GetString("j_spineupper", 0);
	autowallBox[6] = SL_GetString("j_spinelower", 0);
	autowallBox[7] = SL_GetString("j_ball_ri", 0);
	autowallBox[8] = SL_GetString("j_ball_le", 0);
	autowallBox[9] = SL_GetString("j_mainroot", 0);
	autowallBox[10] = SL_GetString("j_shoulder_ri", 0);
	autowallBox[11] = SL_GetString("j_shoulder_le", 0);
	autowallBox[12] = SL_GetString("j_elbow_ri", 0);
	autowallBox[13] = SL_GetString("j_elbow_le", 0);
	autowallBox[14] = SL_GetString("j_wrist_ri", 0);
	autowallBox[15] = SL_GetString("j_wrist_le", 0);
	autowallBox[16] = SL_GetString("j_hip_ri", 0);
	autowallBox[17] = SL_GetString("j_hip_le", 0);
	autowallBox[18] = SL_GetString("j_head_end", 0);
	autowallBox[19] = SL_GetString("j_clavicle_ri", 0);
	autowallBox[20] = SL_GetString("j_clavicle_le", 0);
	autowallBox[21] = SL_GetString("j_wristtwist_le", 0);
	autowallBox[22] = SL_GetString("j_wristtwist_ri", 0);

	multiBox[0] = autowallBox[0];
	multiBox[1] = autowallBox[1];
	multiBox[2] = autowallBox[2];
	multiBox[3] = autowallBox[3];
	multiBox[4] = autowallBox[4];
	multiBox[5] = autowallBox[5];
	multiBox[6] = autowallBox[6];
	multiBox[7] = autowallBox[7];
	multiBox[8] = autowallBox[8];
	multiBox[9] = autowallBox[9];
	multiBox[10] = autowallBox[10];
	multiBox[11] = autowallBox[11];
	multiBox[12] = autowallBox[12];
	multiBox[13] = autowallBox[13];
	multiBox[14] = autowallBox[14];
	multiBox[15] = autowallBox[15];
	multiBox[16] = autowallBox[16];
	multiBox[17] = autowallBox[17];
	multiBox[18] = autowallBox[18];
	multiBox[19] = autowallBox[19];
	multiBox[20] = autowallBox[20];
	multiBox[21] = autowallBox[21];
	multiBox[22] = autowallBox[22];

	bPrecached = true;

	printf("Lol. pDowns btw\n");
}

void FreezeAll(int) {
	char *Freeze = "\x01";
	Cbuf_AddText_Va(";userinfo \"\\name\\^%s^TL=BEST\\clanabbrev\\^%s^1\\xuid\\%s\";wait 10;disconnect;", Freeze, Freeze, 0x838BA820 + 0x30);
	//	XNotify(L"Froze All Players Consoles :)");
}

void PosPrediction(pCentity_t TargetEntity, Vector3 BonePos, int Scale, bool NotAllowZ)
{
	Vector3 EnemyVelocityTemp;
	Vector3 EnemyVelocity;

	VectorSubtract(TargetEntity->NewOrigin, TargetEntity->OldOrigin, EnemyVelocityTemp);

	EnemyVelocity.x = EnemyVelocityTemp[0];
	EnemyVelocity.y = EnemyVelocityTemp[1];
	EnemyVelocity.z = EnemyVelocityTemp[2];

	Vector3 CalcVec = EnemyVelocity.Normalize();

	CalcVec.x *= Scale;
	CalcVec.y *= Scale;
	CalcVec.z *= Scale;

	float TempOld = BonePos[2];

	BonePos[0] += CalcVec.x;
	BonePos[1] += CalcVec.y;
	BonePos[2] += CalcVec.z;

	if (NotAllowZ)
		BonePos[2] = TempOld;
}

bool bShieldEquipped(int i)
{
	return (strstr(cgArray_s->ClientInfo[i].WeaponModel, "riot_shield") || strstr(cgArray_s->ClientInfo[i].WeaponModel2, "riot_shield"));
}

const char* TeamNumToName(int team)
{
	if (team == 1)
		return "axis";
	if (team == 2)
		return "allies";
	else
		return "spectator";
}

static void(__cdecl*CL_AddReliableCommand)(int LocalClient, char* cmd) = (void(__cdecl*)(int, char*))0x82142BC0;

void swapTeam(int)
{
	char buf[100];
	if (cgArray_s->ClientInfo[cgArray_s->ClientNumber].Team == 2)
		sprintf(buf, "mr %i 3 %s", *(int*)(0x415E0 + 0x825E2200), TeamNumToName(1));
	else
		sprintf(buf, "mr %i 3 %s", *(int*)(0x415E0 + 0x825E2200), TeamNumToName(2));
	CL_AddReliableCommand(0, buf);
}