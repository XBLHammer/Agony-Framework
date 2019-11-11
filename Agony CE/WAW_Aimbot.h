bool BoneVisible(Centity_t ent, char *tag) {
	return Aimtarget_isTargetVisible(0, &ent, SL_GetString(tag, 0));
}

void GetViableBone(int Client, Vector3 *Out = NULL, bool *FoundBone = NULL)
{
	Centity_t e = Centity_s[Client];

	if (BoneVisible(e, aimBone)) {
		if (Out != NULL)
			*Out = GetTagPos(Client, aimBone, true);

		return;
	}
	
	for (int i = 0; i < 14; i++) {
		if (BoneVisible(e, BO1HitBoxes[i])) {
			if (Out != NULL)
				*Out = GetTagPos(Client, BO1HitBoxes[i], true);

			if (FoundBone != NULL)
				*FoundBone = true;

			return;
		}
	}

	if (Out != NULL)
		*Out = GetTagPos(Client, aimBone, true);

	if (FoundBone != NULL)
		*FoundBone = false;
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

		if (!Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString("j_head", 0)))
			continue;

		return true;
	}
	return false;
}

struct BulletFireParams
{
	int weaponEntIndex;
	int ignoreEntIndex;
	float damageMultiplier;
	int methodOfDeath;
	Vector3 origStart;
	Vector3 start;
	Vector3 end;
	Vector3 dir;
}; // 0x40

//8219F6D0
static void(__cdecl *CG_SimulateBulletFire_Internal)(int localClientNum, BulletFireParams* bp, int weaponIndex, pCentity_t attacker, float* Coords, int drawTracer, int isPlayer) = (void(__cdecl *)(int, BulletFireParams*, int, pCentity_t, float*, int, int))0x8219F6D0;

bool CanKillPlayer(int Target) {
	Vector3 Pos = GetTagPos(Target, "j_head");

	BulletFireParams bullet;

	bullet.weaponEntIndex = 1022;
	bullet.ignoreEntIndex = cgArray_s->ClientNumber;
	bullet.methodOfDeath = 1;
	bullet.damageMultiplier = 1.0f;

	bullet.start = cgArray_s->RefDef.viewOrigin;
	bullet.origStart = cgArray_s->RefDef.viewOrigin;
	bullet.end = Pos;

	Vector3 subs = Pos - cgArray_s->RefDef.viewOrigin;
	subs = vectoangles(subs);
	angleVectors(subs, &bullet.dir, NULL, NULL);

	CG_SimulateBulletFire_Internal(0, &bullet, BG_GetWeaponDef(Centity_s[cgArray_s->ClientNumber].WeaponID), &Centity_s[cgArray_s->ClientNumber], (float*)&cgArray_s->RefDef.viewOrigin, 0, 1);

	return (bullet.ignoreEntIndex == Target);
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
			if (!CanKillPlayer(i))
				continue;
		}
		else if (aimEvent == 1) {
			if (!Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString("j_head", 0)))
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
			if (!Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString("j_head", 0)))
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
		bool ID_Vis = Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString("j_head", 0));

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

	//if (bMultiBox)
	//	GetViableBone(ClosestPlayer, &Position);

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

void GetWeaponSpread(float* Spread)
{
	float SpreadMultiplier = cgArray_s->SpreadMultiplier;

	float WeaponSpread = 0.0f;
	float BaseSpread = 0.0f;

	int iLocalWeapon = BG_GetWeaponDef(cgArray_s->WeaponID);
	BG_GetSpreadForWeapon(&cgArray_s->playerState, iLocalWeapon, &WeaponSpread, &BaseSpread);
	*Spread = (WeaponSpread + ((BaseSpread - WeaponSpread) * (SpreadMultiplier / 255.0f)));
}

Vector3 ViewPos, SpreadAngle, spreadAng, spreadEndVec;

void _spreadFix(Usercmd_t *cmd)
{
	if (!GetAsyncKeyState(0x1337))
	{
		cmd->buttons &= ~0x00080001;
		Vector3 ViewAxis[3];

		angleVectors(cgArray_s->ViewAngle, &ViewAxis[0], &ViewAxis[1], &ViewAxis[2]);

		Vector3  EndVec, vAngles, Var, SpreadV;

		int ServerTime = cgArray_s->playerState.Command;

		float Spread;
		GetWeaponSpread(&Spread);

		Vector3 View;
		CG_BulletEndPos(ServerTime, Spread, &cgArray_s->RefDef.viewOrigin, &EndVec, &View, &ViewAxis[0], &ViewAxis[1], &ViewAxis[2], 8192.0f);

		Vector3 SpreadFix = vectoangles(View);

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