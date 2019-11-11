#include "Invoker.h"

Vector2 RadarCenter, Center;

int RadarSize = 20;

int __declspec(naked) _GetPickupID(int id) {
	__asm {
		lis r8, 0x5D9F
		ori r8, r8, 0x7391
		mr r9, r3
		mulhw r7, r9, r8
		srawi r11, r7, 9
		srwi r10, r11, 31
		add r6, r11, r10
		mulli r5, r6, 0x578
		subf r3, r5, r9
		blr
	}
}

int R_GetWeaponID(int r3) {
	int tempId;

	__asm {
		lis r8, 0x5D9F
		ori r8, r8, 0x7391
		mr r9, r3
		mulhw r7, r9, r8
		srawi r11, r7, 9
		srwi r10, r11, 31
		add r6, r11, r10
		mulli r5, r6, 0x578
		subf r3, r5, r9
		mr tempId, r3
	}

	return tempId;
}

enum CompassType
{
	COMPASS_TYPE_PARTIAL = 0x0,
	COMPASS_TYPE_FULL = 0x1,
};

struct rectDef_s
{
	float x;
	float y;
	float w;
	float h;
	int horzAlign;
	int vertAlign;
};

float RadarBG[4] = { 0, 0, 0, 0.5578176576 };

void drawMat(float x, float y, float width, float height, float angle, const float *color) {
	CG_DrawRotatedPicPhysical(0x82690F48, x, y, width, height, angle, defaultColor, Material_RegisterHandle("white", 0));
}

void OutlineBox(float x, float y, float w, float h, const float *outlineColor, float lineWidth)
{
	drawMat(x, y, lineWidth, h, 0, outlineColor);
	drawMat(x + lineWidth, y, w - lineWidth, lineWidth, 0, outlineColor);
	drawMat(x + lineWidth, y + h - lineWidth, w - (lineWidth * 2), lineWidth, 0, outlineColor);
	drawMat(x + w - lineWidth, y + lineWidth, lineWidth, h - lineWidth, 0, outlineColor);
}

void*(*Material_RegisterHandle_)(const char *name, int imageTrack) = (void*(*)(const char *, int))0x8234E4F0;

bool notTeam(int i)
{
	if (cgArray_s->ClientInfo[cgArray_s->ClientNumber].Team != cgArray_s->ClientInfo[i].Team || cgArray_s->ClientInfo[i].Team == 0)
		return true;
	else return false;
}

void RadarPatches()
{
	*(int*)0x821102A8 = 0x60000000;
	*(int*)0x820EB508 = 0x4E800020;
	*(int*)0x820EB558 = 0x4E800020;
	*(int*)0x820EB638 = 0x4E800020;
	*(int*)0x820EBBA0 = 0x4E800020;
	*(int*)0x820EB8F8 = 0x4E800020;
	*(int*)0x820EC7A0 = 0x4E800020;
	*(int*)0x820ECA10 = 0x4E800020;
	*(int*)0x820ED000 = 0x4E800020;
	*(int*)0x820ED520 = 0x4E800020;
	*(int*)0x820EBE18 = 0x4E800020;
	*(int*)0x820EC468 = 0x4E800020;
	*(int*)0x820EE938 = 0x4E800020;
	*(int*)0x820EEFA8 = 0x4E800020;
	*(int*)0x820EF928 = 0x4E800020;
	*(int*)0x820EFB78 = 0x4E800020;
	*(int*)0x820EFEA0 = 0x4E800020;
	*(int*)0x82315F70 = 0x4E800020;
}

void Radar() {
	RadarPatches();
	cgArray_t* cgArray = *(cgArray_t**)0x825B8638;
	Centity_t* cEntity = *(Centity_t**)0x825BE150;

	Vector2 RadarXY, RadarCenter, Center;

	int RadarSize = 178;

	RadarXY.x = -160;
	Center.x = cgArray->RefDef.Width / 2;
	RadarXY.y = 0;
	Center.y = cgArray->RefDef.Height / 2;

	Center.x = cgArray_s->RefDef.Width / 2;
	Center.y = cgArray_s->RefDef.Height / 2;
	RadarCenter.x = 210.7211305;
	RadarCenter.y = RadarSize / 2;

	rectDef_s cord = { -80, 15 + RadarXY.y, 187.442261, 185.442261, 0, 0 }; //x, y, w, h

	DrawShader(RadarCenter.x - RadarSize + 5.5, RadarCenter.y - RadarSize / 2 + 19.6, 283.442261, 281.442261, RadarBG, "white");

	DrawShader(RadarCenter.x - RadarSize + 5.5, 160.7211305, 282.442261, 1, colWHITE, "white");
	DrawShader(RadarCenter.x - RadarSize + 150, RadarCenter.y - RadarSize / 2 + 19.6, 1, 281.442261, colWHITE, "white");

	OutlineBox(RadarCenter.x - RadarSize + 5.5, RadarCenter.y - RadarSize / 2 + 19.6, 283.442261, 281.442261, defaultColor, 1.7);

	Invoke<void>(0x820EC0C8, 0, COMPASS_TYPE_PARTIAL, &cord, &cord, Material_RegisterHandle("compass_map_default", 7), colorWhiteTrans);
	CG_DrawRotatedPicPhysical(0x82690F48, RadarCenter.x - 38.27861, 150.7211305, 22, 22, 0, colorYellowTrans, Material_RegisterHandle("compassping_player", 5)); //Character

	for (int i = 0; i < 2048; i++)
	{
		if (i != cgArray->ClientNumber)
		{
			int Type = cEntity[i].Type;

			if (Type != ET_PLAYER && Type != ET_MISSLE && Type != ET_ITEM && Type != ET_PLAYER_CORPSE)
				continue;

			void* Shader;

			float *color = defaultEnemy;
			if (Type == ET_PLAYER) {
				if (!isEntityPlayer(i))
					continue;

				if (!(cEntity[i].Alive & 1))
					continue;
				Shader = Material_RegisterHandle_("compassping_player", 0);

				if (i != cgArray_s->ClientNumber) {
					bool iEnemy = notTeam(i);
					if (!((iEnemy) || (!iEnemy)))
						continue;

					Aimtarget_isTargetVisible(0, &Centity_s[i], autowallBox[1]) ? color = colorCyanTrans : color;
					!iEnemy ? color = colorYellowTrans : color;
					bPlayerPriority[i] ? color = colorPurpleTrans : color;
					i == ClosestPlayer ? color = colorCyanTrans : color;
				}
				else
				{
					color = colorRedTrans;
				}
			}

			int RadarX, RadarY, Final_Radar;

			/*Checking Maps for good math*/
			if (!strcmp(Dvar_GetString("ui_mapname"), "mp_afghan")) { //Afghan
				Final_Radar = 15.6298791;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_terminal")) { //Terminal
				Final_Radar = 15.6298791;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_rust")) { //Rust
				Final_Radar = 9.3731694;
				Cbuf_AddText(0, "set compassMaxRange 2500");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_estate")) { //Estate
				Final_Radar = 16.2298791;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_derail")) { //Derail
				Final_Radar = 16.2796301;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_highrise")) { //Highrise
				Final_Radar = 14.8456478;
				Cbuf_AddText(0, "set compassMaxRange 3500");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_subbase")) { //Subbase
				Final_Radar = 15.6298791;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_boneyard")) { //Scrapyard
				Final_Radar = 15.9456478;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_quarry")) { //Quarry
				Final_Radar = 16.4456478;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_invasion")) { //Invasion
				Final_Radar = 16.6456478;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_nightshift")) { //Skidrow (Zone)
				Final_Radar = 16.9456478;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_rundown")) { //Rundown
				Final_Radar = 16.9456478;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_checkpoint")) { //Karachi
				Final_Radar = 14.8456478;
				Cbuf_AddText(0, "set compassMaxRange 3500");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_brecourt")) { //Wasteland
				Final_Radar = 23.6456478;
				Cbuf_AddText(0, "set compassMaxRange 6750");
			}
			else if (!strcmp(Dvar_GetString("ui_mapname"), "mp_underpass")) { //Underpass
				Final_Radar = 16.9456478;
				Cbuf_AddText(0, "set compassMaxRange 4250");
			}
			else {
				Final_Radar = 10;
			}

			RadarX = GetPlayerOrigin(cgArray_s->ClientNumber).x - GetPlayerOrigin(i).x;
			RadarY = GetPlayerOrigin(cgArray_s->ClientNumber).y - GetPlayerOrigin(i).y;

			float Angle = cgArray_s->ViewAngle.y / 180 * 3.141;

			float RotateX = RadarY * cosf(Angle) - RadarX * sinf(Angle);
			float RotateY = RadarX * cosf(Angle) + RadarY * sinf(Angle);

			float FinalX = RadarCenter.x + RotateX / Final_Radar;
			float FinalY = RadarCenter.y + RotateY / Final_Radar;

			if (FinalX < RadarCenter.x - RadarSize / 1.25)
				FinalX = (RadarCenter.x - RadarSize / 1.25) + 1; //Movement to left

			if (FinalY < RadarCenter.y - RadarSize / 1.35)
				FinalY = (RadarCenter.y - RadarSize / 1.35) - 4.8; //Movement up

			if (FinalX > RadarCenter.x + RadarSize / 1.35)
				FinalX = (RadarCenter.x + RadarSize / 1.35) - 4.8; //Movement to right

			if (FinalY > RadarCenter.y + RadarSize / 1.35)
				FinalY = (RadarCenter.y + RadarSize / 1.35); //Movement down

			if (drawEntites && Type == ET_ITEM) {
				if (!(cEntity[i].Alive & 1))
					continue;

				int WeaponID = _GetPickupID(cEntity[i].PickupID);

				color = colorWhiteTrans;

				if (strcmp(GetRawWeaponName(WeaponID), "WEAPON_SCAVENGER_BAG")) {

					if (WeaponID <= 0)
						continue;

					int dwTempShader = GetWeaponShader(WeaponID);
					if (dwTempShader)
						Shader = (void*)dwTempShader;
					DrawShader(((FinalX - 40)), (FinalY + 60), 22, 20, colorWhiteTrans, *(char**)Shader);
					void* Shader;
				}
				else {
					Shader = Material_RegisterHandle_("specialty_scavenger", 0);
					DrawShader(((FinalX - 40)), (FinalY + 60), 22, 22, colorWhiteTrans, *(char**)Shader);
				}
			}

			if (Type == ET_PLAYER_CORPSE) {
				color = colorRedTrans;
				Shader = Material_RegisterHandle_("killicondied", 0);
			}

			if (drawEntites && Type == ET_MISSLE || Type == ET_PLANE)
			{
				if (!(Centity_s[i].Alive & 4))
					continue;

				int WeaponID = _GetPickupID(cEntity[i].WeaponID);

				color = colorYellowTrans;

				/*if (Type == ET_PLANE) {
					Shader = Material_RegisterHandle_("specialty_helicopter_support", 0);
					printf("Attempting to draw Helicopter."); //Doenst work
				}*/

				if (strcmp(GetRawWeaponName(WeaponID), "WEAPON_FLASH_GRENADE"))
				{
					void* Entity_Shader;
					int dwTempShader = GetWeaponShader(WeaponID);
					if (dwTempShader)
						Entity_Shader = (void*)dwTempShader;
					DrawShader(((FinalX - 40)), (FinalY + 60), 20, 20, colorWhiteTrans, *(char**)Entity_Shader);
				}

				if (!strcmp((const char*)Material_RegisterHandle_("compass_objpoint_ammo_friendly", 5), "compass_objpoint_ammo_friendly"))
					DrawShader(((FinalX - 40)), (FinalY + 60), 20, 20, colorWhiteTrans, "compass_objpoint_ammo_friendly");
				else if (!strcmp((const char*)Material_RegisterHandle_("compass_objpoint_ammo_enemy", 5), "compass_objpoint_ammo_enemy"))
					DrawShader(((FinalX - 40)), (FinalY + 60), 20, 20, colorWhiteTrans, "compass_objpoint_ammo_enemy");
			}
			else if (i <= 18)
			{
				CG_DrawRotatedPicPhysical(0x82690F48, ((FinalX - 35)), (FinalY + 65), 22, 22, (cgArray_s->ViewAngle.y - cgArray_s->ClientInfo[i].viewAngle.y), color, Material_RegisterHandle(*(char**)Shader, 7));
			}
			else {
				if (drawDeaths && Type == ET_PLAYER_CORPSE)
					DrawShader(((FinalX - 35)), (FinalY + 65), 15, 15, colorRedTrans, "killicondied");
			}
		}
	}
}

float Background[4] = { 0.0f, 0.0f, 0.0f, 0.4705882352941176 };
void _Radar()
{
	FadeStart();
	Center.x = IW4MP::cgArray_s->RefDef.Width / 2;
	Center.y = IW4MP::cgArray_s->RefDef.Height / 2;
	RadarCenter.x = (Center.x * 2) - RadarSize - 40;
	RadarCenter.y = RadarSize / 2 + 25;

	//DrawShader(RadarCenter.x - RadarSize, RadarCenter.y - RadarSize / 2, RadarSize * 2, RadarSize, defaultShader, "white");

	//	DrawLine(RadarCenter.x - RadarSize / 2, RadarCenter.y - RadarSize / 2, RadarCenter.x, RadarCenter.y, radarLine, Material_RegisterHandle("white", 0), 1);
	//	DrawLine(RadarCenter.x + RadarSize / 2, RadarCenter.y - RadarSize / 2, RadarCenter.x, RadarCenter.y, radarLine, Material_RegisterHandle("white", 0), 1);

	//	DrawShader(RadarCenter.x - RadarSize, RadarCenter.y, RadarSize * 2, 1, radarLine, "white"); // horz
	//	DrawShader(RadarCenter.x, RadarCenter.y - RadarSize / 2, 1, RadarSize, radarLine, "white"); // vert

	//float healthHeight = cgArray_s->Health * 1.75;

	//float healthHeight = IW4MP::cgArray_s->Health * 0.95; //leghth/size vertical

	//DrawShader(RadarCenter.x - RadarSize - 45, RadarCenter.y - RadarSize / 500, 20, 250, colSHADER, "white");

	//	IW4MP::DrawShader(RadarCenter.x - RadarSize - 1104, (289 - healthHeight) + RadarCenter.y - RadarSize / 5, 5, healthHeight, Fade, "white");   //healthbar

	int CenterX = 1280 / 2;
	int CenterY = 720 / 2;

	float HealthbarLength;
	if (HealthbarLength != (cgArray_s->Health * 2))
	{
		HealthbarLength = (cgArray_s->Health * 2);
	}

	DrawShader((CenterX - 100), (CenterY + 300), 204, 20, Background, "white");

	float healthColor[4] = { (float)1 - (cgArray_s->Health / 100) , (float)cgArray_s->Health / 100, 0,  1 };
	DrawShader((CenterX - 98), (CenterY + 302), HealthbarLength, 16, defaultColor, "white");

	char healthmsg[250];
	sprintf(healthmsg, "Health: (%i / 100)", cgArray_s->Health);
	DrawText(healthmsg, (CenterX - 71), (CenterY + 317), "fonts/objectivefont", 0.45, colWHITE);

	for (int i = 0; i < 2048; i++)
	{
		int Type = IW4MP::Centity_s[i].Type;

		//	if (Type != ET_PLAYER && Type != ET_MISSLE && Type != ET_ITEM)
		continue;

		int Shader;

		float *color = defaultEnemy;
		if (Type == IW4MP::ET_PLAYER) {
			if (!IW4MP::isEntityPlayer(i))
				continue;

			//	Shader = Material_RegisterHandle("compassping_player", 0);

			if (i != IW4MP::cgArray_s->ClientNumber) {
				bool iEnemy = IW4MP::IsEnemy(i);
				//	if (!((bRadarAxis && iEnemy) || (bRadarAlly && !iEnemy)))
				continue;


				Aimtarget_isTargetVisible(0, &Centity_s[i], autowallBox[1]) ? color = defaultVisible : color;

				!iEnemy ? color = defaultFriend : color;
				bPlayerPriority[i] ? color = colorCyanTrans : color;
				bPlayerFriendly[i] ? color = colorCyanTrans : color;
				i == ClosestPlayer ? color = defaultTarget : color;
			}
			else {
				color = colorCyanTrans;
			}
		}

		if (Type == IW4MP::ET_ITEM) {
			if (!bRadarEntity)
				continue;

			if (!(IW4MP::Centity_s[i].Alive & 1))
				continue;

			int WeaponID = IW4MP::_GetPickupID(IW4MP::Centity_s[i].PickupID);

			color = colorWhiteTrans;

			if (strcmp(IW4MP::GetRawWeaponName(WeaponID), "WEAPON_SCAVENGER_BAG")) {

				if (WeaponID <= 0)
					continue;

				int dwTempShader = IW4MP::GetWeaponShader(WeaponID);
				if (dwTempShader)
					Shader = dwTempShader;
			}
			else {
				Shader = IW4MP::Material_RegisterHandle("specialty_scavenger", 0);
			}
		}

		if (Type == IW4MP::ET_MISSLE) {
			if (!bRadarEntity)
				continue;

			if (!(IW4MP::Centity_s[i].Alive & 4))
				continue;

			color = colorYellowTrans;
		}

		int RadarX, RadarY;

		RadarX = IW4MP::GetPlayerOrigin(IW4MP::cgArray_s->ClientNumber).x - IW4MP::GetPlayerOrigin(i).x;
		RadarY = IW4MP::GetPlayerOrigin(IW4MP::cgArray_s->ClientNumber).y - IW4MP::GetPlayerOrigin(i).y;

		float Angle = IW4MP::cgArray_s->ViewAngle.y / 180 * 3.141;

		float RotateX = RadarY * cosf(Angle) - RadarX * sinf(Angle);
		float RotateY = RadarX * cosf(Angle) + RadarY * sinf(Angle);

		float FinalX = RadarCenter.x + RotateX / fRadarDist;
		float FinalY = RadarCenter.y + RotateY / fRadarDist;

		if (FinalX < RadarCenter.x - RadarSize) FinalX = (RadarCenter.x - RadarSize) + 2;
		if (FinalY < RadarCenter.y - RadarSize / 2) FinalY = (RadarCenter.y - RadarSize / 2) + 2;

		if (FinalX > RadarCenter.x + RadarSize) FinalX = (RadarCenter.x + RadarSize) - 2;
		if (FinalY > RadarCenter.y + RadarSize / 2) FinalY = (RadarCenter.y + RadarSize / 2) - 2;

		if (Type == IW4MP::ET_MISSLE)
			IW4MP::DrawShader(FinalX - 2, FinalY - 2, 4, 4, color, "white");
		else
			IW4MP::CG_DrawRotatedPicPhysical(0x82690F48, FinalX - 10, FinalY - 10, 20, 20, (i == IW4MP::cgArray_s->ClientNumber || Type == IW4MP::ET_ITEM) ? 0 : (IW4MP::cgArray_s->ViewAngle.y - IW4MP::cgArray_s->ClientInfo[i].viewAngle.y), color, Shader);
	}
}

Vector2 cCenter;

void _Compass()
{
	cCenter.x = IW4MP::cgArray_s->RefDef.Width / 2;
	cCenter.y = IW4MP::cgArray_s->RefDef.Height / 2;

	for (int i = 0; i < 2048; i++)
	{
		int Type = IW4MP::Centity_s[i].Type;

		if (Type != IW4MP::ET_PLAYER && Type != IW4MP::ET_ITEM)
			continue;

		int Shader, dwWidth, dwHeight;

		float *color = colWHITE;
		if (Type == IW4MP::ET_PLAYER) {
			if (!IW4MP::isEntityPlayer(i))
				continue;

			if (i == IW4MP::cgArray_s->ClientNumber)
				continue;

			dwWidth = 30; dwHeight = 30;
			Shader = IW4MP::Material_RegisterHandle("compassping_player", 0);

			bool iEnemy = IW4MP::IsEnemy(i);
			if (!((bCompassAxis && iEnemy) || (bCompassAlly && !iEnemy)))
				continue;

			color = defaultEnemy;

			IW4MP::Aimtarget_isTargetVisible(0, &IW4MP::Centity_s[i], autowallBox[1]) ? color = defaultVisible : color;
			!iEnemy ? color = defaultFriend : color;
			bPlayerPriority[i] ? color = colorCyanTrans : color;
			bPlayerFriendly[i] ? color = colorCyanTrans : color;
			i == ClosestPlayer ? color = defaultTarget : color;
		}

		if (Type == IW4MP::ET_ITEM) {
			if (!bCompassEntity)
				continue;

			if (!(IW4MP::Centity_s[i].Alive & 1))
				continue;

			int WeaponID = _GetPickupID(IW4MP::Centity_s[i].PickupID);

			if (strcmp(IW4MP::GetRawWeaponName(WeaponID), "WEAPON_SCAVENGER_BAG")) {

				if (WeaponID <= 0)
					continue;

				dwWidth = 40; dwHeight = 20;

				int dwTempShader = IW4MP::GetWeaponShader(WeaponID);
				if (dwTempShader)
					Shader = dwTempShader;
			}
			else {
				dwWidth = 20; dwHeight = 20;
				Shader = IW4MP::Material_RegisterHandle("specialty_scavenger", 0);
			}
		}

		int RadarX, RadarY;

		RadarX = IW4MP::GetPlayerOrigin(IW4MP::cgArray_s->ClientNumber).x - IW4MP::GetPlayerOrigin(i).x;
		RadarY = IW4MP::GetPlayerOrigin(IW4MP::cgArray_s->ClientNumber).y - IW4MP::GetPlayerOrigin(i).y;

		float Angle = IW4MP::cgArray_s->ViewAngle.y / 180 * 3.141;

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
			IW4MP::CG_DrawRotatedPicPhysical(0x82690F48, CircleX - dwWidth / 2, CircleY - dwHeight / 2, dwWidth, dwHeight, FinalA, color, Shader);
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
	MakeLines(Center, -W, -W, H , -W + (W / 2), -W, H , sColor, 1);
	MakeLines(Center, W / 2, -W, H , W, -W, H , sColor, 1);

	MakeLines(Center, -W, -W, H , -W, -W + (W / 2), H , sColor, 1);
	MakeLines(Center, -W, W - (W / 2), H , -W, W, H , sColor, 1);

	MakeLines(Center, W, -W + (W / 2), H , W, -W, H , sColor, 1);
	MakeLines(Center, W, W - (W / 2), H , W, W, H , sColor, 1);

	MakeLines(Center, -W + (W / 2), W, H , -W, W, H , sColor, 1);
	MakeLines(Center, W, W, H , W - (W / 2), W, H , sColor, 1);

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

		float fontSize = 0.45;
		char *fontName = "fonts/smallfont";

		float fDistance = GetDistance(GetPlayerOrigin(client), GetPlayerOrigin(cgArray_s->ClientNumber));
		bool enemy = IsEnemy(client);
		bool enemyp = IsEnemyp(client);

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
			const char *szWeapon = GetWeaponName(Centity_s[client].WeaponID);
			SetTextWithBackground(szWeapon, FeetLocation.x - TextWidth(szWeapon, fontName) / 2 * fontSize, FeetLocation.y + 17, fontName, fontSize, colWHITE, 3);
			int material = *(int*)(BG_GetWeaponVariantDef(Centity_s[client].WeaponID) + 0x48);

			if (material != 0)
				CG_DrawRotatedPicPhysical(0x82690F48, FeetLocation.x - TextWidth(szWeapon, fontName) / 2 * fontSize, FeetLocation.y + 17, 60, 30, 0, enemy ? colRED : colGREEN, material);
		

			else if (material != 0)
				CG_DrawRotatedPicPhysical(0x82690F48, FeetLocation.x - TextWidth(szWeapon, fontName) / 2 * fontSize, FeetLocation.y + 17, 60, 30, 0, enemyp ? colCYAN : colGREEN, material);


		}

		if (bDrawName) {
			const char *clientName = cgArray_s->ClientInfo[client].Name;

			char _header[128];
			char _distance[128];


			_snprintf(_header, 128, "%s", clientName);

			_snprintf(_distance, 128, "%.0fm", fDistance);

			SetTextWithBackground(_header, FeetLocation.x - TextWidth(_header, fontName) / 2 * fontSize, HeadLocation.y - 15, fontName, fontSize, colWHITE, 15);

			SetTextWithBackground(_distance, FeetLocation.x - TextWidth(_distance, fontName) / 2 * fontSize, HeadLocation.y - 3, fontName, fontSize, colWHITE, 3);
		}
	}
}

void DrawBoneLine(IW4MP::pCentity_t entity, int ent, char* tagname1, char* tagname2, float *col)
{
	Vector3 Origin1 = IW4MP::GetTagPos(ent, tagname1), Origin2 = IW4MP::GetTagPos(ent, tagname2);

	Vector2 Loc1, Loc2;
	if (IW4MP::WorldToScreen(Origin1, &Loc1.x, &Loc1.y) && IW4MP::WorldToScreen(Origin2, &Loc2.x, &Loc2.y)) {
		IW4MP::DrawLine(Loc1.x, Loc1.y, Loc2.x, Loc2.y, colorCyanTrans, IW4MP::Material_RegisterHandle("white", 0), 2.50);
	}
}

void DoAllBones(int Client, float *boneESPCol)
{
	pCentity_t ent = &Centity_s[Client];

	int entNum = Client;

	//neck
//	DrawBoneLine(ent, entNum, "j_head", "j_chin_skinroll", boneESPCol);
//	DrawBoneLine(ent, entNum, "j_chin_skinroll", "j_neck", boneESPCol);

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
	DrawBoneLine(ent, entNum, "j_ankle_le", "j_ball_le", boneESPCol);

	//right leg
	DrawBoneLine(ent, entNum, "j_mainroot", "j_hip_ri", boneESPCol);
	DrawBoneLine(ent, entNum, "j_hip_ri", "j_knee_ri", boneESPCol);
	DrawBoneLine(ent, entNum, "j_knee_ri", "j_ankle_ri", boneESPCol);
	DrawBoneLine(ent, entNum, "j_ankle_ri", "j_ball_ri", boneESPCol);
}


void _EntityESP()
{
	for (int i = 0; i < 2048; i++)
	{
		if (IW4MP::Centity_s[i].Type > 0)
		{
			Vector2 Location;
			if (IW4MP::WorldToScreen(IW4MP::Centity_s[i].Origin, &Location.x, &Location.y))
			{
				if (IW4MP::Centity_s[i].Type == IW4MP::ET_ITEM)
				{
					if (IW4MP::Centity_s[i].Alive & 1) {
						int WeaponID = IW4MP::R_GetWeaponID(IW4MP::Centity_s[i].PickupID);

						if (strcmp(IW4MP::GetRawWeaponName(WeaponID), "WEAPON_SCAVENGER_BAG")) {
							if (WeaponID <= 0)
								continue;

							int dwTempShader = IW4MP::GetWeaponShader(WeaponID);
							if (dwTempShader)
								IW4MP::CG_DrawRotatedPicPhysical(0x82690F48, Location.x - 20, Location.y, 40, 20, 0, colWHITE, dwTempShader);

							if (bEntityName)
								IW4MP::SetTextCenteredWithBackGround(IW4MP::GetWeaponName(WeaponID), "fonts/smallFont", Location.x, Location.y, 0.4, 0.4, colWHITE, defaultShader);
						}
						else
							IW4MP::CG_DrawRotatedPicPhysical(0x82690F48, Location.x - 10, Location.y - 10, 28, 28, 0, colWHITE, IW4MP::Material_RegisterHandle("scavenger_pickup", 0));

						if (bEntityLine)
							IW4MP::DrawLine(Location.x, Location.y, IW4MP::cgArray_s->RefDef.Width / 2, IW4MP::cgArray_s->RefDef.Height - 30, colWHITE, IW4MP::Material_RegisterHandle("white", 0), 1);
					}
				}
				else if (IW4MP::Centity_s[i].Type == IW4MP::ET_MISSLE)
				{
					if (IW4MP::Centity_s[i].Alive & 4) {
						DrawBoundingBox(IW4MP::Centity_s[i].Origin, 8, 13, colorCyanTrans);

						if (bEntityLine)
							IW4MP::DrawLine(Location.x, Location.y, IW4MP::cgArray_s->RefDef.Width / 2, IW4MP::cgArray_s->RefDef.Height - 30, colorCyanTrans, IW4MP::Material_RegisterHandle("white", 0), 1);
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

		if (bDrawBones)
			DoAllBones(i, iEnemy ? colRED : colGREEN);

		if ((bDrawAxis && iEnemy) || (bDrawAllies && !iEnemy))
		{
			Vector3 Origin = GetPlayerOrigin(i);
			Origin.z -= 5;
			if (WorldToScreen(Origin, &Screen.x, &Screen.y))
			{
				float *espColo = defaultEnemy;
				Aimtarget_isTargetVisible(0, &Centity_s[i], autowallBox[1]) ? espColo = defaultVisible : espColo;
				!iEnemy ? espColo = defaultFriend : espColo;
				bPlayerPriority[i] ? espColo = colorCyanTrans : espColo;
				bPlayerFriendly[i] ? espColo = colorGreenTrans : espColo;
				i == ClosestPlayer ? espColo = defaultTarget : espColo;


				_ESPClient(i, espColo);
			}
		}
	}
}