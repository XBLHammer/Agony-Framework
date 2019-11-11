static int(*rMaterial_RegisterHandle)(const char *name, int imageTrack, bool errorIfMissing, int waitTime) = (int(__cdecl*)(const char*, int, bool, int))0x828B78F0;
static int(*R_RegisterFont)(const char * name, int imageTrack) = (int(__cdecl*)(const char*, int))0x82275F78;
static void(__cdecl *R_AddCmdDrawTextInternal)(const char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) = (void(__cdecl*)(const char*, int, int, float, float, float, float, float, float*, int))0x828B8BA0;
static void(__cdecl *R_AddCmdDrawStretchPicInternal)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, int) = (void(__cdecl*)(float, float, float, float, float, float, float, float, float*, int))0x828B86C0;
static bool(__cdecl *Dvar_GetBool_f)(dvar_t* Dvar) = (bool(__cdecl *)(dvar_t*))0x824964C0;
static void(__cdecl *CG_DrawRotatedPicPhysical)(int ScreenPlacement, float x, float y, float width, float height, float angle, float* color, int material) = (void(__cdecl*)(int, float, float, float, float, float, float*, int))0x821C7F58;
static bool(__cdecl *AimTarget_GetTasPos)(pCentity_t targ_centity, unsigned tagIndex, Vector3& pos) = (bool(__cdecl *)(pCentity_t, unsigned, Vector3&))0x821E9C08;
static int(__cdecl *SL_GetString)(const char* Text, int) = (int(__cdecl *)(const char*, int))0x82533528;
static dvar_t*(__cdecl *Dvar_FindMalleableVar)(const char* LocalClient) = (dvar_t*(__cdecl *)(const char*))0x82496430;
static bool(__cdecl *CG_IsEntityFriendlyNotEnemy)(int LocalClient, pCentity_t Centity) = (bool(__cdecl *)(int, pCentity_t))0x821CD948;
static bool(__cdecl *WorldPosToScreenPos)(int localClientNum, Vector3 *worldPos, Vector2 *outScreenPos) = (bool(__cdecl*)(int localClientNum, Vector3 *worldPos, Vector2 *outScreenPos))0x821DA808;
static bool(__cdecl *AimTarget_isTargetVisible_)(int LocalClient, pCentity_t Centity) = (bool(__cdecl*)(int, pCentity_t))0x821A2B68;
static bool(__cdecl *Key_isDown)(int localClientNum, int Key) = (bool(__cdecl *)(int, int))0x824964C0;
static void(__cdecl*Cbuf_AddText)(int LocalClient, char* Angles) = (void(__cdecl*)(int, char*))0x824015E0;
static void(__cdecl *BG_GetSpeadForWeapon)(playerState_s* ps, int weapon, float* minSpread, float* maxSpread) = (void(__cdecl *)(playerState_s*, int, float*, float*))0x826BB4E0;
static void(__cdecl *CG_SimulateBulletFire_Internal)(int localClientNum, BulletFireParams* bp, int weaponIndex, pCentity_t attacker, float* Coords, int drawTracer, int isPlayer, BulletTraceResults* br) = (void(__cdecl *)(int, BulletFireParams*, int, pCentity_t, float*, int, int, BulletTraceResults*))0x82258840;
static int(__cdecl*BG_GetWeaponDef)(int Weapon) = (int(__cdecl *)(int))0x826BF988;
static int(__cdecl*CScr_PlayFXInternal)(int LocalCClient, int fxid, Vector3* Angle, Vector3* Origin, int time, float fracation, int lighting) = (int(__cdecl *)(int LocalClient, int fxid, Vector3* Angle, Vector3* Origin, int time, float fracation, int lighting))0x8220EC90;
static void(__cdecl*CG_PlayRumbleOnClient)(int LocalClientNumber, char* rumbleName) = (void(__cdecl *)(int LocalClientNumber, char* rumbleName))0x82201C18;
static void(__cdecl*CL_ConsolePrint)(int LocalClientNumber, int type, char* text, int duration, int r7, int r8) = (void(__cdecl *)(int LocalClientNumber, int type, char* text, int duration, int r7, int r8))0x8226AE80;
static int(__cdecl*R_TextWidth)(int, const char *text, int maxchars, int font) = (int(__cdecl*)(int, const char*, int, int))0x828B6FD8;
static int(__cdecl *R_TextHeight)(int font) = (int(__cdecl*)(int))0x82490390;

void UI_PlaySound(int, char*, int) {

}

int Material_RegisterHandle(const char *name, int imgTrack) {
	return rMaterial_RegisterHandle(name, imgTrack, false, 0);
}

bool Dvar_GetBool(const char *dvarName)
{
	if (((*(int*)0x82BBC554) == 0) || ((*(int*)0x82C70F4C) == 0) || ((*(int*)0x82BBAE68) == 0)) return false;
	return (Dvar_GetBool_f(Dvar_FindMalleableVar(dvarName)));
}

void updatePlayerList() {
	for (int i = 0; i < 18; i++)
	{
		if (strcmp(cgArray_s->ClientInfo[i].Name, ""))
			MenuVars.Option_Text[6][i] = cgArray_s->ClientInfo[i].Name;
		else
			MenuVars.Option_Text[6][i] = "Not Connected";
	}
}

void DrawText(const char *text, float x, float y, const char *fontName, float scale, float* color)
{
	R_AddCmdDrawTextInternal(text, 0x7FFFFFFF, R_RegisterFont(fontName, 1), x, y, scale, scale, 0, color, 0);
}

void DrawShader(float x, float y, float width, float height, float* color, const char *material)
{
	R_AddCmdDrawStretchPicInternal(x, y, width, height, 0, 0, 1, 1, color, Material_RegisterHandle(material, 0));
}

int TextWidth(const char *text, const char *font)
{
	return R_TextWidth(0, text, 0x7FFFFFFF, R_RegisterFont(font, 0));
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
	CG_DrawRotatedPicPhysical(0x82CBC168, X, Y, L2, Width, Angle, Colors, Shader);
}

int TextHeight(const char* font)
{
	return R_TextHeight(R_RegisterFont(font, 0));
}


void SetTextCenteredWithBackGround(const char *text, const char* font, float x, float y, float xScale, float yScale, float *color, float *bcolor, bool bDrawShader = true)
{
	if (bDrawShader)
		DrawShader(((x - 2) - (TextWidth(text, font) / 2) * xScale), (y - (TextHeight(font) * xScale)), ((TextWidth(text, font) * xScale) + 4), TextHeight(font) * xScale, bcolor, "white");

	R_AddCmdDrawTextInternal(text, 0x7FFFFFFF, R_RegisterFont(font, 0), (x - (TextWidth(text, font) / 2) * xScale), y, xScale, yScale, 0, color, 0);
}


int GetWeaponShader(int Weapon)
{
	return *(int *)(*(int *)(*(int *)(0x845CA998 + ((Weapon * 4) & 0x3FC)) + 0x08) + 0x660);
}

bool GetStructs()
{
	if (!*(int*)0x82BBC554 || !*(int*)0x82C70F4C || !*(int*)0x82BBAE68) return false;
	Centity_s = *(pCentity_t*)0x82BBC554;
	cgArray_s = *(cgArray_t**)0x82BBAE68;
	ClientActive = *(ClientActive_t**)0x82C70F4C;
	return true;
}

void ToggleRCS(int)
{
	*(int*)0x8223AC00 = bRCS ? 0x60000000 : 0x4800000C;
}

void ToggleRecoil(int)
{
	*(int*)0x82259BC8 = bNoRecoil ? 0x38600001 : 0x48461341;
	*(int*)0x826C7A64 = bNoRecoil ? 0x60000000 : 0x4BFFF95D;
	*(int*)0x8223FE80 = bNoRecoil ? 0x60000000 : 0x4BFFAC41;
}

void ToggleSway(int)
{
	*(int*)0x826C6E6C = bNoSway ? 0x60000000 : 0x4BFFE975;
	*(int*)0x826C7A7C = bNoSway ? 0x60000000 : 0x4BFFFA85;
}

bool IsEnemy(int ClientNumber)
{
	return (!CG_IsEntityFriendlyNotEnemy(0, &Centity_s[ClientNumber]));
}

Vector3 GetPlayerOrigin(int c) {
	return Centity_s[c].Origin;
}

Vector3 NullVec;
Vector3 Vec, aVec;

Vector3 GetTagPos(int EntNum, const char* Tag, bool bIsPoint = false) {
	AimTarget_GetTasPos(&Centity_s[EntNum], SL_GetString(Tag, 0), Vec);
	if (bPointCorrection && bIsPoint) {
		aVec = Vector3(Vec.x, Vec.y, Vec.z + 7);
		return Vec + ((aVec - Vec) / fPCorrection);
	}
	else
		return Vec;
}

static void(__cdecl *CG_LocationalTrace)(trace_t *results, Vector3 start, Vector3 end, int passEntityNum, int contMask, int u1, int u2) = (void(__cdecl*)(trace_t *results, Vector3 start, Vector3 end, int passEntityNum, int contMask, int u1, int u2))0x8225C568;

bool Aimtarget_isTargetVisible(int c, pCentity_t cent, unsigned int ataga) {
	Vector3 ret;
	if (!AimTarget_GetTasPos(&Centity_s[cent->ClientNumber], ataga, ret)) return false;

	trace_t trace;

	CG_LocationalTrace(&trace, cgArray_s->RefDef.viewOrigin, ret, cgArray_s->ClientNumber, 0x803003, 1, 0);

	return trace.fraction >= 0.97;
}

int CG_GetEntity(int entNum, int mod = 0)
{
	return *(int*)0x82BBC554 + mod + (0x374 * entNum); // centity
}

short GetEType(int entNum)
{
	return *(short*)CG_GetEntity(entNum, 0x2A8);
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

bool isEntityPlayer(int i) {

	int cEnt = *(int *)(0x82BBC554 + (0 << 2));
	cEnt += (i * 0x374);

	if ((*(int *)(cEnt + 0x36C) & 0x40000000) == 0)// if the client is dead
		return false;

	if (*(short *)(cEnt + 0x2A8) != 1)
		return false;

	if (*(int *)(cEnt + 0x1D4) & 0x40000)
		return false;

	return (!cgArray_s->ClientInfo[i].Dead && strcmp(cgArray_s->ClientInfo[i].Name, "") && cgArray_s->ClientInfo[i].somethinghax && cgArray_s->Health > 0);
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
	_snprintf(buffer, sizeof(buffer), "cmd mr %i -1 endround", *(int*)(0x829BE624));
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
			if (WorldToScreen(GetTagPos(i, BO1HitBoxes[b]), &bScreenPos.x, &bScreenPos.y))
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