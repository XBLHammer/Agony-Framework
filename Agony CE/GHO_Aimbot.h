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
	memset(&bp, 0x00, sizeof(bp));

	//setupBulletTrace(&bp, eyePos, Functions::getTagPos(clientNum, tag));

	*(long long*)0x822C73C0 = 0x386000014E800020;
	*(long long*)0x82385B38 = 0x386000014E800020;
	*(long long*)0x822C21F8 = 0x386000014E800020;

	FireBulletPenetrate(0, &bp, Centity_s[cgArray_s->ClientNumber].WeaponID, 0, &Centity_s[cgArray_s->ClientNumber], 0xFFFFFFFF, cgArray_s->RefDef.viewOrigin, false);

	*(long long*)0x822C73C0 = 0x7D8802A648513B51;
	*(long long*)0x82385B38 = 0x7D8802A6484553D1;
	*(long long*)0x822C21F8 = 0x7D8802A69181FFF8;

	return Player == bp.ignoreEntIndex;
}

bool EntityWall(int i) {
	return Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString(aimBone, 0)) || CanKillPlayer(i, GetTagPos(i, aimBone));
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
			OldAngles = ClientActive->viewAngle;
			ResetAngles = true;
		}

		ClientActive->viewAngle = FinalAngles;
	}

	if (bLegitbot)
		_SmoothAngle(FinalAngles, ClientActive->viewAngle, fAimSpeed);
}


float CG_GoodRandomFloat(int *pHoldrand)
{
	/* Generating random value based on seed */
	unsigned int r11 = 214013 * *pHoldrand + 2531011;
	*pHoldrand = r11; /* Applying value to seed for next usage */
	return (r11 >> 17) * 0.000030517578; /* Returning shifted value */
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
	float SpreadMultiplier = cgArray_s->SpreadMultiplier / 255.0f;

	float MaxSpread = 0.0f;
	float BaseSpread = 0.0f;

	int iLocalWeapon = Centity_s[cgArray_s->ClientNumber].WeaponID;

	BG_GetSpreadForWeapon(GetPointer(0x82AD56FC), iLocalWeapon, &BaseSpread, &MaxSpread); /* Gets min and max spread values */

	*Spread = BaseSpread + ((MaxSpread - BaseSpread) * SpreadMultiplier);
}

void CG_BulletEndpos(int randSeed, Vector3 *end)
{
	float flSpread, flSpreadX, flSpreadY;

	float flDistance = 8192.f;

	GetWeaponSpread(&flSpread);

	flSpread = tan(flSpread * (M_PI / 180.0f)) * flDistance;

	RandomBulletDir(randSeed, &flSpreadX, &flSpreadY);

	flSpreadX *= flSpread;
	flSpreadY *= flSpread;

	Vector3 ForwardDir, RightDir, UpDir;
	angleVectors(cgArray_s->ViewAngle, &ForwardDir, &RightDir, &UpDir);

	*end = cgArray_s->RefDef.viewOrigin + (ForwardDir * flDistance) + (RightDir * flSpreadX) + (UpDir * flSpreadY);
}

Vector3 ViewPos, SpreadAngle, spreadAng, spreadEndVec;

void _spreadFix(Usercmd_t *cmd)
{
	if (!((InputState.Gamepad.bLeftTrigger / 30) > 0))
	{
		Vector3 spreadEndVec;
		int Seed = cmd->time;
		TransformSeed(&Seed);

		CG_BulletEndpos(Seed, &spreadEndVec);

		spreadEndVec -= cgArray_s->RefDef.viewOrigin;
		Vector3 SpreadFix = vectoangles(spreadEndVec.Normalize());

		cmd->viewAngles[0] += ANGLE2SHORT(cgArray_s->ViewAngle.x - SpreadFix.x);
		cmd->viewAngles[1] += ANGLE2SHORT(cgArray_s->ViewAngle.y - SpreadFix.y);
	}
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