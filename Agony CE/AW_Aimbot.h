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

/*
void R_FireBulletPenetrate(BulletFireParams* bp, unsigned int weaponIndex, pCentity_t attacker, int enemyID)
{
bool v13, traceHit;

// ? v6 = a1
int weaponDef = BG_GetWeaponDef(weaponIndex);
int weaponVariantDef = BG_GetWeaponVariantDef(weaponIndex);

BulletTraceResults br;
bool firstTrace = BulletTrace(0, bp, weaponDef, &br, 0);

if (br.trace.startsolid || !firstTrace)
return;

float weaponPenetration = *(float*)(*(int*)(0x82557750 + (attacker->WeaponID * 4)) + 0x30);
float bulletPenetrationMult = *(float*)(*(int*)(0x82557554) + 8);

for (int i = 0; i < 5; i++)
{
float maxDepth = BG_GetSurfacePenetrationDepth(weaponDef, br.depthSurfaceType);

maxDepth *= weaponPenetration;

// if fmj
maxDepth *= bulletPenetrationMult;

if (maxDepth <= 0.0f)
return;

Vector3 lastHitPos = br.hitPos;

if (!BG_AdvancedTrace(bp, &br, 0.13500001))
return;

traceHit = BulletTrace(0, bp, weaponDef, &br, br.depthSurfaceType);

BulletFireParams revBp = *bp;

revBp.dir = -bp->dir;
revBp.start = bp->end;
revBp.end = revBp.dir * 0.009999999776482582f + lastHitPos;

BulletTraceResults revBr = br;

revBr.trace.normal = -revBr.trace.normal;

if (traceHit)
{
revBr.trace.normal.z = 0.0099999998f;
BG_AdvancedTrace(&revBp, &revBr, 0.0099999998f);
}

bool revTrace = BulletTrace(0, &revBp, weaponDef, &revBr, revBr.depthSurfaceType);

v13 = (revTrace && revBr.trace.allsolid || br.trace.startsolid && revBr.trace.startsolid);

if (!revTrace)
break;

float depth;

if (v13)
depth = (revBp.end - revBp.start).Length();
else
depth = (lastHitPos - revBr.hitPos).Length();

if (depth < 1.0f)
depth = 1.0f;

if (revTrace)
{
float newDepth = BG_GetSurfacePenetrationDepth(weaponDef, revBr.depthSurfaceType) * bulletPenetrationMult;

maxDepth = min(maxDepth, newDepth) * weaponPenetration;

if (maxDepth <= 0.0f)
return;
}

bp->damageMultiplier -= depth / maxDepth;

if (bp->damageMultiplier <= 0.0f)
return;

if (!revTrace)
{
if (traceHit || !(br.trace.surfaceFlags & 4))
{
bp->damageMultiplier = 1;
bp->ignoreEntIndex = enemyID;
return;
}
}
}

if (!v13) {
if (!traceHit)
return;

//bp->damageMultiplier = 1;
//bp->ignoreEntIndex = enemyID;
//return;
}
}
*/

bool CanKillPlayer(int Player, Vector3 PlayerOrigin)
{
	BulletFireParams bp;
	memset(&bp, 0, sizeof(BulletFireParams));

	bp.MaxEntNum = 0x7FE;
	bp.ignoreEntIndex = cgArray_s->ClientNumber;
	bp.damageMultiplier = 1.0f;
	bp.methodOfDeath = 2;
	bp.origStart = cgArray_s->RefDef.viewOrigin;
	bp.start = cgArray_s->RefDef.viewOrigin;
	bp.end = PlayerOrigin;

	angleVectors(vectoangles(PlayerOrigin - cgArray_s->RefDef.viewOrigin), &bp.dir, NULL, NULL);

	*(long long*)0x825D22F8 = 0x386000014E800020;
	*(long long*)0x82535D78 = 0x386000014E800020;
	*(long long*)0x825C4E98 = 0x386000014E800020;

	FireBulletPenetrate(0, &bp, Centity_s[cgArray_s->ClientNumber].WeaponID, 0, 1, &Centity_s[cgArray_s->ClientNumber], 0xFFFFFFFF, cgArray_s->RefDef.viewOrigin, 0);

	*(long long*)0x825D22F8 = 0x7D8802A64BC21C09;
	*(long long*)0x82535D78 = 0x7D8802A64BCBE175;
	*(long long*)0x825C4E98 = 0x7D8802A64BC2F081;

	return (bp.ignoreEntIndex == Player && bp.damageMultiplier > 0.0f);
}

bool EntityWall(int i) {
	return Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString("j_head", 0)) || CanKillPlayer(i, GetTagPos(i, "j_head"));
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
			if (WorldToScreen(GetTagPos(i, aimBone), &ScreenPos.x, &ScreenPos.y))
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

bool bShieldEquipped(int i) {
	return false;// (strstr(cgArray_s->ClientInfo[i].WeaponModel, "riot_shield") || strstr(cgArray_s->ClientInfo[i].WeaponModel2, "riot_shield"));
}

bool bBezierSeedSet;

void _Aimbot()
{
	if (!isEntityPlayer(cgArray_s->ClientNumber)) return;

	if (ResetAngles && ClosestPlayer == -1)
	{
		ClientActive->viewAngle.x = OldAngles.x;
		ClientActive->viewAngle.y = OldAngles.y;

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

	Position = GetTagPos(ClosestPlayer, !bPlayerBodyAim[ClosestPlayer] ? aimBone : "j_spine4", true);

	if (bMultiBox)
		GetViableBone(ClosestPlayer, &Position);

	bAntiAntiAim && bShieldEquipped(ClosestPlayer) ? Position = GetTagPos(ClosestPlayer, "j_ankle_le") : Position;

	if (bPrediction)
		PosPrediction(&Centity_s[ClosestPlayer], Position, fPrediction, true);

	FinalAngles = vectoangles(Position - cgArray_s->RefDef.viewOrigin) - ClientActive->baseAngle;

	if (bRagebot && !bSilent) {
		if (bSnapback && !ResetAngles)
		{
			OldAngles.x = ClientActive->viewAngle.x;
			OldAngles.y = ClientActive->viewAngle.y;

			ResetAngles = true;
		}

		ClientActive->viewAngle.x = FinalAngles.x;
		ClientActive->viewAngle.y = FinalAngles.y;

	}

	if (bLegitbot) {
		Vector3 curAngle;
		curAngle.x = ClientActive->viewAngle.x;
		curAngle.y = ClientActive->viewAngle.y;
		curAngle.z = 0;

		_SmoothAngle(FinalAngles, curAngle, fAimSpeed);
	}
}


double CG_GoodRandomFloat(int *pHoldrand)
{
	unsigned int r11 = 214013 * *pHoldrand + 2531011;
	*pHoldrand = r11;
	return (double)(r11 >> 17) * 0.000030517578;
}

void RandomBulletDir(int randSeed, float *x, float *y)
{
	float f26 = (CG_GoodRandomFloat(&randSeed) * 360.0f) * (M_PI / 180.0f);
	float f28 = CG_GoodRandomFloat(&randSeed);
	*x = f28 * cosf(f26); // sin
	*y = f28 * sinf(f26); // cos
}

void GetWeaponSpread(float*Spread)
{
	float SpreadMultiplier = *(float*)((*(int*)(0x82AD0298)) + 0x5B8) / 255.0f;

	float MaxSpread = 0.0f;
	float BaseSpread = 0.0f;

	BG_GetSpeadForWeapon(cgArray_s, &MaxSpread, &BaseSpread);

	*Spread = BaseSpread + ((MaxSpread - BaseSpread) * SpreadMultiplier);
}

void CG_BulletEndpos(int randSeed, Vector3 *end, Vector3 RefDefAngles)
{
	float flSpread, flSpreadX, flSpreadY;

	float flDistance = 8192.f;

	GetWeaponSpread(&flSpread);
	flSpread = tan(flSpread * (M_PI / 180.0f)) * flDistance;

	RandomBulletDir(randSeed, &flSpreadX, &flSpreadY);

	flSpreadX *= flSpread;
	flSpreadY *= flSpread;

	Vector3 ForwardDir, RightDir, UpDir;

	angleVectors(RefDefAngles, &ForwardDir, &RightDir, &UpDir);

	Vector3 SpreadView;

	SpreadView.x = cgArray_s->RefDef.viewOrigin.x + (ForwardDir.x * flDistance) + (RightDir.x * flSpreadX) + (UpDir.x * flSpreadY);
	SpreadView.y = cgArray_s->RefDef.viewOrigin.y + (ForwardDir.y * flDistance) + (RightDir.y * flSpreadX) + (UpDir.y * flSpreadY);
	SpreadView.z = cgArray_s->RefDef.viewOrigin.z + (ForwardDir.z * flDistance) + (RightDir.z * flSpreadX) + (UpDir.z * flSpreadY);

	*end = SpreadView;
}
Vector3 ViewPos, SpreadAngle, spreadAng, spreadEndVec;

int TransformSeed_(int seed) {
	return 0x343FD * (0x343FD * (0x343FD * (0x343FD * seed + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3;
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

void __cdecl AngleVectors__(const float * angles, float * forward, float * right, float * up)
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

int cg_s__(int Client)
{
	int Value = *(int *)(0x82AD0298);
	if (Value == 0)
		return 0;

	return Value;
}

void _spreadFix(Usercmd_t *oldcmd)
{
	float viewAngles[3],
		viewAxis[3][3],
		minSpread,
		maxSpread,
		spread,
		spreadEndVec[3],
		spreadDirection[3];

	int ClientActive_t,
		cg_s,
		weapon,
		seed;

	cg_s = cg_s__(0);

	// get the weapon
	weapon = *(int *)(cg_s + 0x5A8);

	// aimSpreadScale
	spread = *(float *)(cg_s + 0xBDB80) * 0.0039215689f;


	((void(*)(...))0x82647658)(cg_s, &minSpread, &maxSpread);

	spread = ((spread * (maxSpread - minSpread)) + minSpread);

	// get our view axis
	viewAngles[0] = 0;
	viewAngles[1] = 0;
	viewAngles[2] = 0;
	AngleVectors__(viewAngles, viewAxis[0], viewAxis[1], viewAxis[2]);


	seed = oldcmd->time;
	seed = TransformSeed_(seed);

	((void(*)(...))0x825C5130)(&seed, 0.0f, spread, &cgArray_s->RefDef.viewOrigin, spreadEndVec, spreadDirection, 0.0f, 360.0f, viewAxis[0], viewAxis[1], viewAxis[2], 8192.0f);

	VectorToAngles_(spreadDirection, viewAngles);


	oldcmd->viewAngles[0] += ANGLE2SHORT(-viewAngles[0]);
	oldcmd->viewAngles[1] += ANGLE2SHORT(-viewAngles[1]);
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