bool CanKillPlayer(int Player, Vector3 PlayerOrigin)
{
	BulletFireParams bp;

	bp.MaxEntNum = 2047;
	bp.ignoreEntIndex = cgArray_s->ClientNumber;
	bp.damageMultiplier = 1.0f;
	bp.methodOfDeath = 1;
	bp.origStart = cgArray_s->RefDef.viewOrigin;
	bp.start = cgArray_s->RefDef.viewOrigin;
	bp.end = PlayerOrigin;

	angleVectors(vectoangles(PlayerOrigin - cgArray_s->RefDef.viewOrigin), &bp.dir, NULL, NULL);

	FireBulletPenetrate(0, &bp, cgArray_s->Weapon, &Centity_s[cgArray_s->ClientNumber], -1, (float*)&cgArray_s->RefDef.viewOrigin, 0);

	return (bp.ignoreEntIndex == Player && bp.damageMultiplier > 1.0f);
}

static bool(__cdecl *BG_AdvancedTrace)(BulletFireParams *bp, BulletTraceResults *br, float dist) = (bool(__cdecl*)(BulletFireParams*, BulletTraceResults *, float))0x820E2A78;

static bool(__cdecl *BulletTrace)(int local, BulletFireParams* bulletFireParams, int weaponDef, BulletTraceResults* bulletTraceResultsype, int lastSurfaceType) = (bool(__cdecl*)(int, BulletFireParams*, int, BulletTraceResults*, int))0x8212E760;

static float(__cdecl *BG_GetSurfacePenetrationDepth)(int penetrateType, int surfaceFlags) = (float(__cdecl*)(int, int))0x820E2178;

static bool(__cdecl *sub_8212EB48)(int localClientNum, BulletFireParams *bp) = (bool(__cdecl*)(int, BulletFireParams*))0x8212EB48;


void R_FireBulletPenetrate(BulletFireParams* bp, unsigned int weaponIndex, pCentity_t attacker, int enemyID)
{
	bool hasBulletPenetration = (*(int*)((int)cgArray_s + 0x428) & 32) != 0;
	bool v13, traceHit;
	
	int weaponDef = BG_GetWeaponDef(weaponIndex);
	int weaponVariantDef = BG_GetWeaponVariantDef(weaponIndex);

	BulletTraceResults br;
	bool firstTrace = BulletTrace(0, bp, weaponDef, &br, 0);

	if (!firstTrace)
		return;

	float weaponPenetration = *(float*)(*(int*)(0x82557750 + (attacker->WeaponID * 4)) + 0x30);
	float bulletPenetrationMult = *(float*)(*(int*)(0x82557554) + 8);

	for (int i = 0; i < 12; i++)
	{
		float maxDepth = BG_GetSurfacePenetrationDepth(weaponDef, br.depthSurfaceType) * weaponPenetration;

		if (hasBulletPenetration)
			maxDepth *= bulletPenetrationMult;

		if (maxDepth <= 0.0f)
			return;

		Vector3 lastHitPos = br.hitPos;

		if (!BG_AdvancedTrace(bp, &br, 0.13500001f))
			return;

		traceHit = BulletTrace(0, bp, weaponDef, &br, br.depthSurfaceType);

		BulletFireParams revBp = *bp;

		revBp.dir = -bp->dir;
		revBp.start = bp->end;
		revBp.end = revBp.dir * 0.0099999998f + lastHitPos;

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
			float newDepth = BG_GetSurfacePenetrationDepth(weaponDef, revBr.depthSurfaceType);

			if (hasBulletPenetration)
				newDepth *= bulletPenetrationMult;

			maxDepth = min(maxDepth, newDepth) * weaponPenetration;

			if (maxDepth <= 0.0f)
				return;

			bp->damageMultiplier -= depth / maxDepth;

			if (bp->damageMultiplier <= 0.0f)
				return;
		}

		else if (traceHit)
			break;

		if (v13)
			continue;
	}
}

bool EntityWall(int cent, Vector3 vieworg, Vector3 PlayerOrigin, SHORT Bone) {
	if (Aimtarget_isTargetVisible(0, &Centity_s[cent], Bone))
		return true;

	BulletFireParams bp;

	bp.MaxEntNum = 2047;
	bp.ignoreEntIndex = cgArray_s->ClientNumber;
	bp.damageMultiplier = 1.0f;
	bp.methodOfDeath = 1;
	bp.origStart = cgArray_s->RefDef.viewOrigin;
	bp.start = cgArray_s->RefDef.viewOrigin;
	bp.end = PlayerOrigin;
	angleVectors(vectoangles(PlayerOrigin - cgArray_s->RefDef.viewOrigin), &bp.dir, NULL, NULL);

	*(long long*)0x82134510 = 0x386000014E800020;
	*(long long*)0x821A4A58 = 0x386000014E800020;
	*(long long*)0x8212EB48 = 0x386000014E800020;
	FireBulletPenetrate(0, &bp, cgArray_s->Weapon, &Centity_s[cgArray_s->ClientNumber], -1, (float*)&cgArray_s->RefDef.viewOrigin, 0);
	*(long long*)0x82134510 = 0x7D8802A64826F1C1;
	*(long long*)0x821A4A58 = 0x7D8802A6481FEC7D;
	*(long long*)0x8212EB48 = 0x7D8802A69181FFF8;
	//R_FireBulletPenetrate(&bp, cgArray_s->ClientInfo[cgArray_s->ClientNumber].Weapon, &Centity_s[cgArray_s->ClientNumber], cent);
	return bp.ignoreEntIndex == cent;
}

BOOL BoneVisible(pCentity_t ent, int tag) {
	return Aimtarget_isTargetVisible(0, ent, tag);
}

BOOL GetVisibleBone(DWORD Target, SHORT DefaultBox, Vector3 *_out = NULL)
{
	if (BoneVisible(&Centity_s[Target], DefaultBox)) {
		*_out = GetTagPos(Target, NULL, DefaultBox, true);
		return TRUE;
	}

	return FALSE;
}

BOOL ValidBone(DWORD Target, SHORT Bone) {
	return EntityWall(Target, cgArray_s->RefDef.viewOrigin, GetTagPos(Target, NULL, Bone), Bone);
}

float CG_GoodRandomFloat(int *pHoldrand)
{
	unsigned int r11 = 214013 * *pHoldrand + 2531011;
	*pHoldrand = r11;
	return (r11 >> 17) * 0.000030517578;
}

void RandomBulletDir(int randSeed, float *x, float *y)
{
	float f26 = (CG_GoodRandomFloat(&randSeed) * 360.0f) * 0.01745329998474369f;
	float f28 = CG_GoodRandomFloat(&randSeed);
	*x = f28 * cos(f26); // sin
	*y = f28 * sin(f26); // cos
}

BOOL GetBone(DWORD Target, SHORT DefaultBox, Vector3 *_out) {
	if (ValidBone(Target, DefaultBox)) {
		*_out = GetTagPos(Target, NULL, DefaultBox, true);
		return TRUE;
	}

	if (!bMultiBox)
		return FALSE;

	if (Target && ClosestPlayer != -1) {
		for (int i = 0; i < 4; i++) {
			if (ValidBone(Target, multiBox[i])) {
				if (BulletTrace || R_FireBulletPenetrate || FireBulletPenetrate || CG_LocationalTrace || BG_AdvancedTrace) {
					*_out = GetTagPos(Target, NULL, multiBox[i]);
					return TRUE;
				}
			}
		}

		if (bPlayerPriority[Target]) {
			for (int i = 0; i < 25; i++) {
				if (ValidBone(Target, multiBox[i])) {
					*_out = GetTagPos(Target, NULL, multiBox[i]);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
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

/*
const char* CloseToMe()
{
	Vector3 _Temp;

	for (int i = 0; i < 18; i++)
	{
		if (i == cgArray_s->ClientNumber)
			continue;

		if (!isEntityPlayer(i))
			continue;

		if (!IsEnemy(i))
			continue;

		if (GetDistance(GetPlayerOrigin(i), cgArray_s->RefDef.viewOrigin) < 10)
		{
			if (GetVisibleBone(i, SL_GetString("j_spineupper", 0), &_Temp))
			{
				return "j_spineupper";
			}
		}
		else
		{
			return GetTagPos(i, NULL, multiBox[i]);
		}
		return "j_spineupper";
	}
}
*/

DWORD GetTarget(Vector3 *vecOut) {
	if (aimEvent == 2) {
		if (!GetAsyncKeyState(0x1337))
			return -1;
	}

	if (aimEvent == 3) {
		if (!GetAsyncKeyState(0x1338))
			return -1;
	}

	bool bVisible = isAnyVis(cgArray_s->ClientNumber);

	DWORD dwReturnIndex = -1;
	FLOAT flClosest = 8192.0f;

	Vector3 _Temp, _Return;

	SHORT aimTag = SL_GetString(aimBone, 0);

	for (int i = 0; i < 18; i++) {
		if (i == cgArray_s->ClientNumber)
			continue;

		if (!isEntityPlayer(i))
			continue;

		if ((!IsEnemy(i) && !bPlayerPriority[i]) || bPlayerFriendly[i])
			continue;

		if (aimEvent == 0) {
			if (!GetBone(i, aimTag, &_Temp))
				continue;
		}

		if (aimEvent == 1) {
			if (!GetVisibleBone(i, aimTag, &_Temp))
				continue;
		}

		if (bLegitbot) {
			if (!Aimtarget_isTargetVisible(0, &Centity_s[i], aimTag, &_Temp))
				continue;

			Vector2 ScreenPos;
			if (WorldToScreen(GetTagPos(i, aimBone), &ScreenPos.x, &ScreenPos.y))
			{
				if (!(
					//ScreenPos.x > ((cgArray_s->RefDef.Width / 2) - (fFOVSize / 2)) &&
					ScreenPos.x < ((cgArray_s->RefDef.Width / 2) + (fFOVSize / 2)) &&
					ScreenPos.y > ((cgArray_s->RefDef.Height / 2) - (fFOVSize / 2)) &&
					ScreenPos.y < ((cgArray_s->RefDef.Height / 2) + (fFOVSize / 2))
					))
					continue;
			}
			else
				continue;
		}

		FLOAT flDistance = bPlayerPriority[i] ? 6.5f : GetDistance(Centity_s[i].Origin, Centity_s[cgArray_s->ClientNumber].Origin);
		
		if (!bVisible || Aimtarget_isTargetVisible(0, &Centity_s[i], aimTag) || bPlayerPriority[i]) {
			if (flDistance < flClosest) {
				_Return = _Temp;
				dwReturnIndex = i;
				flClosest = flDistance;
			}
		}
	}

	*vecOut = _Return;

	return dwReturnIndex;
}

const char* riotbonehandler()
{
	static bool shield;
	shield = !shield;

	if (shield)
	{
		return "j_knee_ri";
	}
	return "j_ankle_le";
	{
		return "j_knee_le";
	}
	return "j_ankle_ri";
	{
		return "j_ankle_le";
	}
	return "j_ball_ri";
	{
		return "j_ball_le";
	}
}

void _Aimbot()
{
	if (!isEntityPlayer(cgArray_s->ClientNumber)) return;

	ClientActive->viewAngle.z = (vectoangles(Vector3(1, 1, 1) - cgArray_s->RefDef.viewOrigin) - ClientActive->baseAngle).z;

	if (ResetAngles && ClosestPlayer == -1) {
		ClientActive->viewAngle = OldAngles;
		ResetAngles = false;
	}

	Vector3 _vOutPos;

	if (bRagebot || bLegitbot) {
		ClosestPlayer = GetTarget(&_vOutPos);

		if (ClosestPlayer == -1) {
			bFirstBezierSet = false;
			bBezierSeedSet = false;
			return;
		}

		if (!bBezierSeedSet) {
			dwBezierSeed = cgArray_s->Servertime;
			bBezierSeedSet = true;
		}

		Position = bPlayerBodyAim[ClosestPlayer] ? GetTagPos(ClosestPlayer, "j_head", true) : _vOutPos;

		Position = (bShieldEquipped(ClosestPlayer)) ? GetTagPos(ClosestPlayer, riotbonehandler()) : Position;

		if (bPrediction)
			PosPrediction(&Centity_s[ClosestPlayer], Position, fPrediction, true);

		FinalAngles = vectoangles(Position - cgArray_s->RefDef.viewOrigin) - ClientActive->baseAngle;

		if ((!bSilent || bPlayerPriority[ClosestPlayer]))
		{
			if (bSnapback && !ResetAngles) {
				OldAngles = ClientActive->viewAngle;
				ResetAngles = true;
			}

			ClientActive->viewAngle = FinalAngles;
		}

		/*
		if (bSnap && (!bSilent || bPlayerPriority[ClosestPlayer])) 
		{
			if (bSnapback && !ResetAngles) {
				OldAngles = ClientActive->viewAngle;
				ResetAngles = true;
			}

			ClientActive->viewAngle = FinalAngles;
		}
		*/

		if (bLegitbot)
			_SmoothAngle(FinalAngles, ClientActive->viewAngle, fAimSpeed);
	}
}

void GetWeaponSpread(float*Spread)
{
	float SpreadMultiplier = cgArray_s->SpreadMultiplier;
	float WeaponSpread = 0.0f;
	float BaseSpread = 0.0f;

	int iLocalWeapon = BG_GetWeaponDef(cgArray_s->Weapon);
	BG_GetSpreadForWeapon(cgArray_s, iLocalWeapon, &WeaponSpread, &BaseSpread);
	*Spread = (WeaponSpread + ((BaseSpread - WeaponSpread) * (SpreadMultiplier * 0.00399956862f))); //0.00399956862f
}

void CG_BulletEndpos(int randSeed, Vector3 *end)
{
	float flSpread, flSpreadX, flSpreadY;

	float flDistance = 8192.f;

	GetWeaponSpread(&flSpread);

	flSpread = tan(flSpread * 0.01795329998474369f) * flDistance;

	RandomBulletDir(randSeed, &flSpreadX, &flSpreadY);

	flSpreadX *= flSpread;
	flSpreadY *= flSpread;

	Vector3 ForwardDir, RightDir, UpDir;
	angleVectors(cgArray_s->ViewAngle, &ForwardDir, &RightDir, &UpDir);

	*end = cgArray_s->RefDef.viewOrigin + (ForwardDir * flDistance) + (RightDir * flSpreadX) + (UpDir * flSpreadY);
}

//Vector3 ViewPos, SpreadAngle, spreadAng, spreadEndVec;

//static void(__cdecl *_CG_BulletEndPos)(int* randSeed, const float spread, Vector3 *start, Vector3 *end, Vector3 *dir, Vector3 *forwardDir, Vector3 *rightDir, Vector3 *upDir, const float maxRange) = (void(__cdecl*)(int*, const float, Vector3*, Vector3 *, Vector3 *, Vector3 *, Vector3 *, Vector3 *, const float))0x8212F000;

void _spreadFix(Usercmd_t *cmd)
{
	if (cgArray_s->RefDef.flZoomProgress < 1.0f) {
		int Seed = cgArray_s->Servertime - 1;

		TransformSeed(&Seed);

		float Spread;
		GetWeaponSpread(&Spread);

		Vector2 flSpread;

		RandomBulletDir(Seed, &flSpread.x, &flSpread.y);

		cmd->viewAngles[0] += ANGLE2SHORT(flSpread.y * Spread);
		cmd->viewAngles[1] += ANGLE2SHORT(flSpread.x * Spread);
	}
}