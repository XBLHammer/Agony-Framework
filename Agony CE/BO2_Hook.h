void _DrawMenu()
{
	//DrawShader(100, 200, 100, 50, Fade, "barrack_ass_killer");
	
	DrawText(szMenuName, 50, cgArray_s->RefDef.Height - 250, "fonts/720/normalFont", 0.5, defaultColor);

	if (MenuVars.openState == 1)
	{
		int CurrentMenu = MenuVars.currentMenu,
			CurrentOption = MenuVars.currentOption[CurrentMenu],
			MaxOption = MenuVars.displayCount[CurrentMenu],
			MenuOption = MenuVars.optionCount[CurrentMenu];
		const char* Title_Text = MenuVars.Menu_Title[CurrentMenu];

		float flMenuH = MenuVars.MenuH[CurrentMenu];

		DrawShader(flMenuX + flBSize, flMenuY + flHSize, flMenuW - flBSize * 2, flMenuH - flBSize, defaultShader, "white");

		DrawShader(flMenuX, flMenuY, flMenuW, flHSize, colGRAY, "white");
		DrawShader(flMenuX, flMenuY + flHSize, flBSize, flMenuH, colGRAY, "white");
		DrawShader(flMenuX + flMenuW - flBSize, flMenuY + flHSize, flBSize, flMenuH, colGRAY, "white");
		DrawShader(flMenuX + flBSize, flMenuY - 2 + flMenuH + flBSize * 2, flMenuW - (flBSize * 2), flBSize, colGRAY, "white");

		DrawShader(flMenuX + flBSize, flMenuY + flHSize, flMenuW - (flBSize * 2), 15, colDGRAY, "white");

		char _szName[64];
		_snprintf(_szName, 64, "%s - %s", szMenuName, szVersionNum);

		DrawText(_szName, flMenuX + (flMenuW / 2) - ((TextWidth(_szName, szHeaderFont) / 2) * flHeaderSize), flMenuY + TextHeight(szHeaderFont) * flHeaderSize, szHeaderFont, flHeaderSize, defaultText);

		for (int i = 0; i < 7; i++)
			DrawText(MenuVars.Menu_Title[i], flMenuX + flBSize + 13 + (i * 85), flMenuY + flHSize + 14, szOptionFont, flOptionSize, i == CurrentMenu ? defaultColor : defaultText);

		float flX[3];
		float a_flX = flMenuX + 30;

		float flY[3][2];
		float a_flY = flMenuY + (flHSize * 2) + 30;

		float flComboX;
		float flComboY;

		for (int i = 0; i < 3; i++) {
			flX[i] = flMenuX + 30;
			for (int c = 0; c < 2; c++)
				flY[i][c] = flMenuY + (flHSize * 2) + 30 + (c * 200.0f);
		}

		bool bSubToggle = false;

		if (MenuVars.Sub_Toggle[CurrentMenu] != NULL)
		{
			bSubToggle = true;
			DrawShader(flX[0], flY[0][0] + 1 - 13, 11, 11, defaultShader, "white");
			if (*MenuVars.Sub_Toggle[CurrentMenu])
				DrawShader(flX[0] + 2, flY[0][0] + 3 - 13, 7, 7, defaultColor, "white");

			DrawText("Active", flX[0] + 14, flY[0][0], szOptionFont, flOptionSize, CurrentOption == 0 ? defaultColor : defaultText);

			a_flY += flOptionH;

			for (int i = 0; i < 3; i++) {
				for (int c = 0; c < 2; c++)
					flY[i][c] += flOptionH;
			}
		}

		for (int i = 0; i < MaxOption; i++)
		{
			if (MenuVars.GroupHeight[CurrentMenu][i] > 0)
			{
				int t_Column = MenuVars.gOffset_Column[CurrentMenu][i];
				int t_Row = MenuVars.gOffset_Row[CurrentMenu][i];
				float t_flX = a_flX + ((t_Column * (flOptionW + 47.5f)));
				float t_flY = a_flY + ((t_Row * 200.0f));

				const char *szGroupName = MenuVars.GroupName[CurrentMenu][i];
				float flNameW = TextWidth(szGroupName, szOptionFont) * flOptionSize;

				float flGWidth = 16 + flNameW;

				float flBoxH = 3.0f + MenuVars.GroupHeight[CurrentMenu][i] * flOptionH;

				DrawText(szGroupName, t_flX + 13, t_flY + ((TextHeight(szOptionFont) * flOptionSize) / 2), szOptionFont, flOptionSize, defaultText);

				DrawShader(t_flX, t_flY, 10, 2, defaultColor, "white");
				DrawShader(t_flX + flGWidth, t_flY, (flOptionW - flGWidth), 2, defaultColor, "white");
				DrawShader(t_flX, t_flY + 2, 2, flBoxH, defaultColor, "white");
				DrawShader(t_flX + flOptionW - 2, t_flY + 2, 2, flBoxH, defaultColor, "white");
				DrawShader(t_flX + 2, t_flY + flBoxH, flOptionW - 4, 2, defaultColor, "white");

				flY[t_Column][t_Row] += flOptionH;
			}
		}

		for (int i = bSubToggle ? 1 : 0; i < MenuOption; i++)
		{
			const char* Option_Text = MenuVars.Option_Text[CurrentMenu][i];
			int t_Column = MenuVars.Offset_Column[CurrentMenu][i];
			int t_Row = MenuVars.Offset_Row[CurrentMenu][i];

			float t_flX = flX[t_Column] + ((t_Column * (flOptionW + 47.5f))) + 5;
			float t_flY = flY[t_Column][t_Row];

			if (MenuVars.Option_Toggle[CurrentMenu][i] != NULL)
			{
				DrawText(Option_Text, t_flX + 14, t_flY, szOptionFont, flOptionSize, i == CurrentOption ? defaultColor : defaultText);

				DrawShader(t_flX, t_flY + 1 - 13, 11, 11, defaultShader, "white");
				if (*MenuVars.Option_Toggle[CurrentMenu][i])
					DrawShader(t_flX + 2, t_flY + 3 - 13, 7, 7, defaultColor, "white");
			}
			else if (MenuVars.Option_ToggleArr[CurrentMenu][i] != NULL) {

				DrawText(Option_Text, t_flX + 14, t_flY, szOptionFont, flOptionSize, i == CurrentOption ? defaultColor : defaultText);

				t_flY += 10;
				flY[t_Column][t_Row] += 10;
				DrawShader(t_flX + 14, t_flY - 9, 80, 10, colBLACK, "white");
				const char *ArrayText = MenuVars.Option_ToggleArr[CurrentMenu][i][*MenuVars.Option_ToggleArr_Cur[CurrentMenu][i]];

				if (MenuVars.bComboBox[CurrentMenu][i]) {
					flComboX = t_flX + 14;
					flComboY = t_flY;
				}
				else
					DrawText(ArrayText, t_flX + 14 + 40 - ((TextWidth(ArrayText, szOptionFont) * 0.40) / 2), t_flY + 2, szOptionFont, 0.40, defaultText);
			}
			else if (MenuVars.fBarValue[CurrentMenu][i] != NULL) {
				t_flX += 30;

				DrawText(Option_Text, t_flX + 40 - ((TextWidth(Option_Text, szOptionFont) * flOptionSize) / 2), t_flY, szOptionFont, flOptionSize, i == CurrentOption ? defaultColor : defaultText);

				t_flY += 10;
				flY[t_Column][t_Row] += 10;
				float fBarWidth = 80 * ((*MenuVars.fBarValue[CurrentMenu][i] - (MenuVars.fBarMin[CurrentMenu][i])) / ((MenuVars.fBarMax[CurrentMenu][i]) - (MenuVars.fBarMin[CurrentMenu][i])));

				DrawShader(t_flX, t_flY - 9, 80, 3, colBLACK, "white");
				DrawShader(t_flX, t_flY - 9, fBarWidth, 3, defaultColor, "white");

				DrawShader(t_flX + fBarWidth - 1, t_flY - 11, 2, 7, defaultColor, "white");

				char ArrayText[16];
				_snprintf(ArrayText, 16, "%.1f", *MenuVars.fBarValue[CurrentMenu][i]);

				DrawText(ArrayText, t_flX + 40 - ((TextWidth(ArrayText, szOptionFont) * 0.40) / 2), t_flY + 6, szOptionFont, 0.40, defaultText);
				t_flY += 5;
				flY[t_Column][t_Row] += 5;
			}
			else
			{
				DrawText(Option_Text, t_flX + 14, t_flY, szOptionFont, flOptionSize, i == CurrentOption ? defaultColor : defaultText);
			}

			flY[t_Column][t_Row] += flOptionH;
		}
		if (MenuVars.bComboBox[CurrentMenu][CurrentOption]) {
			char **ComboArray = MenuVars.cComboData;
			int ComboSize = MenuVars.iComboMax;

			DrawShader(flComboX, flComboY, 80, 14 * ComboSize, colBLACK, "white");

			for (int i = 0; i < ComboSize; i++) {
				DrawText(ComboArray[i], flComboX + 40 - ((TextWidth(ComboArray[i], "fonts/720/normalFont") * 0.40) / 2), flComboY + 3 + (15 * i), "fonts/720/normalFont", 0.40, defaultText);

				if (i == MenuVars.iComboScroll) {
					DrawShader(flComboX, flComboY + (15 * i) - 9, 10, 2, defaultColor, "white");
					DrawShader(flComboX, flComboY + (15 * i) + 3, 10, 2, defaultColor, "white");

					DrawShader(flComboX + 70, flComboY + (15 * i) - 9, 10, 2, defaultColor, "white");
					DrawShader(flComboX + 70, flComboY + (15 * i) + 3, 10, 2, defaultColor, "white");

					DrawShader(flComboX, flComboY + (15 * i) - 7, 2, 10, defaultColor, "white");
					DrawShader(flComboX + 78, flComboY + (15 * i) - 7, 2, 10, defaultColor, "white");
				}
			}
		}

		if (CurrentMenu == 6) {
			if (strcmp(cgArray_s->ClientInfo[CurrentOption].Name, "")) {
				DrawShader(RadarCenter.x - RadarSize, RadarCenter.y - RadarSize / 2 + 250, 275, 60, defaultShader, "white");
				unsigned char StringIP[4];
				int IP = (GetIP(XNADDRA(CurrentOption)));
				memcpy(StringIP, (void*)IP, 4);
				const char player_ip[50] = "";
				_snprintf((char*)player_ip, 50, "%u.%u.%u.%u", StringIP[0], StringIP[1], StringIP[2], StringIP[3]);

				char _clientBuff[512];// = new char[512];

				_snprintf(_clientBuff, 512, "Prioritized: %s\nFriendly: %s\nBody Aim: %s\nIP: %s\nEnemy: %s",
					bPlayerPriority[CurrentOption] ? "Yes" : "No",
					bPlayerFriendly[CurrentOption] ? "Yes" : "No",
					bPlayerBodyAim[CurrentOption] ? "Yes" : "No",
					CurrentOption == cgArray_s->ClientNumber ? "1.3.3.7" : player_ip,
					IsEnemy(CurrentOption) ? "Yes" : "No");

				DrawText(_clientBuff, RadarCenter.x - RadarSize + 8, RadarCenter.y - RadarSize / 2 + 250 + 15, "fonts/hudbigfont", 1.5, defaultText);

			}
		}
	}
	else if (MenuVars.openState == 2)
	{
		float fRGBW = 300;
		float fRGBH = 150;
		float fRGBX = cgArray_s->RefDef.Width / 2 - (fRGBW / 2);
		float fRGBY = cgArray_s->RefDef.Height / 2 - (fRGBH / 2);
		float fBWidth = fRGBW - 150;
		int selected = MenuVars.RGBScroll;

		float fBarY[3] = { fRGBY + 15, fRGBY + fRGBH / 2, fRGBY + fRGBH - 15 };

		DrawShader(fRGBX, fRGBY, fRGBW, fRGBH, defaultShader, "white");

		DrawShader(fRGBX + 15, fBarY[0], fBWidth, 5, colWHITE, "white");
		DrawShader(fRGBX + 16, fBarY[0] + 1, MenuVars.RGBColor[0] * fBWidth - 2, 3, colRED, "white");

		DrawShader(fRGBX + 15, fBarY[1], fBWidth, 5, colWHITE, "white");
		DrawShader(fRGBX + 16, fBarY[1] + 1, MenuVars.RGBColor[1] * fBWidth - 2, 3, colGREEN, "white");

		DrawShader(fRGBX + 15, fBarY[2], fBWidth, 5, colWHITE, "white");
		DrawShader(fRGBX + 16, fBarY[2] + 1, MenuVars.RGBColor[2] * fBWidth - 2, 3, colBLUE, "white");

		DrawShader(fRGBX + 15 + MenuVars.RGBColor[selected] * fBWidth - 2, fBarY[selected] - 3, 4, 11, colWHITE, "white");

		DrawShader(fRGBX + 25 + fBWidth, fRGBY + 15, 115, 126, MenuVars.RGBColor, "white");
	}
}


int dwColorIndex;

int Upd_t = 0;
void FuncUpdate()
{
	if (Upd_t >= 180)
	{
		Upd_t = 0;
		SetFOV(0);
	}
	else
		Upd_t++;
}

#define BO2_R_RenderScene 0x828AF5A0 //BO2 TU18
typedef void(__cdecl *R_RenderScene_t)(DWORD refdef);
R_RenderScene_t BO2_R_RenderScene_ = (R_RenderScene_t)BO2_R_RenderScene;
void H_R_SetFrameFog(DWORD a1)
{
	//freeze patch
	*(short*)0x82334BF4 = 0x4800;
	*(int*)0x821DDE88 = 0x60000000;

	BO2_R_RenderScene_(a1);
	GetStructs();
	FuncUpdate();

	if (!isEntityPlayer(cgArray_s->ClientNumber))
		return;

	if (bLegitbot && bRagebot)
		bLegitbot = false;

	if (bXHair && MenuVars.openState == 0)
	{
		float xHairSize = (8 + (cgArray_s->SpreadMultiplier / 4));

		float xHairWidth = ((cgArray_s->RefDef.Width / 2) - 2 + 71.75 + 8) - ((cgArray_s->RefDef.Width / 2) - 8 - 71.75) + 40;

		if (bXHairSpread) {
			DrawShader((cgArray_s->RefDef.Width / 2) - 8 - xHairSize, cgArray_s->RefDef.Height / 2 - 1, 8, 1, defaultColor, "white");
			DrawShader((cgArray_s->RefDef.Width / 2) - 1 + xHairSize, cgArray_s->RefDef.Height / 2 - 1, 8, 1, defaultColor, "white");

			DrawShader((cgArray_s->RefDef.Width / 2) - 1, cgArray_s->RefDef.Height / 2 - xHairSize - 8, 1, 8, defaultColor, "white");
			DrawShader((cgArray_s->RefDef.Width / 2) - 1, cgArray_s->RefDef.Height / 2 + xHairSize - 1, 1, 8, defaultColor, "white");
		}

		DrawShader(cgArray_s->RefDef.Width / 2 - 1, cgArray_s->RefDef.Height / 2 - 15, 1, 30, defaultColor, "white");
		DrawShader(cgArray_s->RefDef.Width / 2 - 15, cgArray_s->RefDef.Height / 2 - 1, 30, 1, defaultColor, "white");
	}

	_ESP();

	if (bRadar) {
		_Radar();
	}

	if (bCompass) {
		_Compass();
	}

	if (bShowHost) {
		if (MenuVars.openState == 0) {
			char _fps[64];
			_snprintf(_fps, 64, "FPS: %.0f", *(float*)(0x83BA2A18));

			DrawText("Target Details", cgArray_s->RefDef.Width - TextWidth("Target Details", "fonts/720/normalFont") * 0.5 - 50, 250, "fonts/720/normalFont", 0.5, defaultColor);
			DrawText(_fps, cgArray_s->RefDef.Width - TextWidth(_fps, "fonts/720/normalFont") * 0.5 - 50, 230, "fonts/720/normalFont", 0.5, defaultText);

			if (ClosestPlayer != -1) {
				char _id[64];
				char _name[64];
				char _distance[64];
				char _visible[64];

				_snprintf(_id, 64, "ID: %i", ClosestPlayer);
				_snprintf(_name, 64, "Name: %s", cgArray_s->ClientInfo[ClosestPlayer].Name);
				_snprintf(_distance, 64, "Distance: %.1f", GetDistance(Centity_s[ClosestPlayer].Origin, Centity_s[cgArray_s->ClientNumber].Origin));
				_snprintf(_visible, 64, "Visible: %s", Aimtarget_isTargetVisible(0, &Centity_s[ClosestPlayer], SL_GetString("j_head", 0)) ? "Yes" : "No");

				DrawText(_id, cgArray_s->RefDef.Width - TextWidth(_id, "fonts/720/normalFont") * 0.5 - 50, 270, "fonts/720/normalFont", 0.5, defaultText);
				DrawText(_name, cgArray_s->RefDef.Width - TextWidth(_name, "fonts/720/normalFont") * 0.5 - 50, 290, "fonts/720/normalFont", 0.5, defaultText);
				DrawText(_distance, cgArray_s->RefDef.Width - TextWidth(_distance, "fonts/720/normalFont") * 0.5 - 50, 310, "fonts/720/normalFont", 0.5, defaultText);
				DrawText(_visible, cgArray_s->RefDef.Width - TextWidth(_visible, "fonts/720/normalFont") * 0.5 - 50, 330, "fonts/720/normalFont", 0.5, defaultText);

			}
			else {
				DrawText("N/A", cgArray_s->RefDef.Width - TextWidth("N/A", "fonts/720/normalFont") * 0.5 - 50, 270, "fonts/720/normalFont", 0.5, defaultText);
			}
		}
	}

	/*if (bProximity) {
		if (CloseToMe()) {
			DrawText("* Enemy Near *", cgArray_s->RefDef.Width / 2 - TextWidth("* Enemy Near *", "fonts/smallDevFont") / 2, 230, "fonts/smallDevFont", 1, colRED);
		}
	}*/

	if (bVisible) {
		if (isAnyVis(cgArray_s->ClientNumber)) {
			DrawText("* Enemy Visible *", cgArray_s->RefDef.Width / 2 - TextWidth("* Enemy Visible *", "fonts/smallDevFont") / 2, 250, "fonts/smallDevFont", 1, colRED);
		}
	}

	if (bTriggerbot)
		_Triggerbot();

	_DrawMenu();

	// Reverse R_EndFrame
	_Aimbot();
}

int GetAAClient()
{
	int viableClient = -1;

	float nearestDistance = 99999999;

	for (int i = 0; i < 18; i++)
	{
		if (i == cgArray_s->ClientNumber)
			continue;

		if (!isEntityPlayer(i))
			continue;

		if (!IsEnemy(i))
			continue;

		float Distance = GetDistance(GetPlayerOrigin(cgArray_s->ClientNumber), GetPlayerOrigin(i));

		if (Distance < nearestDistance)
		{
			nearestDistance = Distance;
			viableClient = i;
		}
	}
	return viableClient;
}

void EdgeAngleByIndex(int index, float *AngleX, float *AngleY)
{
	switch (index)
	{
	default:
		if (AngleX)
			*AngleX = 0.0f;

		if (AngleY)
			*AngleY = 0.0f;
		break;

	case 0:
		if (AngleX)
			*AngleX += 30.0f;

		if (AngleY)
			*AngleY += 0.0f;
		break;

	case 1:
		if (AngleX)
			*AngleX += 30.0f;

		if (AngleY)
			*AngleY -= 30.0f;
		break;

	case 2:
		if (AngleX)
			*AngleX += 0.0f;

		if (AngleY)
			*AngleY -= 30.0f;
		break;

	case 3:
		if (AngleX)
			*AngleX -= 30.0f;

		if (AngleY)
			*AngleY -= 30.0f;
		break;

	case 4:
		if (AngleX)
			*AngleX -= 30.0f;

		if (AngleY)
			*AngleY -= 0.0f;
		break;

	case 5:
		if (AngleX)
			*AngleX -= 30.0f;

		if (AngleY)
			*AngleY += 30.0f;
		break;

	case 6:
		if (AngleX)
			*AngleX -= 0.0f;

		if (AngleY)
			*AngleY += 30.0f;
		break;

	case 7:
		if (AngleX)
			*AngleX += 30.0f;

		if (AngleY)
			*AngleY += 30.0f;
		break;
	}
}

#define ANGLE_DOWN 69.99999999999999f
#define ANGLE_UP -69.99999999999999f

bool bDelayShoot = false;
bool bDelayTrigger = false;
bool bBurstTrigger = false;
int dwShootDelay;
int dwBurstDelay;

int __declspec(naked) H_CL_WritePacketStub(int r3)
{
	__asm
	{
		li r3, 8
		nop
		nop
		nop
		nop
		nop
		nop
		blr
	}
}

int dwAirTick = 0;
int dwStickTick = 0;
int dwLagTick = 0;
bool bInAir;
bool bStickWait;

bool bSendPacket;

struct ClientInfo2
{
	int Client;
	int cEntity;
	float Pos[3];
	float AngleToSet[3];
	float Distance;
	bool Use;
};

ClientInfo2 AimClient;

int H_CL_WritePacket(int r3)
{
	if (!*(int*)0x82BBC554 || !*(int*)0x82C70F4C || !*(int*)0x82BBAE68)
	{ return H_CL_WritePacketStub(r3); }
	if (!Dvar_GetBool("cl_ingame")) return H_CL_WritePacketStub(r3);

	GetStructs();

	bSendPacket = true;

	Usercmd_t* cur = &ClientActive->Usercmd[(ClientActive->CurrentCmdNumber) & 0x7F];
	Usercmd_t* newCmd = &ClientActive->Usercmd[(ClientActive->CurrentCmdNumber) & 0x7F];
	Usercmd_t* old = &ClientActive->Usercmd[(ClientActive->CurrentCmdNumber - 1) & 0x7F];

	memcpy(old, cur, sizeof(Usercmd_t));
	old->time -= 1;
	
	if (ClosestPlayer != -1) {
		if (bRagebot && bSilent) {
			float oldAngle = SHORT2ANGLE(old->viewAngles[1]);
			old->viewAngles[0] = ANGLE2SHORT(FinalAngles.x);
			old->viewAngles[1] = ANGLE2SHORT(FinalAngles.y);
			FixMovement(old, SHORT2ANGLE(old->viewAngles[1]), oldAngle, (float)old->fDir, (float)old->rDir);
		}

		if (bNoSpread)
			_spreadFix(old);
	}

	if (!bTriggerShoot) {
		dwShootDelay = 0;
		bDelayShoot = false;
		bDelayTrigger = false;
	}

	if (!bDelayShoot && bTriggerShoot) {
		dwShootDelay = GetTickCount();
		bDelayShoot = true;
	}

	if (bDelayShoot && GetTickCount() - dwShootDelay > (int)fTriggerDelay)
		bDelayTrigger = true;

	if (bBurstFire)
	{
		if (!bBurstTrigger && bDelayTrigger) {
			dwBurstDelay = GetTickCount();
			bBurstTrigger = true;
		}

		if (bBurstTrigger) {
			if (GetTickCount() - dwBurstDelay > 500)
			{
				bBurstTrigger = false;
				bDelayTrigger = false;
				dwBurstDelay = 0;
			}
			else
			{
				bDelayTrigger = true;
			}
		}
	}

	if ((bLegitbot && bTriggerbot && bDelayTrigger) || (bRagebot && bAutoShoot && ClosestPlayer != -1))
	{
		cur->buttons |= 0x80000000;
		//old->buttons &= ~CMD_MASK_FIRE;
		cur->buttons |= CMD_MASK_FIRE;
	}

	bTriggerShoot = false;

	if (bRapidFire && cur->buttons & 1) {
		newCmd->buttons &= ~1;
	}

	if (!(cur->buttons & 1))
	{
		if (bFakeLag)
		{
			if (GetTickCount() - dwLagTick > fLag)
				dwLagTick = GetTickCount();
			else
				bSendPacket = false;
		}

		if (bAirStuck)
		{
			if (GetAsyncKeyState(XINPUT_GAMEPAD_A))
				bStickWait = true;

			if (bStickWait) {
				if (GetTickCount() - dwStickTick > 250) {
					dwStickTick = GetTickCount();
					bInAir = true;
					bStickWait = false;
				}
			}

			if (bInAir) {
				bSendPacket = false;

				if (GetTickCount() - dwAirTick > (fLag * 5)) {
					dwAirTick = GetTickCount();
					bInAir = false;
					bSendPacket = true;
				}
			}
		}
	}

	if (bAntiAim && bRagebot) {
		float oldAngleX = SHORT2ANGLE(newCmd->viewAngles[1]);

		int viableClient = GetAAClient();

		if (xAntiAim_c == 1 || yAntiAim_c == 1) {
			if (viableClient != -1) {
				Vector3 Pos = GetTagPos(viableClient, "j_head");
				Vector3 Angle = vectoangles(Pos - cgArray_s->RefDef.viewOrigin);
				Angle.x -= ClientActive->baseAngle[0];
				Angle.y -= ClientActive->baseAngle[1];

				Angle.y -= 160.0f;

				if (xAntiAim_c == 1)
					newCmd->viewAngles[1] = ANGLE2SHORT(Angle.y);

				if (yAntiAim_c == 1)
					newCmd->viewAngles[0] = ANGLE2SHORT(Angle.x);
			}
		}

		if (xAntiAim_c == 2) {
			if (spinAngle > 360)
				spinAngle -= 360;

			spinAngle += 40.0f;

			newCmd->viewAngles[1] = ANGLE2SHORT(spinAngle);
		}

		if (xAntiAim_c == 3)
			newCmd->viewAngles[1] -= ANGLE2SHORT(!(newCmd->time % 2) ? 180.0f : 0.0f);

		if (xAntiAim_c == 4)
			newCmd->viewAngles[1] -= ANGLE2SHORT(rand() % 2 ? 135.0f : 225.0f);

		if (xAntiAim_c == 5) {
			if (!(newCmd->time % 2))
				newCmd->viewAngles[1] -= ANGLE2SHORT(rand() % 2 ? 135.0f : 225.0f);
			else
				newCmd->viewAngles[1] -= ANGLE2SHORT(rand() % 2 ? 45.0f : -45.0f);
		}

		if (yAntiAim_c == 2 || yAntiAim_c == 3)
			newCmd->viewAngles[0] = ANGLE2SHORT((!(newCmd->time % 2) ? ANGLE_DOWN : ANGLE_UP) - ClientActive->baseAngle.x);

		if (yAntiAim_c == 4)
			newCmd->viewAngles[0] = ANGLE2SHORT(ANGLE_DOWN - ClientActive->baseAngle.x);

		if (yAntiAim_c == 5)
			newCmd->viewAngles[0] = ANGLE2SHORT(ANGLE_UP - ClientActive->baseAngle.x);

		/*if (zAntiAim_c == 1) {
		if (rollAngle > 360)
		rollAngle -= 360;

		rollAngle += 15.0f;

		newCmd->viewAngles[2] = ANGLE2SHORT(rollAngle);
		}

		if (zAntiAim_c == 2)
		newCmd->viewAngles[2] = ANGLE2SHORT(90.0f);

		if (zAntiAim_c == 3)
		newCmd->viewAngles[2] = ANGLE2SHORT(180.0f);

		if (zAntiAim_c == 4)
		newCmd->viewAngles[2] = ANGLE2SHORT(FloatMinMax(0.0f, 360.0f));


		*/
		if (xAntiAim_c == 6) {
			Vector3 Pos = GetTagPos(viableClient, "j_head");
			Vector3 Angle = vectoangles(Pos - cgArray_s->RefDef.viewOrigin);
			Angle.x -= ClientActive->baseAngle[0];
			Angle.y -= ClientActive->baseAngle[1];

			Angle.y -= 90.0f;

			newCmd->viewAngles[1] = ANGLE2SHORT(Angle.y);
		}
		if (xAntiAim_c == 7)
			newCmd->viewAngles[1] = ANGLE2SHORT(FloatMinMax(0.0f, 360.0f));

		if (yAntiAim_c == 6)
			newCmd->viewAngles[0] = ANGLE2SHORT(FloatMinMax(ANGLE_UP, ANGLE_DOWN) - ClientActive->baseAngle.x);

		/*
		if (wallDetect_c > 0) {
			// Define client entity index
			int localClient = cgArray_s->ClientNumber;

			// If we have a target, and client is alive
			if (viableClient != -1 && isEntityPlayer(localClient))
			{
				// Set starting origins
				Vector3 tracePoint[8], successAngle;

				for (int i = 0; i < 8; i++)
				{
					tracePoint[i] = GetTagPos(localClient, "j_mainroot");

					// Modify x / y origin of trace starting point
					EdgeAngleByIndex(i, &tracePoint[i].x, &tracePoint[i].y);

					// Check if bullet trace returns false
					if (!CanKillPlayer(viableClient, tracePoint[i])) {
						// Calculate angle to failed bullet trace
						successAngle = vectoangles(tracePoint[i] - cgArray_s->RefDef.viewOrigin) - ClientActive->baseAngle;

						// Set fake X angle
						newCmd->viewAngles[1] = ANGLE2SHORT(successAngle.y);

						// Modify based on edge type
						if (wallDetect_c == 2)
							newCmd->viewAngles[1] -= ANGLE2SHORT(rand() ? 45.0f : -45.0f);

						if (wallDetect_c == 3)
							newCmd->viewAngles[1] -= ANGLE2SHORT(!(newCmd->time % 2) ? 180.0f : 0.0f);
					}
				}
			}
		}
		*/

		if (!(cur->buttons & 1)) {
			if (xAntiAim_c == 3 || xAntiAim_c == 4 || xAntiAim_c == 5 || yAntiAim_c == 3 || wallDetect_c == 3) {
				if (newCmd->time % 2)
					bSendPacket = false;
			}
		}
	}

	if (bSendPacket)
		return H_CL_WritePacketStub(r3);
}


DWORD __declspec(naked) XamInputGetStateHook_Stub(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState)
{
	__asm
	{
		li r3, 1
		nop
		li r4, 1
		nop
		nop
		nop
		nop
		blr
	}
}

DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState)
{
	DWORD dwResult = XamInputGetStateHook_Stub(dwUserIndex, r4, pState);

	if (dwUserIndex != 0 || dwResult != 0)
		return dwResult;

	if (MenuVars.openState > 0) {
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_UP;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_DOWN;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_LEFT;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_RIGHT;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_A;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_B;
	}

		if (bRagebot && !bSilent && ClosestPlayer != -1) {
			pState->Gamepad.sThumbRX = 0;
			pState->Gamepad.sThumbRY = 0;
		}
	return dwResult;
}

DWORD __declspec(naked) R_DrawIndexedPrimitiveStub(D3DDevice*,int,int,int,int)
{
	__asm
	{
		li r3, 2
		li r3, 1
		li r4, 2
		nop
		li r3, 2
		nop
		nop
		blr
	}
}


DWORD __declspec(naked) R_DrawXModelSkinnedCachedStub(int, int)
{
	__asm
	{
		li r3, 2
		li r3, 1
		li r4, 3
		nop
		nop
		nop
		nop
		blr
	}
}

D3DTexture* RedTexture = NULL;
D3DTexture* YellowTexture = NULL;
D3DTexture* SkyBlueTexture = NULL;
D3DTexture* GreenTexture = NULL;

HRESULT GenerateTexture(D3DDevice* Device, D3DTexture** Texture, DWORD Color)
{
	if (FAILED(Device->CreateTexture(4, 4, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, Texture, NULL)))
		return E_FAIL;

	WORD Color16 = ((WORD)((Color >> 28) & 0xF) << 12) | (WORD)(((Color >> 20) & 0xF) << 8) | (WORD)(((Color >> 12) & 0xF) << 4) | (WORD)(((Color >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*Texture)->LockRect(0, &d3dlr, 0, 0);

	WORD *Dst16 = (WORD*)d3dlr.pBits;

	for (INT xy = 0; xy < 8 * 8; xy++)
		*Dst16++ = Color16;

	(*Texture)->UnlockRect(0);

	return S_OK;
}

char* pShader;
int drawPlayer;
//8290E1A8
int R_DrawXModelSkinnedCached(int pDevice, int Args) {
	drawPlayer = 0;
	pShader = NULL;

	pShader = **(char ***)(pDevice + 0x128);
	D3DDevice *Device = *(D3DDevice **)(pDevice + 0xF0);

	if (Device) {
		if (!RedTexture || !YellowTexture || !SkyBlueTexture || !GreenTexture) {
			GenerateTexture(Device, &RedTexture, D3DCOLOR_RGBA(255, 0, 0, 255));
			GenerateTexture(Device, &YellowTexture, D3DCOLOR_RGBA(255, 255, 0, 255));
			GenerateTexture(Device, &SkyBlueTexture, D3DCOLOR_RGBA(0, 170, 255, 255));
			GenerateTexture(Device, &GreenTexture, D3DCOLOR_RGBA(0, 255, 0, 255));
		}

		//printf("%s %#08x\n", pShader, &Device);

		Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		Device->SetRenderState(D3DRS_ZENABLE, FALSE);

		R_DrawXModelSkinnedCachedStub(pDevice, Args);

		Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		Device->SetRenderState(D3DRS_ZENABLE, TRUE);

	}

	return R_DrawXModelSkinnedCachedStub(pDevice, Args);
}

//82903D60
int R_DrawIndexedPrimitive(D3DDevice *Device, int r4, int r5, int r6, int r7) {
	if (Device) {
		if (!RedTexture || !YellowTexture || !SkyBlueTexture || !GreenTexture) {
			GenerateTexture(Device, &RedTexture, D3DCOLOR_RGBA(255, 0, 0, 255));
			GenerateTexture(Device, &YellowTexture, D3DCOLOR_RGBA(255, 255, 0, 255));
			GenerateTexture(Device, &SkyBlueTexture, D3DCOLOR_RGBA(0, 170, 255, 255));
			GenerateTexture(Device, &GreenTexture, D3DCOLOR_RGBA(0, 255, 0, 255));
		}
		Device->SetTexture(0, GreenTexture);
		//Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	return R_DrawIndexedPrimitiveStub(Device, r4, r5, r6, r7);
}