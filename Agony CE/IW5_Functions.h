DWORD Dvar_GetString_p = 0, Dvar_GetBool_p = 0, Cbuf_AddText_p = 0, CG_GoodRandomFloat_p = 0, BG_GetSpreadForWeapon_p = 0, CG_DrawRotatedPicPhysical_p = 0, R_AddCmdDrawStretchPic_p = 0, R_AddCmdDrawText_p = 0, Material_RegisterHandle_p = 0,
R_RegisterShader_p = 0, CG_CanSeePlayer_p = 0, CG_DObjGetWorldTagPos_p = 0, Com_GetClientDObj_p = 0, R_RegisterFont_p = 0, SL_GetString_p = 0, FireBulletPenetrate_p = 0, R_TextWidth_p = 0, CG_LocationalTrace_p = 0, R_TextHeight_p = 0, BG_GetWeaponDef_p = 0, BulletTrace_p = 0, CG_GetPlayerViewOrigin_p = 0;

static const char*(__cdecl *Dvar_GetString)(const char* Text) = (const char*(__cdecl *)(const char*))Dvar_GetString_p;
static bool(__cdecl*Dvar_GetBool)(const char *) = (bool(__cdecl*)(const char*))Dvar_GetBool_p;
static void(__cdecl*Cbuf_AddText)(int LocalClient, char* Command) = (void(__cdecl*)(int, char*))Cbuf_AddText_p;
static float(__cdecl*CG_GoodRandomFloat)(int* seed) = (float(__cdecl*)(int*))CG_GoodRandomFloat_p;
static void(__cdecl*BG_GetSpreadForWeapon)(cgArray_t* LocalClient, int Weapon, float* min, float* max) = (void(__cdecl*)(cgArray_t* LocalClient, int Weapon, float* min, float* max))BG_GetSpreadForWeapon_p;
static void(__cdecl*CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, int) = (void(__cdecl*)(int, float, float, float, float, float, float*, int))CG_DrawRotatedPicPhysical_p;
static void(__cdecl*R_AddCmdDrawStretchPic)(float, float, float, float, float, float, float, float, float*, int) = (void(__cdecl*)(float, float, float, float, float, float, float, float, float*, int))R_AddCmdDrawStretchPic_p;
static void(__cdecl*R_AddCmdDrawText)(const char *, int, int, float, float, float, float, float, float*, int) = (void(__cdecl*)(const char *, int, int, float, float, float, float, float, float*, int))R_AddCmdDrawText_p;
static int(__cdecl*Material_RegisterHandle)(const char *, int) = (int(__cdecl*)(const char *, int))Material_RegisterHandle_p;
static int(__cdecl*R_RegisterShader)(const char *, int, int, int) = (int(__cdecl*)(const char *, int, int, int))R_RegisterShader_p;
static bool(__cdecl*CG_CanSeePlayer)(int, pCentity_t, int) = (bool(__cdecl*)(int, pCentity_t, int))CG_CanSeePlayer_p;
static bool(__cdecl*CG_DObjGetWorldTagPos)(pCentity_t, int, unsigned int, Vector3&) = (bool(__cdecl*)(pCentity_t, int, unsigned int, Vector3&))CG_DObjGetWorldTagPos_p;
static int(__cdecl*Com_GetClientDObj)(int, int) = (int(__cdecl*)(int, int))Com_GetClientDObj_p;
static int(__cdecl*R_RegisterFont)(const char *, int) = (int(__cdecl*)(const char *, int))R_RegisterFont_p;
static int(__cdecl*SL_GetString)(const char *, int usr) = (int(__cdecl*)(const char*, int))SL_GetString_p;
static void(__cdecl*FireBulletPenetrate)(int LocalClient, BulletFireParams* bullet, int Weapon, int fuckKnows, pCentity_t MyCentity, int fuckKnows2, float* viewOrg, int fuckKnows3) = (void(__cdecl*)(int LocalClient, BulletFireParams* bullet, int Weapon, int fuckKnows, pCentity_t MyCentity, int fuckKnows2, float* viewOrg, int fuckKnows3))FireBulletPenetrate_p;
static int(__cdecl*R_TextWidth)(const char *text, int maxchars, int font) = (int(__cdecl*)(const char*, int, int))R_TextWidth_p;
static void(*CG_LocationalTrace)(trace_t *results, Vector3 *start, Vector3 *end, int passEntityNum, int contentMask) = (void(*)(trace_t *results, Vector3 *start, Vector3 *end, int passEntityNum, int contentMask))CG_LocationalTrace;
static int(__cdecl *R_TextHeight)(int font) = (int(__cdecl*)(int))R_TextHeight_p;
static int(__cdecl*BG_GetWeaponDef)(unsigned int weaponIndex) = (int(__cdecl*)(unsigned int))BG_GetWeaponDef_p;
static bool(__cdecl *BulletTrace)(int localClient, BulletFireParams* bulletFireParams, pCentity_t Cent, trace_t* bulletTraceResultsype, int lastSurfaceType) = (bool(__cdecl*)(int, BulletFireParams*, pCentity_t, trace_t*, int))BulletTrace_p;
static void(__cdecl *CG_GetPlayerViewOrigin)(int localClientNum, cgArray_t *cg, Vector3& origin) = (void(__cdecl*)(int, cgArray_t *cg, Vector3&))0x82159240;

void fillFunctionAddresses(BOOL ResetVars)
{
	if (ResetVars == TRUE)
	{
		Dvar_GetString_p = 0, Dvar_GetBool_p = 0, Cbuf_AddText_p = 0, CG_GoodRandomFloat_p = 0, BG_GetSpreadForWeapon_p = 0, CG_DrawRotatedPicPhysical_p = 0, R_AddCmdDrawStretchPic_p = 0, R_AddCmdDrawText_p = 0, Material_RegisterHandle_p = 0,
			R_RegisterShader_p = 0, CG_CanSeePlayer_p = 0, CG_DObjGetWorldTagPos_p = 0, Com_GetClientDObj_p = 0, R_RegisterFont_p = 0, SL_GetString_p = 0, FireBulletPenetrate_p = 0, R_TextWidth_p = 0, CG_LocationalTrace_p = 0, R_TextHeight_p = 0, BG_GetWeaponDef_p = 0,
			BulletTrace_p = 0;
	}
	else
	{
		Dvar_GetString_p = 0x8232E488;
		Dvar_GetBool_p = 0x8232E2C8;
		Cbuf_AddText_p = 0x82287F68;
		BG_GetSpreadForWeapon_p = 0x82101B08;
		CG_DrawRotatedPicPhysical_p = 0x82117668;
		R_AddCmdDrawStretchPic_p = 0x8241F100;
		R_AddCmdDrawText_p = 0x8241F9E0;
		Material_RegisterHandle_p = 0x82413F48;
		CG_CanSeePlayer_p = 0x8215D848;
		CG_DObjGetWorldTagPos_p = 0x8211BCB8;
		Com_GetClientDObj_p = 0x822A28D0;
		R_RegisterFont_p = 0x82407A90;
		SL_GetString_p = 0x822B5CC8;
		FireBulletPenetrate_p = 0x8215FB08;
		R_TextWidth_p = 0x82407B00;
		CG_LocationalTrace_p = 0x821631B8;
		R_TextHeight_p = 0x82407C80;
		BulletTrace_p = 0x82159330;
		CG_GoodRandomFloat_p = 0x820E7E20;
	}
	Dvar_GetString = (const char*(__cdecl *)(const char*))Dvar_GetString_p;
	Dvar_GetBool = (bool(__cdecl*)(const char*))Dvar_GetBool_p;
	Cbuf_AddText = (void(__cdecl*)(int, char*))Cbuf_AddText_p;
	CG_GoodRandomFloat = (float(__cdecl*)(int*))CG_GoodRandomFloat_p;
	BG_GetSpreadForWeapon = (void(__cdecl*)(cgArray_t* LocalClient, int Weapon, float* min, float* max))BG_GetSpreadForWeapon_p;
	CG_DrawRotatedPicPhysical = (void(__cdecl*)(int, float, float, float, float, float, float*, int))CG_DrawRotatedPicPhysical_p;
	R_AddCmdDrawStretchPic = (void(__cdecl*)(float, float, float, float, float, float, float, float, float*, int))R_AddCmdDrawStretchPic_p;
	R_AddCmdDrawText = (void(__cdecl*)(const char *, int, int, float, float, float, float, float, float*, int))R_AddCmdDrawText_p;
	Material_RegisterHandle = (int(__cdecl*)(const char *, int))Material_RegisterHandle_p;
	R_RegisterShader = (int(__cdecl*)(const char *, int, int, int))R_RegisterShader_p;
	CG_CanSeePlayer = (bool(__cdecl*)(int, pCentity_t, int))CG_CanSeePlayer_p;
	CG_DObjGetWorldTagPos = (bool(__cdecl*)(pCentity_t, int, unsigned int, Vector3&))CG_DObjGetWorldTagPos_p;
	Com_GetClientDObj = (int(__cdecl*)(int, int))Com_GetClientDObj_p;
	R_RegisterFont = (int(__cdecl*)(const char *, int))R_RegisterFont_p;
	SL_GetString = (int(__cdecl*)(const char*, int))SL_GetString_p;
	FireBulletPenetrate = (void(__cdecl*)(int LocalClient, BulletFireParams* bullet, int Weapon, int fuckKnows, pCentity_t MyCentity, int fuckKnows2, float* viewOrg, int fuckKnows3))FireBulletPenetrate_p;
	R_TextWidth = (int(__cdecl*)(const char*, int, int))R_TextWidth_p;
	CG_LocationalTrace = (void(*)(trace_t *results, Vector3 *start, Vector3 *end, int passEntityNum, int contentMask))CG_LocationalTrace;
	R_TextHeight = (int(__cdecl*)(int))R_TextHeight_p;
	BG_GetWeaponDef = (int(__cdecl*)(unsigned int))BG_GetWeaponDef_p;
	BulletTrace = (bool(__cdecl*)(int, BulletFireParams*, pCentity_t, trace_t*, int))BulletTrace_p;
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

void UI_PlaySound(int, const char*, int)
{

}

void DrawText(const char *text, float x, float y, const char *fontName, float scale, float *color)
{
	R_AddCmdDrawText(text, 0x7FFFFFFF, R_RegisterFont(fontName, 1), x, y, scale, scale, 0, color, 0);
}

void DrawShader(float x, float y, float width, float height, float *color, const char *material)
{
	R_AddCmdDrawStretchPic(x, y, width, height, 0, 0, 1, 1, color, Material_RegisterHandle(material, 0));
}

int TextWidth(const char *text, const char *font)
{
	return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 1));
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

	CG_DrawRotatedPicPhysical(0x827322C0, X, Y, L2, Width, Angle, Colors, Shader);
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
	return ((int(*)(int, int))0x820D5A10)(Weapon, 0);
}

int RawWeaponDef(int WeaponID)
{
	int WeaponDef = (0x825E0318 + (WeaponID << 2));
	if (MmIsAddressValid((PVOID)WeaponDef))
		return *(int*)WeaponDef;

	return 0;
}
int GetWeaponVarDef(int Weapon)
{
	return ((int(*)(int))0x820F9B98)(Weapon);
}

int GetWeaponShader(int Weapon)
{
	return *(int *)(*(int *)(0x825E0318 + ((GetWeaponDef(Weapon) * 4) & 0x3FC)) + 0x84);
}

const char *GetRawWeaponName(char Weapon)
{
	int dwWeapon = RawWeaponDef(Weapon);
	if (dwWeapon) {
		char *szRawName = (char *)(*(int*)(dwWeapon));
		if (szRawName)
			return szRawName;
	}
	return "NONE";
}


const char * GetCleanWeaponName(const char* raw)
{
	if (strstr(raw, "ump45"))
		return "UMP 45";
	else if (strstr(raw, "defaultweapon"))
		return "HAX!";
	else if (strstr(raw, "44magnum"))
		return "44 Magnum";
	else if (strstr(raw, "usp45"))
		return "USP 45";
	else if (strstr(raw, "riotshield"))
		return "Riot Shield";
	else if (strstr(raw, "deserteagle"))
		return "Desert Eagle";
	else if (strstr(raw, "mp412"))
		return "MP412";
	else if (strstr(raw, "p99"))
		return "P99";
	else if (strstr(raw, "fnfiveseven"))
		return "Five Seven";
	else if (strstr(raw, "fmg9"))
		return "FMG9";
	else if (strstr(raw, "skorpion"))
		return "Skorpion";
	else if (strstr(raw, "g18"))
		return "G18";
	else if (strstr(raw, "mp5"))
		return "MP5";
	else if (strstr(raw, "m9"))
		return "M9";
	else if (strstr(raw, "p90"))
		return "P90";
	else if (strstr(raw, "mp7"))
		return "MP7";
	else if (strstr(raw, "m16"))
		return "M16";
	else if (strstr(raw, "m4"))
		return "M4";
	else if (strstr(raw, "fad"))
		return "FAD";
	else if (strstr(raw, "type95"))
		return "Type 95";
	else if (strstr(raw, "scar"))
		return "SCAR-L";
	else if (strstr(raw, "mk14"))
		return "MK-14";
	else if (strstr(raw, "pp90m1"))
		return "PP90M1";
	else if (strstr(raw, "acr"))
		return "ACR";
	else if (strstr(raw, "ak47"))
		return "AK47";
	else if (strstr(raw, "mk46"))
		return "MK46";
	else if (strstr(raw, "mp9"))
		return "MP9";
	else if (strstr(raw, "g36c"))
		return "G36C";
	else if (strstr(raw, "cm901"))
		return "CM901";
	else if (strstr(raw, "rpg"))
		return "RPG";
	else if (strstr(raw, "smaw"))
		return "SMAW";
	else if (strstr(raw, "stinger"))
		return "Stinger";
	else if (strstr(raw, "javelin"))
		return "Javelin";
	else if (strstr(raw, "xm25"))
		return "XM25";
	else if (strstr(raw, "dragunov"))
		return "Dragunov";
	else if (strstr(raw, "msr"))
		return "MSR";
	else if (strstr(raw, "barrett"))
		return "Barrett 50. Cal";
	else if (strstr(raw, "rsass"))
		return "RSASS";
	else if (strstr(raw, "as50"))
		return "AS50";
	else if (strstr(raw, "l96a1"))
		return "L96A1";
	else if (strstr(raw, "ksg"))
		return "KSG";
	else if (strstr(raw, "1887_mp"))
		return "Model 1887";
	else if (strstr(raw, "striker"))
		return "Striker";
	else if (strstr(raw, "aa12"))
		return "AA12";
	else if (strstr(raw, "usas12"))
		return "USAS12";
	else if (strstr(raw, "spas12"))
		return "SPAS 12";
	else if (strstr(raw, "iw5_m60"))
		return "M60";
	else if (strstr(raw, "pecheneg"))
		return "Pecheneg";
	else if (strstr(raw, "sa80"))
		return "SA80";
	else if (strstr(raw, "mg36"))
		return "MG36";
	else
		return "Unknown";
}

const char *GetWeaponName(char Weapon)
{
	return GetCleanWeaponName(GetRawWeaponName(Weapon));
}

bool GetStructs()
{
	if (!Dvar_GetBool("cl_ingame") || ((*(int*)0x8263EE60) == 0) || ((*(int*)0x82713DC4) == 0) || ((*(int*)0x826436B8) == 0)) return false;
	cgArray_s = *(cgArray_t**)(0x8263EE60);
	ClientActive = *(ClientActive_t**)(0x82713DC4);
	Centity_s = *(pCentity_t*)0x826436B8;
	return true;
}

void pgStruct()
{
	uicontext = *(UiContext*)0x836E5AF8;
}

void ToggleRecoil(int)
{
	*(int*)0x82101868 = bNoRecoil ? 0x4E800020 : 0x7D8802A6;
}

void ToggleSway(int)
{
	*(int*)0x82103CD8 = bNoSway ? 0x60000000 : 0x4BFFEA61;
	*(int*)0x8210468C = bNoSway ? 0x60000000 : 0x4BFFFB9D;
}

void ToggleRCS(int)
{
	*(int*)0x82101968 = bRCS ? 0x60000000 : 0x40990028;
}

bool IsEnemy(int Client)
{
	if (!strcmp(Dvar_GetString("ui_gametype"), "dm")) return true;

	if (!bSwitchTarget)
		return (cgArray_s->ClientInfo[Client].Team != cgArray_s->ClientInfo[cgArray_s->ClientNumber].Team);
	else
		return (cgArray_s->ClientInfo[Client].Team == cgArray_s->ClientInfo[cgArray_s->ClientNumber].Team);
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

struct refdef_t // cg_s + 0x6BAAC
{
	int x;					//0x00-0x04 - 0
	int y;					//0x04-0x08 - 0
	int width;				//0x08-0x0C - 1280 0x0500
	int height;				//0x0C-0x10 - 720 0x02D0
	float tanHalfFovX;		//0x10-0x14 - 3F 59 74 0D( 0.849427f )
	float tanHalfFovY;		//0x14-0x18 - 3E F4 A2 8F( 0.4778027f )
	float vieworg[3];		//0x18-0x24 - 
	float viewaxis[3][3];	//0x24-0x48 - 
} *pRefdef;

int cg_s(int Client)
{
	int Value = *(int*)(0x8263EE60);
	if (Value == 0)
		return 0;
	Value += (Client * 0x105A80);

	pRefdef = (refdef_t*)(Value + 0x6BAAC);

	return Value;
}

bool AimTarget_GetTagPos(pCentity_t ent, int tag, Vector3& v1) {
	int var = Com_GetClientDObj(*(int*)((int)ent + 0xC4), 0);

	if (var == 0) {
		return false;
	}

	return CG_DObjGetWorldTagPos(ent, var, tag, v1);
}

/*
trace_t trace;
bool Aimtarget_isTargetVisible(int localClient, pCentity_t ent, unsigned int aimTag) {

	ZeroMemory(&trace, sizeof(trace));

	cgArray_t* cg = *(cgArray_t**)0x8263EE60;

	Vector3 tagpos;
	if (AimTarget_GetTagPos(ent, aimTag, tagpos)) {
		CG_LocationalTrace(&trace, &cgArray_s->RefDef.viewOrigin, &tagpos, cgArray_s->ClientNumber, 0x803003);
		return trace.fraction >= 0.95f;
	}
	return false;
}*/

/*
bool Aimtarget_isTargetVisible(int localClient, pCentity_t ent, unsigned int aimTag) {
Vector3 tagpos;
trace_t trace; //False errors
ZeroMemory(&trace, sizeof(trace));

cgArray_t* cg = *(cgArray_t**)0x8263EE60;

int DObj = Com_GetClientDObj(ent->Handle, 0);

if (!DObj)
return false;

if (CG_DObjGetWorldTagPos(ent, DObj, aimTag, tagpos)) {
CG_LocationalTrace(&trace, &cgArray_s->ViewAngle, &tagpos, cgArray_s->ClientNumber, 0x803003);
return trace.fraction >= 0.95f;
}
return false;
}*/

bool Aimtarget_isTargetVisible(int localClient, pCentity_t ent, unsigned int aimTag) {
	trace_t trace;

	Vector3 visVec;

	int DObj = Com_GetClientDObj(ent->Handle, 0);

	if (!DObj)
	return false;

	if (CG_DObjGetWorldTagPos(ent, DObj, aimTag, visVec)) {
		((void(*)(trace_t* result, float* start, float* end, float* NullVec, int IgnoreEntity, int ContentMask, bool, bool))0x82162FA0)
			(&trace, (float*)&cgArray_s->RefDef.viewOrigin, (float*)&visVec, (float*)0x82033B14, cgArray_s->ClientNumber, 0x803003, false, false);

	return (trace.fraction > 0.95f);
	}
	return false;
}

bool isEntityPlayer(int i) {
	return ((Centity_s[i].Type == 1) && (Centity_s[i].Alive & 1) && strcmp(cgArray_s->ClientInfo[i].HeadModel, ""));
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

void Jug(int)
{
	char CmdArr[512];
	_snprintf(CmdArr, 512, "mr %d 10 axis", *(int*)(0x82676C00 + 0x415E8));
	Cbuf_AddText(0, CmdArr);
}

void swapTeams(int)
{
	char buf[100];
	sprintf(buf, "cmd mr %i 3 %s", *(int*)(0x82676C00 + 0x415E8), (cgArray_s->ClientInfo[cgArray_s->ClientNumber].Team == Axis || cgArray_s->ClientInfo[cgArray_s->ClientNumber].Team == Spectator) ? "allies" : "axis");
	Cbuf_AddText(0, buf);
}

void EndGame(int)
{
	char buffer[50];
	_snprintf(buffer, sizeof(buffer), "cmd mr %i %i %s", *(int*)(0x82676C00 + 0x415E8), 3, "endround");
	Cbuf_AddText(0, buffer);
}

void setClass(int)
{
	char buff[30];
	_snprintf(buff, 30, "cmd mr %i 10 custom1", *(int*)(0x82676C00 + 0x415E8));
	Cbuf_AddText(0, buff);
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

	((void(*)(...))0x82287EE0)(0, buffer);
}

void SetGT()
{
	Cbuf_AddText_Va("userinfo \"\\rate\\20000\\snaps\\20\\name\\%s\\xuid\\%s\\natType\\1\rank\\1\\prestige\\0\"", szGT, 0x839691A8 + 0x30);
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
		Cbuf_AddText_Va("userinfo \"\\rate\\20000\\snaps\\20\\name\\%s\\xuid\\%s\\natType\\1\rank\\1\\prestige\\0\"", cmd, 0x839691A8 + 0x30);
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
	Cbuf_AddText_Va("userinfo \"\\rate\\20000\\snaps\\20\\clanAbbrev\\%s\\name\\%s\\xuid\\%s\\natType\\1\rank\\1\\prestige\\0\"", ct, name, 0x839691A8 + 0x30);
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