Vector2 RadarCenter, Center;

int RadarSize = 175;

void _Radar()
{
	Center.x = cgArray_s->RefDef.Width / 2;
	Center.y = cgArray_s->RefDef.Height / 2;
	RadarCenter.x = (Center.x * 2) - RadarSize - 40;
	RadarCenter.y = RadarSize / 2 + 25;

	DrawShader(RadarCenter.x - RadarSize, RadarCenter.y - RadarSize / 2, RadarSize * 2, RadarSize, defaultShader, "white");

	DrawLine(RadarCenter.x - RadarSize / 2, RadarCenter.y - RadarSize / 2, RadarCenter.x, RadarCenter.y, radarLine, Material_RegisterHandle("white", 0), 1);
	DrawLine(RadarCenter.x + RadarSize / 2, RadarCenter.y - RadarSize / 2, RadarCenter.x, RadarCenter.y, radarLine, Material_RegisterHandle("white", 0), 1);

	DrawShader(RadarCenter.x - RadarSize, RadarCenter.y, RadarSize * 2, 1, radarLine, "white"); // horz
	DrawShader(RadarCenter.x, RadarCenter.y - RadarSize / 2, 1, RadarSize, radarLine, "white"); // vert

	float healthHeight = cgArray_s->Health * 1.75;

	DrawShader(RadarCenter.x - RadarSize - 4, RadarCenter.y - RadarSize / 2, 2, 175, colSHADER, "white");
	DrawShader(RadarCenter.x - RadarSize - 4, (175 - healthHeight) + RadarCenter.y - RadarSize / 2, 2, healthHeight, colGREEN, "white");

	for (int i = 0; i < 2048; i++)
	{
		int Type = Centity_s[i].Type;

		if (Type != ET_PLAYER && Type != ET_MISSLE && Type != ET_ITEM)
			continue;

		int Shader;

		float *color = defaultEnemy;
		if (Type == ET_PLAYER) {
			if (!isEntityPlayer(i))
				continue;

			Shader = Material_RegisterHandle("cb_compassping_arrow", 0);

			if (i != cgArray_s->ClientNumber) {
				bool iEnemy = IsEnemy(i);
				if (!((bRadarAxis && iEnemy) || (bRadarAlly && !iEnemy)))
					continue;


				Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString("j_head", 0)) ? color = defaultVisible : color;
				!iEnemy ? color = defaultFriend : color;
				bPlayerPriority[i] ? color = colorPurpleTrans : color;
				bPlayerFriendly[i] ? color = colorCyanTrans : color;
				i == ClosestPlayer ? color = defaultTarget : color;
			}
			else {
				color = colorCyanTrans;
			}
		}

		if (Type == ET_ITEM) {
			if (!bRadarEntity)
				continue;

			if (!(Centity_s[i].Alive & 1))
				continue;

			int WeaponID = Centity_s[i].WeaponID;

			color = colorWhiteTrans;

			if (WeaponID <= 0)
				continue;

			int dwTempShader = GetWeaponShader(WeaponID);
			if (dwTempShader)
				Shader = dwTempShader;

		}

		if (Type == ET_MISSLE) {
			if (!bRadarEntity)
				continue;

			if (!(Centity_s[i].Alive & 4))
				continue;

			color = colorYellowTrans;
		}

		int RadarX, RadarY;

		RadarX = GetPlayerOrigin(cgArray_s->ClientNumber).x - GetPlayerOrigin(i).x;
		RadarY = GetPlayerOrigin(cgArray_s->ClientNumber).y - GetPlayerOrigin(i).y;

		float Angle = cgArray_s->ViewAngle.y / 180 * 3.141;

		float RotateX = RadarY * cosf(Angle) - RadarX * sinf(Angle);
		float RotateY = RadarX * cosf(Angle) + RadarY * sinf(Angle);

		float FinalX = RadarCenter.x + RotateX / fRadarDist;
		float FinalY = RadarCenter.y + RotateY / fRadarDist;

		if (FinalX < RadarCenter.x - RadarSize) FinalX = (RadarCenter.x - RadarSize) + 2;
		if (FinalY < RadarCenter.y - RadarSize / 2) FinalY = (RadarCenter.y - RadarSize / 2) + 2;

		if (FinalX > RadarCenter.x + RadarSize) FinalX = (RadarCenter.x + RadarSize) - 2;
		if (FinalY > RadarCenter.y + RadarSize / 2) FinalY = (RadarCenter.y + RadarSize / 2) - 2;

		if (Type == ET_MISSLE)
			DrawShader(FinalX - 2, FinalY - 2, 4, 4, color, "white");
		else
			CG_DrawRotatedPicPhysical(0x82B94570, FinalX - 10, FinalY - 10, 20, 20, (i == cgArray_s->ClientNumber || Type == ET_ITEM) ? 0 : (cgArray_s->ViewAngle.y - Centity_s[i].viewAngle.y), color, Shader);
	}
}

Vector2 cCenter;

void _Compass()
{
	cCenter.x = cgArray_s->RefDef.Width / 2;
	cCenter.y = cgArray_s->RefDef.Height / 2;

	for (int i = 0; i < 2048; i++)
	{
		int Type = Centity_s[i].Type;

		if (Type != ET_PLAYER && Type != ET_ITEM)
			continue;

		int Shader, dwWidth, dwHeight;

		float *color = colWHITE;
		if (Type == ET_PLAYER) {
			if (!isEntityPlayer(i))
				continue;

			if (i == cgArray_s->ClientNumber)
				continue;

			dwWidth = 30; dwHeight = 30;
			Shader = Material_RegisterHandle("cb_compassping_arrow", 0);

			bool iEnemy = IsEnemy(i);
			if (!((bCompassAxis && iEnemy) || (bCompassAlly && !iEnemy)))
				continue;

			color = defaultEnemy;

			Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString("j_head", 0)) ? color = defaultVisible : color;
			!iEnemy ? color = defaultFriend : color;
			bPlayerPriority[i] ? color = colorPurpleTrans : color;
			bPlayerFriendly[i] ? color = colorCyanTrans : color;
			i == ClosestPlayer ? color = defaultTarget : color;
		}

		if (Type == ET_ITEM) {
			if (!bCompassEntity)
				continue;

			if (!(Centity_s[i].Alive & 1))
				continue;

			int WeaponID = Centity_s[i].WeaponID;

			if (WeaponID <= 0)
				continue;

			dwWidth = 40; dwHeight = 20;

			int dwTempShader = GetWeaponShader(WeaponID);
			if (dwTempShader)
				Shader = dwTempShader;

		}

		int RadarX, RadarY;

		RadarX = GetPlayerOrigin(cgArray_s->ClientNumber).x - GetPlayerOrigin(i).x;
		RadarY = GetPlayerOrigin(cgArray_s->ClientNumber).y - GetPlayerOrigin(i).y;

		float Angle = cgArray_s->ViewAngle.y / 180 * 3.141;

		float RotateX = RadarY * cos(Angle) - RadarX * sin(Angle);
		float RotateY = RadarX * cos(Angle) + RadarY * sin(Angle);

		float FinalX = cCenter.x + RotateX / fRadarDist;
		float FinalY = cCenter.y + RotateY / fRadarDist;

		float angle = atan(RotateX / RotateY) * (180 / M_PI);
		float FinalA = FinalY > cCenter.y ? -angle - 180.0f : -angle;

		if (FinalA < 0)
			FinalA += 360.0f;

		double radians = (M_PI / 180)*(FinalA - 90.0f);
		float CircleX = cCenter.x + (cos(radians) * fCompassSize);
		float CircleY = cCenter.y + (sin(radians) * fCompassSize);

		if (Shader)
			CG_DrawRotatedPicPhysical(0x82B94570, CircleX - dwWidth / 2, CircleY - dwHeight / 2, dwWidth, dwHeight, FinalA, color, Shader);
	}
}


void MakeLines(Vector3 Origin, float X1, float Y1, float Z1, float X2, float Y2, float Z2, float *Color, int Size = 1)
{
	Vector2 Screen1, Screen2;
	Vector3 Origin1(Origin.x + X1, Origin.y + Y1, (Origin.z + Z1) - 5);
	Vector3 Origin2(Origin.x + X2, Origin.y + Y2, (Origin.z + Z2) - 5);
	if (WorldToScreen(Origin1, &Screen1.x, &Screen1.y) && WorldToScreen(Origin2, &Screen2.x, &Screen2.y)) {
		DrawLine(Screen1.x, Screen1.y, Screen2.x, Screen2.y, Color, Material_RegisterHandle("white", 0), Size);
	}
}

float GetBoxWidth(pCentity_t ent) {
	if (ent->Flags & FLAG_PRONE)
		return 35;
	else return 17;
}

float GetBoxHeight(pCentity_t ent) {
	if (ent->Flags & FLAG_PRONE)
		return 25;
	else if (ent->Flags & FLAG_CROUCHED)
		return 55;
	else return 70;
}

void Draw3DBox(int client, float sColor[4])
{
	Vector3 Center = Centity_s[client].Origin;

	float W = GetBoxWidth(&Centity_s[client]), H = GetBoxHeight(&Centity_s[client]);

	//bottom
	MakeLines(Center, -W, -W, 0, -W + (W / 2), -W, 0, sColor, 1);
	MakeLines(Center, W / 2, -W, 0, W, -W, 0, sColor, 1);

	MakeLines(Center, -W, -W, 0, -W, -W + (W / 2), 0, sColor, 1);
	MakeLines(Center, -W, W - (W / 2), 0, -W, W, 0, sColor, 1);

	MakeLines(Center, W, -W + (W / 2), 0, W, -W, 0, sColor, 1);
	MakeLines(Center, W, W - (W / 2), 0, W, W, 0, sColor, 1);

	MakeLines(Center, -W + (W / 2), W, 0, -W, W, 0, sColor, 1);
	MakeLines(Center, W, W, 0, W - (W / 2), W, 0, sColor, 1);

	//middle
	MakeLines(Center, -W, -W, 0, -W, -W, H / 6, sColor, 1);
	MakeLines(Center, -W, -W, H, -W, -W, H - (H / 6), sColor, 1);

	MakeLines(Center, -W, W, 0, -W, W, H / 6, sColor, 1);
	MakeLines(Center, -W, W, H, -W, W, H - (H / 6), sColor, 1);

	MakeLines(Center, W, -W, 0, W, -W, H / 6, sColor, 1);
	MakeLines(Center, W, -W, H, W, -W, H - (H / 6), sColor, 1);

	MakeLines(Center, W, W, 0, W, W, H / 6, sColor, 1);
	MakeLines(Center, W, W, H, W, W, H - (H / 6), sColor, 1);

	//top
	MakeLines(Center, -W, -W, H, -W + (W / 2), -W, H, sColor, 1);
	MakeLines(Center, W / 2, -W, H, W, -W, H, sColor, 1);

	MakeLines(Center, -W, -W, H, -W, -W + (W / 2), H, sColor, 1);
	MakeLines(Center, -W, W - (W / 2), H, -W, W, H, sColor, 1);

	MakeLines(Center, W, -W + (W / 2), H, W, -W, H, sColor, 1);
	MakeLines(Center, W, W - (W / 2), H, W, W, H, sColor, 1);

	MakeLines(Center, -W + (W / 2), W, H, -W, W, H, sColor, 1);
	MakeLines(Center, W, W, H, W - (W / 2), W, H, sColor, 1);

}

void DrawTriBox(int client, float sColor[4])
{
	Vector3 Center = Centity_s[client].Origin;

	float W = GetBoxWidth(&Centity_s[client]), H = GetBoxHeight(&Centity_s[client]);

	W *= 1.5;
	H *= 1.25;

	//bottom
	MakeLines(Center, -W, -W, 0, W, -W, 0, sColor, 1);
	MakeLines(Center, -W, -W, 0, -W, W, 0, sColor, 1);
	MakeLines(Center, W, W, 0, W, -W, 0, sColor, 1);
	MakeLines(Center, W, W, 0, -W, W, 0, sColor, 1);
	//middle
	MakeLines(Center, -W, -W, 0, 0, 0, H, sColor, 1);
	MakeLines(Center, -W, W, 0, 0, 0, H, sColor, 1);
	MakeLines(Center, W, -W, 0, 0, 0, H, sColor, 1);
	MakeLines(Center, W, W, 0, 0, 0, H, sColor, 1);
}

void DrawBoundingBox(Vector3 HeadOrigin, float W, float H, float sColor[4])
{
	MakeLines(HeadOrigin, -W, W, 0, W, W, 0, sColor);
	MakeLines(HeadOrigin, -W, W, 0, -W, W, H, sColor);
	MakeLines(HeadOrigin, W, W, 0, W, W, H, sColor);
	MakeLines(HeadOrigin, -W, W, H, W, W, H, sColor);

	MakeLines(HeadOrigin, -W, W, 0, -W, -W, 0, sColor);
	MakeLines(HeadOrigin, W, -W, 0, W, W, 0, sColor);
	MakeLines(HeadOrigin, W, -W, 0, -W, -W, 0, sColor);
	MakeLines(HeadOrigin, -W, -W, 0, -W, -W, H, sColor);

	MakeLines(HeadOrigin, W, -W, 0, W, -W, H, sColor);
	MakeLines(HeadOrigin, -W, W, H, -W, -W, H, sColor);
	MakeLines(HeadOrigin, W, -W, H, W, W, H, sColor);
	MakeLines(HeadOrigin, W, -W, H, -W, -W, H, sColor);
}


void _ESPClient(int client, float sColor[4])
{
	Vector3 FeetOrigin = GetPlayerOrigin(client);
	Vector3 HeadOrigin = GetTagPos(client, "j_head");
	FeetOrigin.z -= 5;
	HeadOrigin.z += 10;
	Vector2 FeetLocation, HeadLocation;
	if (WorldToScreen(FeetOrigin, &FeetLocation.x, &FeetLocation.y) &&
		WorldToScreen(HeadOrigin, &HeadLocation.x, &HeadLocation.y))
	{
		float fHeight = FeetLocation.y - HeadLocation.y;
		float fWidth;
		if (Centity_s[client].Flags & FLAG_PRONE)
			fWidth = fHeight / 0.9;
		else
			fWidth = fHeight / 1.95;

		int size = 1;

		float fontSize = 0.55;
		char *fontName = "fonts/smallfont";

		float fDistance = GetDistance(GetPlayerOrigin(client), GetPlayerOrigin(cgArray_s->ClientNumber));

		if (cESPType_c == 1) {
			if (bBoxOutline) {
				DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, fWidth, 3, colorBlackTrans, "white"); // top line
				DrawShader((FeetLocation.x - (fWidth / 2)) - 1, FeetLocation.y - 1, fWidth, 3, colorBlackTrans, "white"); // bottom line
				DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - fHeight) + 1, 3, fHeight - 1, colorBlackTrans, "white"); // left line
				DrawShader((FeetLocation.x + (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, 3, fHeight + 3, colorBlackTrans, "white"); // right line
			}

			DrawShader((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - fHeight), fWidth, size, sColor, "white"); // top line
			DrawShader((FeetLocation.x - (fWidth / 2)), FeetLocation.y, fWidth, size, sColor, "white"); // bottom line
			DrawShader((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - fHeight), size, fHeight, sColor, "white"); // left line
			DrawShader((FeetLocation.x + (fWidth / 2)), (FeetLocation.y - fHeight), size, fHeight + size, sColor, "white"); // right line
		}
		else if (cESPType_c == 2) {
			Draw3DBox(client, sColor);
		}
		else if (cESPType_c == 3) {
			if (bBoxOutline) {
				DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, (fWidth / 4) + 2, 3, colBLACK, "white");					// top left line
				DrawShader((FeetLocation.x - (fWidth / 2)) - 1, FeetLocation.y - 1, (fWidth / 4) + 2, 3, colBLACK, "white");								// bottom left line
				DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, 3, (fWidth / 4) + 2, colBLACK, "white");					// left top line
				DrawShader((FeetLocation.x + (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, 3, (fWidth / 4) + 2, colBLACK, "white");					// right top line

				DrawShader((FeetLocation.x + ((fWidth / 2) - (fWidth / 4))) - 1, (FeetLocation.y - fHeight) - 1, (fWidth / 4) + 2, 3, colBLACK, "white");		// top right line
				DrawShader((FeetLocation.x + ((fWidth / 2) - (fWidth / 4))) - 1, FeetLocation.y - 1, (fWidth / 4) + 3, 3, colBLACK, "white");				// bottom right line
				DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - (fWidth / 4)) - 1, 3, (fWidth / 4) + 2, colBLACK, "white");				// left bottom line
				DrawShader((FeetLocation.x + (fWidth / 2)) - 1, (FeetLocation.y - (fWidth / 4)) - 1, 3, (fWidth / 4) + 2, colBLACK, "white");				// right bottom line
			}

			DrawShader((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - fHeight), (fWidth / 4), 1, sColor, "white");					// top left line
			DrawShader((FeetLocation.x - (fWidth / 2)), FeetLocation.y, (fWidth / 4), 1, sColor, "white");								// bottom left line
			DrawShader((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - fHeight), 1, (fWidth / 4), sColor, "white");					// left top line
			DrawShader((FeetLocation.x + (fWidth / 2)), (FeetLocation.y - fHeight), 1, (fWidth / 4), sColor, "white");					// right top line

			DrawShader((FeetLocation.x + ((fWidth / 2) - (fWidth / 4))), (FeetLocation.y - fHeight), (fWidth / 4), 1, sColor, "white");	// top right line
			DrawShader((FeetLocation.x + ((fWidth / 2) - (fWidth / 4))), FeetLocation.y, (fWidth / 4) + 1, 1, sColor, "white");				// bottom right line
			DrawShader((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - (fWidth / 4)), 1, (fWidth / 4), sColor, "white");				// left bottom line
			DrawShader((FeetLocation.x + (fWidth / 2)), (FeetLocation.y - (fWidth / 4)), 1, (fWidth / 4), sColor, "white");				// right bottom line
		}
		else if (cESPType_c == 4) {
			DrawShader((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - fHeight), fWidth, fHeight, sColor, "white"); //top

			float size = bBoxOutline ? 1 : 2;
			float *oColor = bBoxOutline ? colBLACK : sColor;

			DrawShader((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - fHeight), fWidth, size, oColor, "white"); // top line
			DrawShader((FeetLocation.x - (fWidth / 2)), FeetLocation.y, fWidth, size, oColor, "white"); // bottom line
			DrawShader((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - fHeight), size, fHeight, oColor, "white"); // left line
			DrawShader((FeetLocation.x + (fWidth / 2)), (FeetLocation.y - fHeight), size, fHeight + size, oColor, "white"); // right line
		}
		else if (cESPType_c == 5)
			DrawTriBox(client, sColor);

		if (bDrawLines)
			DrawLine(FeetLocation.x, FeetLocation.y, cgArray_s->RefDef.Width / 2, cgArray_s->RefDef.Height - 30, sColor, Material_RegisterHandle("white", 0), 1);

		if (bDrawWeapon) {
			int Shader = GetWeaponShader(Centity_s[client].WeaponID);
			if (Shader) {
				CG_DrawRotatedPicPhysical(0x82B94570, FeetLocation.x - 30, FeetLocation.y, 60, 30, 0, colWHITE, Shader);
			}
		}

		if (bDrawName) {
			char *clientName = cgArray_s->ClientInfo[client].Name;
			char _dist[128];
			_snprintf(_dist, 128, "[%.1fm]", fDistance);

			SetTextCenteredWithBackGround(clientName, fontName, FeetLocation.x, HeadLocation.y - 3, fontSize, fontSize, colWHITE, colSHADER, false);
			SetTextCenteredWithBackGround(_dist, fontName, FeetLocation.x, HeadLocation.y - 3 - (TextHeight(fontName) * fontSize), fontSize, fontSize, colWHITE, colSHADER, false);
		}
	}
}

void DrawBoneLine(pCentity_t entity, int ent, const char* tagname1, const char* tagname2, float *col)
{
	Vector3 Origin1 = GetTagPos(ent, tagname1), Origin2 = GetTagPos(ent, tagname2);

	Vector2 Loc1, Loc2;
	if (WorldToScreen(Origin1, &Loc1.x, &Loc1.y) && WorldToScreen(Origin2, &Loc2.x, &Loc2.y)) {
		DrawLine(Loc1.x, Loc1.y, Loc2.x, Loc2.y, col, Material_RegisterHandle("white", 0), 1.25);
	}
}

void DoAllBones(int Client, float *boneESPCol)
{
	pCentity_t ent = &Centity_s[Client];

	int entNum = Client;

	//neck
	DrawBoneLine(ent, entNum, "j_head", "j_neck", boneESPCol);

	//left arm
	DrawBoneLine(ent, entNum, "j_neck", "j_shoulder_le", boneESPCol);
	DrawBoneLine(ent, entNum, "j_shoulder_le", "j_elbow_le", boneESPCol);
	DrawBoneLine(ent, entNum, "j_elbow_le", "j_wrist_le", boneESPCol);

	//right arm
	DrawBoneLine(ent, entNum, "j_neck", "j_shoulder_ri", boneESPCol);
	DrawBoneLine(ent, entNum, "j_shoulder_ri", "j_elbow_ri", boneESPCol);
	DrawBoneLine(ent, entNum, "j_elbow_ri", "j_wrist_ri", boneESPCol);

	//spine
	DrawBoneLine(ent, entNum, "j_neck", "j_mainroot", boneESPCol);

	//left leg
	DrawBoneLine(ent, entNum, "j_mainroot", "j_hip_le", boneESPCol);
	DrawBoneLine(ent, entNum, "j_hip_le", "j_knee_le", boneESPCol);
	DrawBoneLine(ent, entNum, "j_knee_le", "j_ankle_le", boneESPCol);

	//right leg
	DrawBoneLine(ent, entNum, "j_mainroot", "j_hip_ri", boneESPCol);
	DrawBoneLine(ent, entNum, "j_hip_ri", "j_knee_ri", boneESPCol);
	DrawBoneLine(ent, entNum, "j_knee_ri", "j_ankle_ri", boneESPCol);
}

void _EntityESP()
{
	for (int i = 0; i < 2048; i++)
	{
		if (Centity_s[i].Type > 0)
		{
			Vector2 Location;
			if (WorldToScreen(Centity_s[i].Origin, &Location.x, &Location.y))
			{
				if (Centity_s[i].Type == ET_ITEM)
				{
					if (Centity_s[i].Alive & 1) {
						int WeaponID = Centity_s[i].WeaponID;

						int dwTempShader = GetWeaponShader(WeaponID);
						if (dwTempShader)
							CG_DrawRotatedPicPhysical(0x82B94570, Location.x - 20, Location.y, 40, 20, 0, colWHITE, dwTempShader);


						if (bEntityLine)
							DrawLine(Location.x, Location.y, cgArray_s->RefDef.Width / 2, cgArray_s->RefDef.Height - 30, colWHITE, Material_RegisterHandle("white", 0), 1);
					}
				}
				else if (Centity_s[i].Type == ET_MISSLE)
				{
					if (Centity_s[i].Alive & 4) {
						DrawBoundingBox(Centity_s[i].Origin, 8, 13, colorYellowTrans);

						if (bEntityLine)
							DrawLine(Location.x, Location.y, cgArray_s->RefDef.Width / 2, cgArray_s->RefDef.Height - 30, colorYellowTrans, Material_RegisterHandle("white", 0), 1);
					}
				}
			}
		}
	}
}

void _ESP()
{
	if (bDrawEntity)
		_EntityESP();

	Vector2 Screen;
	for (int i = 0; i < 18; i++)
	{
		if (i == cgArray_s->ClientNumber)
			continue;

		if (!isEntityPlayer(i))
			continue;

		bool iEnemy = IsEnemy(i);
		if ((bDrawAxis && iEnemy) || (bDrawAllies && !iEnemy))
		{
			Vector3 Origin = GetPlayerOrigin(i);
			Origin.z -= 5;
			if (WorldToScreen(Origin, &Screen.x, &Screen.y))
			{
				float *espColo = defaultEnemy;
				Aimtarget_isTargetVisible(0, &Centity_s[i], SL_GetString("j_head", 0)) ? espColo = defaultVisible : espColo;
				!iEnemy ? espColo = defaultFriend : espColo;
				bPlayerPriority[i] ? espColo = colorPurpleTrans : espColo;
				bPlayerFriendly[i] ? espColo = colorCyanTrans : espColo;
				i == ClosestPlayer ? espColo = defaultTarget : espColo;

				_ESPClient(i, espColo);

				if (bDrawBones)
					DoAllBones(i, colWHITE);
			}
		}
	}
}