bool BoneVisible(Centity_t ent, char *tag)
{
	return Aimtarget_isTargetVisible(0, &ent, SL_GetString(tag, 0));
}

void GetViableBone(int Client, Vector3 *Out = NULL, bool *FoundBone = NULL)
{
	Centity_t e = Centity_s[Client];

	if (BoneVisible(e, "j_head") && BoneVisible(e, "j_ankle_le")) {
		if (Out != NULL)
			*Out = GetTagPos(ClosestPlayer, aimBone, true);

		return;
	}


	for (int i = 0; i < 14; i++)
	{
		if (BoneVisible(e, BO1HitBoxes[i]))
		{
			if (Out != NULL)
				*Out = GetTagPos(ClosestPlayer, BO1HitBoxes[i], true);

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

bool CanKillPlayer(int Target)
{
	Vector3 PlayerOrigin;
	Vector3 Pos = GetTagPos(Target, "j_head");

	BulletFireParams bullet;
	BulletTraceResults bulletTrace;

	bullet.weaponEntIndex = 0x3FE;
	bullet.ignoreEntIndex = cgArray_s->ClientNumber;
	bullet.methodOfDeath = 2;
	bullet.damageMultiplier = 1.0f;
	bullet.origStart = cgArray_s->RefDef.viewOrigin;
	bullet.start = cgArray_s->RefDef.viewOrigin;
	bullet.end = Pos;

	angleVectors(vectoangles(PlayerOrigin - cgArray_s->RefDef.viewOrigin), &bullet.dir, NULL, NULL);

	*(int *)0x82223DA8 = 0x4E800020;
	*(int *)0x82292230 = 0x4E800020;

	CG_SimulateBulletFire_Internal(0, &bullet, Centity_s[cgArray_s->ClientNumber].WeaponID, &Centity_s[cgArray_s->ClientNumber], (float*)&cgArray_s->RefDef.viewOrigin, 0, 1, &bulletTrace);

	*(int*)0x82223DA8 = 0x7D8802A6;
	*(int*)0x82292230 = 0x7D8802A6;

	return (bullet.ignoreEntIndex == Target);
}

int cg_s_2(int Client)
{
	int Value = *(int *)(0x82AD0298);
	if (Value == 0)
		return 0;

	return Value;
}

int cEntity(int Client)
{
	int Value = *(int *)(0x8296808C);
	if (Value == 0)
		return 0;

	return Value;
}

bool DoAutoWallCheck(int OurClient, int Client, float* Endpos)
{
	int weaponDefPtr;
	int cg_s;
	float *MyView;
	int Dir[3];
	int cEnt;
	int OurcEnt;
	int Entity;
	int Weapon;
	byte Byte[0x100];

	BulletFireParams bulletFireParams;

	cg_s = cg_s_2(0);
	MyView = cgArray_s->RefDef.viewOrigin;

	OurcEnt = cEntity(OurClient);
	cEnt = cEntity(Client);

	Entity = OurClient;

	ZeroMemory(&bulletFireParams, sizeof(BulletFireParams));
	//Vector3 &angles, Vector3 *forward, Vector3 *right, Vector3 *up

	Weapon = *(short *)(cg_s + 0x14C);
	weaponDefPtr = ((int(*)(int))0x821919D8)(Weapon);

	bulletFireParams.weaponEntIndex = 0x3FE;
	bulletFireParams.ignoreEntIndex = Entity;
	bulletFireParams.damageMultiplier = 1.0f;
	bulletFireParams.methodOfDeath = 1;

	VectorCopy(MyView, bulletFireParams.origStart);
	VectorCopy(MyView, bulletFireParams.start);
	VectorCopy(Endpos, bulletFireParams.end);

	VectorSubtract(Endpos, MyView, Dir);
	
	Vector3 Direction;
	Direction.x = Dir[0];
	Direction.y = Dir[1];
	vectoangles2(Direction, Direction);

	angleVectors((Vector3)Direction, &bulletFireParams.dir, NULL, NULL);

	//stop the bullet effects and sounds
	*(int*)0x82223DA8 = 0x4E800020;
	*(int*)0x82292230 = 0x4E800020;

	//FireBulletPenetrate
	((void(*)(...))0x822252F8)(0, &bulletFireParams, Weapon, OurcEnt, MyView, 0, 1, Byte);

	//restore them
	*(int*)0x82223DA8 = 0x7D8802A6;
	*(int*)0x82292230 = 0x7D8802A6;

	return bulletFireParams.ignoreEntIndex == Client;
}

bool EntityWall(int i) {
	return CanKillPlayer(i);
}

bool isAnyVis(int mClient)
{
	for (int i = 0; i < 18; i++)
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

void GetWeaponSpread(float* Spread)
{
	float SpreadMultiplier = cgArray_s->SpreadMultiplier;

	float WeaponSpread = 0.0f;
	float BaseSpread = 0.0f;

	int iLocalWeapon = BG_GetWeaponDef(Centity_s[cgArray_s->ClientNumber].WeaponID);
	BG_GetSpreadForWeapon((*(int*)(0x82964EA0)) + 0x3EF9C, iLocalWeapon, &WeaponSpread, &BaseSpread);
	*Spread = (WeaponSpread + ((BaseSpread - WeaponSpread) * (SpreadMultiplier / 255.0f)));
}

Vector3 ViewPos, SpreadAngle, spreadAng, spreadEndVec;

void _spreadFix(Usercmd_t *cmd)
{
	if (!GetAsyncKeyState(0x1337))
	{
		cgArray_t* cgArray = *(cgArray_t**)0x82964EA0;

		Vector3 ViewAxis[3];

		angleVectors(cgArray->ViewAngle, &ViewAxis[0], &ViewAxis[1], &ViewAxis[2]);

		Vector3  EndVec, vAngles, Var, SpreadV;

		int ServerTime = *(int*)((*(int*)(0x82964EA0)) + 0x3EF9C);

		float Spread;
		GetWeaponSpread(&Spread);

		Vector3 View;
		CG_BulletEndPos(ServerTime, Spread, &cgArray->RefDef.viewOrigin, &EndVec, &View, &ViewAxis[0], &ViewAxis[1], &ViewAxis[2], 8192.0f);

		Vector3 SpreadFix = vectoangles(View);

		cmd->viewAngles[0] -= ANGLE2SHORT(-(cgArray->ViewAngle.x - SpreadFix.x));
		cmd->viewAngles[1] -= ANGLE2SHORT(-(cgArray->ViewAngle.y - SpreadFix.y));
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