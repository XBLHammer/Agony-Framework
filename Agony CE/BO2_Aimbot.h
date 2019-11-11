bool BoneVisible(Centity_t ent, char *tag)
{
	return Aimtarget_isTargetVisible(0, &ent, SL_GetString(tag, 0));
}

void GetViableBone(int Client, Vector3 *Out = NULL, bool *FoundBone = NULL)
{
	Centity_t e = Centity_s[Client];

	if (BoneVisible(e, "j_helmet") && BoneVisible(e, "j_ankle_le")) {
		if (Out != NULL)
			*Out = GetTagPos(ClosestPlayer, aimBone, true);

		return;
	}

	for (int i = 0; i < 14; i++)
	{
		if (BoneVisible(e, hitBoxes[i]))
		{
			if (Out != NULL)
				*Out = GetTagPos(ClosestPlayer, hitBoxes[i], true);

			if (FoundBone != NULL)
				*FoundBone = true;

			return;
		}
	}
	if (Out != NULL)
		*Out = GetTagPos(ClosestPlayer, aimBone, true);

	if (FoundBone != NULL)
		*FoundBone = false;
}

namespace BO2
{
	enum weapClass_t : int
	{
		WEAPCLASS_RIFLE = 0,
		WEAPCLASS_MG = 1,
		WEAPCLASS_SMG = 2,
		WEAPCLASS_SPREAD = 3,
		WEAPCLASS_PISTOL = 4,
		WEAPCLASS_GRENADE = 5,
		WEAPCLASS_ROCKETLAUNCHER = 6,
		WEAPCLASS_TURRET = 7,
		WEAPCLASS_NON_PLAYER = 8,
		WEAPCLASS_GAS = 9,
		WEAPCLASS_ITEM = 10,
		WEAPCLASS_MELEE = 11,
		WEAPCLASS_KILLSTREAK_ALT_STORED_WEAPON = 12,
		WEAPCLASS_PISTOL_SPREAD = 13,
		WEAPCLASS_MAX
	};
	enum TraceHitType
	{
		TRACE_HITTYPE_NONE = 0,
		TRACE_HITTYPE_ENTITY = 1,
		TRACE_HITTYPE_DYNENT_MODEL = 2,
		TRACE_HITTYPE_DYNENT_BRUSH = 3,
		TRACE_HITTYPE_DYNENT_UNKNOWN = 4
	};
	enum PenetrateType
	{
		PENETRATE_TYPE_NONE = 0x0,
		PENETRATE_TYPE_SMALL = 0x1,
		PENETRATE_TYPE_MEDIUM = 0x2,
		PENETRATE_TYPE_LARGE = 0x3,
		PENETRATE_TYPE_COUNT = 0x4,
	};
#pragma pack(push, 1)
	struct trace_t
	{
		Vector3 normal;//0x0
		char unk1[0x04];//0xc
		float Fraction;//0x10
		char unk2[0x08];//0x14
		TraceHitType hitType;//0x1c
		short hitId;//0x20
		short modelIndex;//0x22
		short partName;//0x24
		short partGroup;//0x26
		char unk4[0x10];//0x28
	}; // 0x38
	struct sFont
	{
		char *fontName;
		int imageTrack;
		bool isSet;
		bool hasBeenPrinted;
	};
	struct BulletFireParams
	{
		int weaponEntIndex;//0x0
		int ignoreEntIndex;//0x4
		float damageMultiplier;//0x8
		int bulletType;//0xc
		Vector3 origStart;//0x10
		Vector3 start;//0x1c
		Vector3 end;//0x28
		Vector3 dir;//0x34
	}; // 0x40
	struct BulletTraceResults
	{
		trace_t trace;//0x0
		char unk[8];//0x34
		int hitEnt; //0x38
		float hitPos[3];//0x3c
		int ignoreHitEnt;//0x48
		int surfaceType;//0x4c
	}; // 0x50
};

float VectorLength_(Vector3 v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

void VectorNormalize_(Vector3 Vec)
{
	float l = 1 / VectorLength_(Vec);
	Vec.x *= l;
	Vec.y *= l;
	Vec.z *= l;
}

typedef bool(*BulletTrace)(int localClient, void *bp, pCentity_t centity_s_ptr, void *results, int surfaceType);
BulletTrace bulletTrace = (BulletTrace)0x8224CDA8;

bool performBulletTrace(int myClientNum, int clients, void *bulletFireParams, void *bulletTraceResults, int surfaceType)
{
	return bulletTrace(0, bulletFireParams, &Centity_s[clients], bulletTraceResults, surfaceType);
}

typedef unsigned short(*Trace_GetEntityHitId)(void *trace);
Trace_GetEntityHitId trace_getEntityHitId = (Trace_GetEntityHitId)0x823F7160;

int getEntityHitId(void *trace)
{
	return trace_getEntityHitId(trace);
}

typedef float(*BG_GetSurfacePenetrationDepth)(DWORD weapDef, int surfaceFlags);
BG_GetSurfacePenetrationDepth bg_getSurfacePenetrationDepth = (BG_GetSurfacePenetrationDepth)0x826B0278;

float getSurfacePenetrationDepth(int surfaceType)
{
	return bg_getSurfacePenetrationDepth(1, surfaceType);
}

typedef bool(*BG_AdvanceTrace)(void *bp, void *br, float dist);
BG_AdvanceTrace bg_advanceTrace = (BG_AdvanceTrace)0x826B0148;

bool advanceTrace(void *bulletFireParams, void *bulletTraceResults, float dist)
{
	return bg_advanceTrace(bulletFireParams, bulletTraceResults, dist);
}

float Get3dDistance(Vector3 myCoords, Vector3 enemyCoords)
{
	return sqrt(
		pow(double(enemyCoords[0] - myCoords[0]), 2.0) +
		pow(double(enemyCoords[1] - myCoords[1]), 2.0) +
		pow(double(enemyCoords[2] - myCoords[2]), 2.0)
	);
}

bool isClientWallbangableBo2(int client)
{
	int weaponDefPtr = BG_GetWeaponDef(cgArray_s->ClientInfo[cgArray_s->ClientNumber].Weapon);

	if (!weaponDefPtr)
		return -1.0f;

	BO2::BulletFireParams bulletFireParams;
	memset(&bulletFireParams, 0x00, sizeof(BO2::BulletFireParams));

	bulletFireParams.weaponEntIndex = 1022;
	bulletFireParams.ignoreEntIndex = cgArray_s->ClientNumber;
	bulletFireParams.damageMultiplier = 1.0f;

	Vector3 End = GetTagPos(client, aimBone);
	memcpy(bulletFireParams.origStart, cgArray_s->RefDef.viewOrigin, 0xC);
	memcpy(bulletFireParams.start, cgArray_s->RefDef.viewOrigin, 0xC);
	memcpy(bulletFireParams.end, End, 0xC);

	Vector3 dir = SubstractVector(End, cgArray_s->RefDef.viewOrigin);
	dir = vectoangles(dir);
	angleVectors(dir, &bulletFireParams.dir, NULL, NULL);

	BO2::BulletTraceResults bulletTraceResults;
	bool hit = performBulletTrace(cgArray_s->ClientNumber, cgArray_s->ClientNumber, &bulletFireParams, &bulletTraceResults, 0);

	if (!hit)
		return bulletFireParams.damageMultiplier;

	if (getEntityHitId(&bulletTraceResults.trace) != 1022)
		return 0.0f;

	if (*(WORD*)((DWORD)&bulletTraceResults.trace + 40) == 2)
		return 0.0f;

	if (!*(DWORD*)(weaponDefPtr + 36)
		|| *(BYTE*)((DWORD)&bulletTraceResults.trace + 43)
		)
		return 0.0f;

	int penetrationCount = 0;
	float perk_bulletPenetrationMultiplier = 2.0f;
	float penetrationDepth;
	BO2::BulletFireParams bulletFireParams_2;
	BO2::BulletTraceResults bulletTraceResults_2;
	Vector3 hitPosBackup;
	bool hit_2;
	bool v26;

	while (true)
	{

		penetrationDepth = getSurfacePenetrationDepth(bulletTraceResults.surfaceType);

		if (penetrationDepth <= 0.0f)
			return 0.0f;

		memcpy(hitPosBackup, bulletTraceResults.hitPos, 0xC);
		if (!advanceTrace(&bulletFireParams, &bulletTraceResults, 0.13500000536441803f))
			return 0.0f;

		hit = performBulletTrace(cgArray_s->ClientNumber, cgArray_s->ClientNumber, &bulletFireParams, &bulletTraceResults, bulletTraceResults.surfaceType);

		memcpy(&bulletFireParams_2, &bulletFireParams, sizeof(BO2::BulletFireParams));

		VectorScale(bulletFireParams.dir, -1.0f, bulletFireParams_2.dir);
		memcpy(bulletFireParams_2.start, bulletFireParams.end, 0xC);
		VectorMA(hitPosBackup, 0.009999999776482582f, bulletFireParams_2.dir, bulletFireParams_2.end);

		memcpy(&bulletTraceResults_2, &bulletTraceResults, sizeof(BO2::BulletTraceResults));

		VectorScale(bulletTraceResults_2.trace.normal, -1.0f, bulletTraceResults_2.trace.normal);


		if (hit)
			advanceTrace(&bulletFireParams_2, &bulletTraceResults_2, 0.009999999776482582f);

		hit_2 = performBulletTrace(cgArray_s->ClientNumber, cgArray_s->ClientNumber, &bulletFireParams_2, &bulletTraceResults_2, bulletTraceResults_2.surfaceType);

		v26 = (hit_2 != 0) && *(BYTE*)((DWORD)&bulletTraceResults_2.trace + 42) || *(BYTE*)((DWORD)&bulletTraceResults.trace + 43) && *(BYTE*)((DWORD)&bulletTraceResults_2.trace + 43);

		if (hit_2 || v26)
			break;

		if (!hit)
		{
			return bulletFireParams.damageMultiplier;
		}
		goto continueLoop;

	continueLoop:
		if (hit)
		{
			penetrationCount++;
			if (penetrationCount < 5) // max number of surfaces penetrated is 5 (from penetrationCount dvar)
				continue;
		}

		return 0.0f;
	}

	// calculate the surface depth
	float surfaceDepth = 0.0f;
	if (v26)
		surfaceDepth = Get3dDistance(bulletFireParams_2.start, bulletFireParams_2.end);
	else
		surfaceDepth = Get3dDistance(bulletTraceResults_2.hitPos, hitPosBackup);


	if (surfaceDepth < 1.0f)
		surfaceDepth = 1.0f;

	if (hit_2)
	{
		float penetrationDepth_2 = getSurfacePenetrationDepth(bulletTraceResults_2.surfaceType);


		penetrationDepth = min(penetrationDepth, penetrationDepth_2);

		if (penetrationDepth <= 0.0f)
			return 0.0f;
	}

	if (1 == 0)
	{
		if (1 == 0)
		{
		LABEL_84:
			if (bulletFireParams.damageMultiplier <= 0.0f)
				return 0.0f;

			goto continueLoop;
		}
	}

	bulletFireParams.damageMultiplier -= surfaceDepth / penetrationDepth;
	goto LABEL_84;

	return 0.0f;
}

struct refdef_t // cg_s + 0x4D880
{
	int x;					//0x00-0x04 - 0
	int y;					//0x04-0x08 - 0
	int width;				//0x08-0x0C - 1280 0x0500
	int height;				//0x0C-0x10 - 720 0x02D0
	char Buf[0x14];			//0x10-0x24 - unk
	float tanHalfFovX;		//0x24-0x28 - 3F 59 74 0D( 0.849427f )
	float tanHalfFovY;		//0x28-0x2C - 3E F4 A2 8F( 0.4778027f )
	char Buf2[0x0C];		//0x2C-0x38 - unk
	float vieworg[3];		//0x38-0x44 - 
	int Buf3;				//0x44-0x48 - null
	float viewaxis[3][3];	//0x48-0x6C - 
} *pRefdef;

int cg_sBO2(int Client)
{
	int Value = *(int *)(0x82BBAE68);
	if (Value == 0)
		return 0;
	Value += (Client * 0x87700);

	pRefdef = (refdef_t*)(Value + 0x4D880);

	return Value;
}

bool(__cdecl *CG_GetPlayerViewOrigin)(int localClientNum, DWORD ps, Vector3 &origin) = (bool(*)(int, DWORD, Vector3 &))0x822544B0;
Vector3 &GetViewPOS()
{
	Vector3 MyViewOrigin;
	CG_GetPlayerViewOrigin(0, (DWORD)cg_sBO2 + 0x480A8, MyViewOrigin);
	return MyViewOrigin;
}

bool isVisible(int i, short tag)
{
	Vector3 end = Vector3();
	Vector3 start = GetViewPOS();
	trace_t trace;

	if (!SL_GetString(aimBone, 0))
		return false;

	CG_LocationalTrace(&trace, start, end, cgArray_s->ClientNumber, 0x803003, true, 0);
	return trace.fraction >= 0.95f;
}

template <class T> void writeData(int address, T data, char* info) {
	if (MmIsAddressValid((PVOID)address))
		memcpy((T*)address, &data, sizeof T);
}

float *GetViewOrig()
{
	return cgArray_s->RefDef.viewOrigin;
}

void __cdecl VectorToAngles(const float * Vec, float * angles)
{
	float forward, yaw, pitch, PiDiv = (180.0f / XM_PI);

	if (Vec[1] == 0 && Vec[0] == 0)
	{
		yaw = 0;
		if (Vec[2] > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		if (Vec[0])
			yaw = (atan2(Vec[1], Vec[0]) * PiDiv);
		else if (Vec[1] > 0)
			yaw = 90.0f;
		else
			yaw = 270.0f;

		if (yaw < 0.0f)
			yaw += 360.0f;

		forward = sqrt((Vec[0] * Vec[0]) + (Vec[1] * Vec[1]));
		pitch = (atan2(Vec[2], forward) * PiDiv);

		if (pitch < 0.0f)
			pitch += 360;
	}

	angles[0] = 360.0f - pitch;
	angles[1] = yaw;
	angles[2] = 0.0f;
	for (int i = 0; i < 2; i++) {
		if (angles[i] > 360.0f)
			angles[i] -= 360.0f;
		if (angles[i] < 0.0f)
			angles[i] += 360.0f;
	}
}

void __cdecl AngleVectors(const float * angles, float * forward, float * right, float * up)
{
	float angle, sr, sp, sy, cr, cp, cy, PiDiv = (XM_PI / 180.0f);

	angle = angles[1] * PiDiv;
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[0] * PiDiv;
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[2] * PiDiv;
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1 * sr*sp*cy + -1 * cr*-sy);
		right[1] = (-1 * sr*sp*sy + -1 * cr*cy);
		right[2] = -1 * sr*cp;
	}
	if (up)
	{
		up[0] = (cr*sp*cy + -sr*-sy);
		up[1] = (cr*sp*sy + -sr*cy);
		up[2] = cr*cp;
	}
}

bool CanKillPlayer(int Player, Vector3 Pos)
{
	int weaponDefPtr;
	int cg_s;
	float *MyView;
	float Dir[3];
	int cEnt;
	int OurcEnt;
	int Entity;
	int Weapon;
	int OurClient;
	__int64 Autowall[3];
	byte Byte[0x100];

	BulletFireParams bulletFireParams;

	cg_s = cg_sBO2(0);
	MyView = GetViewOrig();
	OurcEnt = *(int *)(cg_s + 0x28);

	if (OurcEnt == 0)
		return false;

	OurcEnt = *(int *)(OurcEnt + 0x1B0);
	cEnt = cg_s + (Player * 0x808) + 0x69A90;
	OurcEnt = cg_s + (OurcEnt * 0x808) + 0x69A90;

	Entity = OurClient;

	ZeroMemory(&bulletFireParams, sizeof(BulletFireParams));

	Weapon = *(int *)(cg_s + 0x480A8 + 0x1B8);
	weaponDefPtr = ((int(*)(...))0x826BF988)(Weapon);

	bulletFireParams.weaponEntIndex = 1997;
	bulletFireParams.ignoreEntIndex = Entity;
	bulletFireParams.damageMultiplier = 1.0f;
	bulletFireParams.methodOfDeath = 1 || 2;

	VectorCopy(MyView, bulletFireParams.origStart);
	VectorCopy(MyView, bulletFireParams.start);
	VectorCopy(Pos, bulletFireParams.end);

	VectorSubtract(Pos, MyView, Dir);
	VectorToAngles(Dir, Dir);

	AngleVectors(Dir, bulletFireParams.dir, NULL, NULL);

	((void(*)(...))0x82258840)(0, &bulletFireParams, Weapon, OurcEnt, MyView, 1, 1, Byte);

	/**(int*)0x822DF558 = 0x7D8802A6;
	*(int*)0x82258520 = 0x7D8802A6;

	//restore them
	*(__int64*)0x82257C48 = Autowall[0];
	*(__int64*)0x82257D28 = Autowall[1];
	*(__int64*)0x82257D54 = Autowall[2];

	*(long long*)0x8224D060 = 0x7D8802A69181FFF8;
	*(long long*)0x821FA7F8 = 0x3D6082BC7C892378;

	*(int*)0x822DF558 = 0x7D8802A6;
	*(int*)0x82258520 = 0x7D8802A6;*/

	return bulletFireParams.ignoreEntIndex == Player;
}

bool isAnyVis(int mClient)
{
	for (int i = 0; i < 18; ++i)
	{
		if (i == mClient)
			continue;

		if (!IsEnemy(i))
			continue;

		if (!isEntityPlayer(i))
			continue;

		if (!Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString(aimBone, 0)))
			continue;

		return true;
	}
	return false;
}

bool EntityWall(int i) {
	return CanKillPlayer(i, GetTagPos(i, aimBone)) || isClientWallbangableBo2(i);
}

int nearestClient;
int GetNearestPlayer(int Client)
{
	bool ClientVis = isAnyVis(Client);

	nearestClient = -1;
	float nearestDistance = 99999999;
	for (int i = 0; i < 18; i++)
	{
		if (i == Client)
			continue;

		if (!isEntityPlayer(i))
			continue;

		if (!IsEnemy(i))
			continue;

		if (bPlayerFriendly[i])
			continue;

		if (aimEvent == 0) {
			if (!EntityWall(i))
				continue;
		}
		else if (aimEvent == 1) {
			if (!Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString(aimBone, 0)))
				continue;
		}
		else if (aimEvent == 2) {
			if (!GetAsyncKeyState(0x1337))
				continue;
		}
		else if (aimEvent == 3) {
			if (!GetAsyncKeyState(0x1338))
				continue;
		}

		if (bLegitbot) {
			if (!Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString(aimBone, 0)))
				continue;

			Vector2 ScreenPos;
			if (WorldToScreen(GetTagPos(i, "j_head"), &ScreenPos.x, &ScreenPos.y))
			{
				if (!(ScreenPos.x > ((cgArray_s->RefDef.Width / 2) - (fFOVSize / 2)) &&
					ScreenPos.x < ((cgArray_s->RefDef.Width / 2) + (fFOVSize / 2)) &&
					ScreenPos.y >((cgArray_s->RefDef.Height / 2) - (fFOVSize / 2)) &&
					ScreenPos.y < ((cgArray_s->RefDef.Height / 2) + (fFOVSize / 2))))
					continue;
			}
			else
				continue;
		}

		float Distance = GetDistance(GetPlayerOrigin(Client), GetPlayerOrigin(i));
		bool ID_Vis = Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString(aimBone, 0));

		if (Distance < nearestDistance && (ClientVis ? ID_Vis : !ID_Vis) || (bPlayerPriority[i] && nearestDistance > 15))
		{
			if (!bPlayerPriority[i] || (bPlayerPriority[i] && nearestDistance > 15))
				nearestDistance = Distance;
			else
				nearestDistance = 15;
			nearestClient = i;
		}
	}
	return nearestClient;
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

const char* shieldBones[] = {
	"j_knee_ri",
	"j_knee_le",
	"j_ankle_ri",
	"j_ankle_le",
};

bool ShieldCheck(int i) {
	if (Centity_s[i].WeaponID == 89)
		return true;
	else {
		aimTags_c = 1;
	}

	if (*(int*)((int)&Centity_s[i] + 0x1B4) == 89)
		return true;
	else {
		aimTags_c = 1;
	}

	return false;
}

const char* riotbonehandler(int client)
{
	Centity_t e = Centity_s[client];
	int boneDmg = 1.0f;

	/*Shield bones*/
	if (EntityWall(client) && EntityWall(client) == true || EntityWall(client) == false) {
		aimTags_c = 17; /*j_ball_le*/
		boneDmg == 0.63f;
	}
	if (EntityWall(client) && EntityWall(client) == true || EntityWall(client) == false) {
		aimTags_c = 16; /*j_ball_ri*/
		boneDmg == 0.63f;
	}
	if (EntityWall(client) && EntityWall(client) == true || EntityWall(client) == false) {
		aimTags_c = 15; /*j_ankle_le*/
		boneDmg == 0.63f;
	}
	if (EntityWall(client) && EntityWall(client) == true || EntityWall(client) == false) {
		aimTags_c = 14; /*j_ankle_ri*/
		boneDmg == 0.63f;
	}
	if (Centity_s[client].OldWeapon == 89 && EntityWall(client) && EntityWall(client) && EntityWall(client) == true || EntityWall(client) == false) {
		aimTags_c = 13; /*j_knee_le*/
		boneDmg == 0.95f;
	}
	if (Centity_s[client].OldWeapon == 89 && EntityWall(client) && EntityWall(client) && EntityWall(client) == true || EntityWall(client) == false) {
		aimTags_c = 12; /*j_knee_ri*/
		boneDmg == 0.95f;
	}

	/*Visible Shield Check*/
	if (BoneVisible(e, "j_ball_le")) {
		aimTags_c = 17; /*j_ball_le*/
		boneDmg == 0.63f;
	}
	if (BoneVisible(e, "j_ball_ri")) {
		aimTags_c = 16; /*j_ball_ri*/
		boneDmg == 0.63f;
	}
	if (BoneVisible(e, "j_ankle_le")) {
		aimTags_c = 15; /*j_ankle_le*/
		boneDmg == 0.63f;
	}
	if (BoneVisible(e, "j_ankle_ri")) {
		aimTags_c = 14; /*j_ankle_ri*/
		boneDmg == 0.63f;
	}
	if (BoneVisible(e, "j_knee_le")) {
		aimTags_c = 13; /*j_knee_le*/
		boneDmg == 0.95f;
	}
	if (BoneVisible(e, "j_knee_ri")) {
		aimTags_c = 12; /*j_knee_ri*/
		boneDmg == 0.95f;
	}

	if (boneDmg <= 0.95f) {
		(const char*)&shieldBones;
	}

	return (const char*)&shieldBones;
}

bool bBezierSeedSet;

void _Aimbot()
{
	Vector3 _vOutPos;

	if (!isEntityPlayer(cgArray_s->ClientNumber)) return;

	if (ResetAngles && ClosestPlayer == -1)
	{
		ClientActive->viewAngle = OldAngles;
		ResetAngles = false;
	}

	ClosestPlayer = GetNearestPlayer(cgArray_s->ClientNumber);

	if (ClosestPlayer == -1) {
		bFirstBezierSet = false;
		bBezierSeedSet = false;
		return;
	}

	if (!bBezierSeedSet) {
		dwBezierSeed = cgArray_s->Servertime;
		bBezierSeedSet = true;
	}

	Position = GetTagPos(ClosestPlayer, !bPlayerBodyAim[ClosestPlayer] ? aimBone : "j_neck", true);

	ShieldCheck(ClosestPlayer) ? Position = GetTagPos(ClosestPlayer, riotbonehandler(ClosestPlayer)) : Position;

	Position = (ShieldCheck(ClosestPlayer)) ? GetTagPos(ClosestPlayer, riotbonehandler(ClosestPlayer)) : Position;

	if (bPrediction)
		PosPrediction(&Centity_s[ClosestPlayer], Position, fPrediction, true);

	//GetViableBone(ClosestPlayer);

	FinalAngles = vectoangles(Position - cgArray_s->RefDef.viewOrigin) - ClientActive->baseAngle;

	if (bRagebot && !bSilent) {
		if (bSnapback && !ResetAngles)
		{
			OldAngles = ClientActive->viewAngle;
			ResetAngles = true;
		}

		ClientActive->viewAngle = FinalAngles;
	}

	if (bLegitbot)
		_SmoothAngle(FinalAngles, ClientActive->viewAngle, fAimSpeed);
}

int cg_ss(int Client)
{
	int Value = *(int *)(0x82BBAE68);
	if (Value == 0)
		return 0;
	Value += (Client * 0x87700);

	return Value;
}

int ClientActive_f(int Client)
{
	int Value = *(int *)(0x82C70F4C);
	if (Value == 0)
		return 0;
	return (Value);
}

void __cdecl VectorToAngles_(const float * Vec, float * angles)
{
	float forward, yaw, pitch, PiDiv = (180.0f / XM_PI);

	if (Vec[1] == 0 && Vec[0] == 0)
	{
		yaw = 0;
		if (Vec[2] > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		if (Vec[0])
			yaw = (atan2(Vec[1], Vec[0]) * PiDiv);
		else if (Vec[1] > 0)
			yaw = 90.0f;
		else
			yaw = 270.0f;

		if (yaw < 0.0f)
			yaw += 360.0f;

		forward = sqrt((Vec[0] * Vec[0]) + (Vec[1] * Vec[1]));
		pitch = (atan2(Vec[2], forward) * PiDiv);

		if (pitch < 0.0f)
			pitch += 360;
	}

	angles[0] = 360.0f - pitch;
	angles[1] = yaw;
	angles[2] = 0.0f;
	for (int i = 0; i < 2; i++) {
		if (angles[i] > 360.0f)
			angles[i] -= 360.0f;
		if (angles[i] < 0.0f)
			angles[i] += 360.0f;
	}
}

void __cdecl AngleVectors_(const float * angles, float * forward, float * right, float * up)
{
	float angle, sr, sp, sy, cr, cp, cy, PiDiv = (XM_PI / 180.0f);

	angle = angles[1] * PiDiv;
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[0] * PiDiv;
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[2] * PiDiv;
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1 * sr*sp*cy + -1 * cr*-sy);
		right[1] = (-1 * sr*sp*sy + -1 * cr*cy);
		right[2] = -1 * sr*cp;
	}
	if (up)
	{
		up[0] = (cr*sp*cy + -sr*-sy);
		up[1] = (cr*sp*sy + -sr*cy);
		up[2] = cr*cp;
	}
}

float(*BG_Random)(int* seed) = (float(*)(int*))0x82696250;
void(*BG_SeedRandWithGameTime)(int* seed) = (void(*)(int*))0x826961B8;
#define seedRand(seed) *seed = (0x343FD * (0x343FD * (0x343FD * (0x343FD * *seed + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3)


void RandomBulletDir(int randSeed, float *x, float *y)
{
	BG_SeedRandWithGameTime(&randSeed);
	float theta = BG_Random(&randSeed) * 360.0;

	seedRand(&randSeed);

	float r = BG_Random(&randSeed);
	float v3 = (float)(theta * 0.017453292);

	*x = r * cos(v3);
	*y = r * sin(v3);
}
int cg_Re(int Client)
{
	int Value = *(int *)(0x82BBAE68);
	if (Value == 0)
		return 0;
	Value += (Client * 0x87700);

	pRefdef = (refdef_t*)(Value + 0x4D880);

	return Value;
}

void removespread(Usercmd_t *cmd)
{
	float minSpread = 0.0f, maxSpread = 0.0f, totalSpread = 0.0f;

	int Seed = cmd->time;

	int cg = cg_Re(0);

	((void(*)(...))0x826BB4E0)(((DWORD)cg + 0x480A8), cmd->weapon, &minSpread, &maxSpread);

	totalSpread = (minSpread + ((maxSpread - minSpread) * (cgArray_s->SpreadMultiplier * 0.00399956862f))); //0.00399956862f

	RandomBulletDir(Seed, &minSpread, &maxSpread);

	cmd->buttons &= ~0x80000000;

	cmd->viewAngles[0] += ANGLE2SHORT(maxSpread * totalSpread);
	cmd->viewAngles[1] += ANGLE2SHORT(minSpread * totalSpread);
}

Vector3 ViewPos, SpreadAngle, spreadAng, spreadEndVec;

void _spreadFix(Usercmd_t *cmd)
{
	if (!GetAsyncKeyState(0x1337))
	{
		float viewAngles[3],
			viewAxis[3][3],
			minSpread,
			maxSpread,
			spread,
			spreadEndVec[3],
			spreadDirection[3];

		int ClientActive_ts,
			cg_s,
			*cmdNum,
			seed;

		float Range;
		int playerState,
			WeaponNum,
			WeaponDef,
			unkSpread = 0;

		ClientActive_ts = ClientActive_f(0);
		cg_s = cg_ss(0);
		cmdNum = (int *)(ClientActive_ts + 0x44AA8);

		playerState = cg_s + 0x480A8;
		WeaponNum = *(int *)(cg_s + 0x248);
		WeaponDef = ((int(*)(int))0x826BF988)(WeaponNum);
		unkSpread = 0;

		cmd->buttons &= ~0x80000000;

		((void(*)(...))0x826BB4E0)(playerState, WeaponNum, &minSpread, &maxSpread);

		spread = *(float *)(cg_s + 0x80B80) * 0.0039215689f;

		if (*(float *)(playerState + 0x1E0) == 1.0f)
			minSpread = *(float *)(WeaponDef + 0x7E0);

		spread = ((spread * (maxSpread - minSpread)) + minSpread);

		viewAngles[0] = *(float *)(playerState + 0x1F8);
		viewAngles[1] = *(float *)(playerState + 0x1FC);
		viewAngles[2] = 0;
		AngleVectors_(viewAngles, viewAxis[0], viewAxis[1], viewAxis[2]);

		seed = *(int *)playerState;

		((void(*)(...))0x826961B8)(&seed);

		if (*(int *)(WeaponDef + 0x20) != 0x3 && *(int *)(WeaponDef + 0x20) != 0xD)
			unkSpread = 1;
		else
			unkSpread = *(int *)(WeaponDef + 0x3D0);

		if (*(int *)(WeaponDef + 32) == 3 || *(int *)(WeaponDef + 32) == 0xD)
			Range = *(float *)(WeaponDef + 0x410) * ((float(*)(...))0x826C40C8)(WeaponNum);
		else
			Range = 8192.0f;

		((void(*)(...))0x8224D4A8)(&seed, spread, (float*)&cgArray_s->RefDef.viewOrigin, spreadEndVec, spreadDirection, viewAxis[0], viewAxis[1], viewAxis[2], Range,
			WeaponNum, 0, unkSpread);

		VectorToAngles_(spreadDirection, viewAngles);

		if (*(float *)(cg_s + 0x4DB18) == 0)
		{
			cmd->viewAngles[0] += ANGLE2SHORT(*(float *)(playerState + 0x1F8) - viewAngles[0]);
			cmd->viewAngles[1] += ANGLE2SHORT(*(float *)(playerState + 0x1FC) - viewAngles[1]);
		}
	}
}