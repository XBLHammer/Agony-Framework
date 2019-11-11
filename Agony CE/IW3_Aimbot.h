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

bool CanKillPlayer(int Player, Vector3 PlayerOrigin)
{
	BulletFireParams bp;

	bp.MaxEntNum = 1022;
	bp.ignoreEntIndex = cgArray_s->ClientNumber;
	bp.damageMultiplier = 1.0f;
	bp.methodOfDeath = 2;
	bp.origStart = cgArray_s->RefDef.viewOrigin;
	bp.start = cgArray_s->RefDef.viewOrigin;
	bp.end = PlayerOrigin;

	angleVectors(vectoangles(PlayerOrigin - cgArray_s->RefDef.viewOrigin), &bp.dir, NULL, NULL);

	FireBulletPenetrate(0, &bp, BG_GetWeaponDef(Centity_s[cgArray_s->ClientNumber].WeaponID), &Centity_s[cgArray_s->ClientNumber], (float*)&cgArray_s->RefDef.viewOrigin, 0);

	return (bp.ignoreEntIndex == Player && bp.damageMultiplier > 0.0f);
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
			if (!Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString(aimBone, 0)) && !CanKillPlayer(i, GetTagPos(i, aimBone)))
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

bool bFirstTele;

void _Aimbot()
{
	if (!isEntityPlayer(cgArray_s->ClientNumber)) return;

	if (ResetAngles && ClosestPlayer == -1)
	{
		ClientActive->viewAngle = OldAngles;
		ResetAngles = false;
	}

	Vector3 MyPos = Vector3(1, 1, 1);
	Vector3 MyAng = vectoangles(MyPos - cgArray_s->RefDef.viewOrigin) - ClientActive->baseAngle;

	ClientActive->viewAngle.z = MyAng.z;

	ClosestPlayer = GetNearestPlayer(cgArray_s->ClientNumber);

	if (ClosestPlayer == -1) {
		bFirstBezierSet = false;
		bBezierSeedSet = false;
		return;
	}

	if (!bBezierSeedSet) {
		dwBezierSeed = GetTickCount();
		bBezierSeedSet = true;
	}

	Position = GetTagPos(ClosestPlayer, !bPlayerBodyAim[ClosestPlayer] ? aimBone : "j_spine4", true);

	if (bMultiBox)
		GetViableBone(ClosestPlayer, &Position);

	if (bPrediction)
		PosPrediction(&Centity_s[ClosestPlayer], Position, fPrediction, true);

	FinalAngles = vectoangles(Position - cgArray_s->RefDef.viewOrigin) - ClientActive->baseAngle;

	if (bRagebot && !bSilent) {
		if (bSnapback && !ResetAngles) {
			OldAngles = ClientActive->viewAngle;
			ResetAngles = true;
		}

		ClientActive->viewAngle = FinalAngles;
	}

	if (bLegitbot)
		_SmoothAngle(FinalAngles, ClientActive->viewAngle, fAimSpeed);
}

static void(__cdecl*RandomBulletDir)(int randSeed, float *x, float *y) = (void(__cdecl *)(int randSeed, float *x, float *y))0x822E9758;

void GetWeaponSpread(float*Spread)
{
	float SpreadMultiplier = cgArray_s->SpreadMultiplier;
	int PlayerState = *(int*)(0x823F28A0) + 0x44744;

	//printf("PlayerState: %#08x\n", PlayerState);

	float WeaponSpread = 0.0f;
	float BaseSpread = 0.0f;

	int iLocalWeapon = BG_GetWeaponDef(Centity_s[cgArray_s->ClientNumber].WeaponID);
	BG_GetSpreadForWeapon(PlayerState, iLocalWeapon, &WeaponSpread, &BaseSpread);
	*Spread = (WeaponSpread + ((BaseSpread - WeaponSpread) * (SpreadMultiplier / 255.0f)));
}

static void(__cdecl *CG_BulletEndPos)(int randSeed, const float spread, Vector3 *start, Vector3 *end, Vector3 *dir, Vector3 *forwardDir, Vector3 *rightDir, Vector3 *upDir, const float maxRange) = (void(__cdecl*)(int, const float, Vector3*, Vector3 *, Vector3 *, Vector3 *, Vector3 *, Vector3 *, const float))0x822E9D70;

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
	if (!GetAsyncKeyState(0x1337))
	{
		Vector3 ViewAxis[3];

		angleVectors(cgArray_s->ViewAngle, &ViewAxis[0], &ViewAxis[1], &ViewAxis[2]);

		Vector3  EndVec, vAngles, Var, SpreadV;

		int ServerTime = cgArray_s->playerState.Servertime;

		float Spread;
		GetWeaponSpread(&Spread);

		Vector3 View;
		CG_BulletEndPos(ServerTime, Spread, &cgArray_s->RefDef.viewOrigin, &EndVec, &View, &ViewAxis[0], &ViewAxis[1], &ViewAxis[2], 8192.0f);

		Vector3 SpreadFix = vectoangles(View);

		DbgPrint("%f, %f\n", SpreadFix.x, SpreadFix.y);

		cmd->viewAngles[0] += ANGLE2SHORT(cgArray_s->ViewAngle.x - SpreadFix.x);
		cmd->viewAngles[1] += ANGLE2SHORT(cgArray_s->ViewAngle.y - SpreadFix.y);
	}
}