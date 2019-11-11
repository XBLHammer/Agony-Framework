void _DrawMenu()
{
	//DrawText(szMenuName, 50, uicontext.screenHeight - 290, "fonts/hudbigfont", 0.35, fclFlashMain);

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

				float flBoxH = 3.0f + MenuVars.GroupHeight[CurrentMenu][i] * 20.0f;

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
					DrawText(ArrayText, t_flX + 14 + 40 - ((TextWidth(ArrayText, szOptionFont) * 0.25) / 2), t_flY, szOptionFont, 0.25, defaultText);
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

				DrawText(ArrayText, t_flX + 40 - ((TextWidth(ArrayText, szOptionFont) * 0.25) / 2), t_flY + 6, szOptionFont, 0.25, defaultText);
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
				DrawText(ComboArray[i], flComboX + 40 - ((TextWidth(ComboArray[i], "fonts/hudbigfont") * 0.25) / 2), flComboY + 3 + (15 * i), "fonts/hudbigfont", 0.25, defaultText);

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

		if (CurrentMenu == 6 && Dvar_GetBool("cl_ingame")) {
			if (strcmp(cgArray_s->ClientInfo[CurrentOption].Name, "")) {
				DrawShader(0, RadarCenter.y - RadarSize / 2 + 280, 245, 80, defaultShader, "white");
				unsigned char StringIP[4];
				int IP = (GetIP(XNADDRA(CurrentOption)));
				memcpy(StringIP, (void*)IP, 4);
				const char player_ip[50] = "";
				_snprintf((char*)player_ip, 50, "%u.%u.%u.%u", StringIP[0], StringIP[1], StringIP[2], StringIP[3]);

				char _clientBuff[512];// = new char[512];

				_snprintf(_clientBuff, 512, "Prioritized: %s\nFriendly: %s\nBody Aim: %s\nIP: %s\nEnemy: %s\nWeapon: %s",
					bPlayerPriority[CurrentOption] ? "True" : "False",
					bPlayerFriendly[CurrentOption] ? "True" : "False",
					bPlayerBodyAim[CurrentOption] ? "True" : "False",
					CurrentOption == cgArray_s->ClientNumber ? "1.3.3.7" : player_ip,
					IsEnemy(CurrentOption) ? "True" : "False",
					GetWeaponName(Centity_s[CurrentOption].WeaponID));

				DrawText(_clientBuff, 8, RadarCenter.y - RadarSize / 2 + 280 + 15, "fonts/hudbigfont", 0.3, defaultText);

			}
		}
	}
	else if (MenuVars.openState == 2)
	{
		float fRGBW = 300;
		float fRGBH = 150;
		float fRGBX = uicontext.screenWidth / 2 - (fRGBW / 2);
		float fRGBY = uicontext.screenHeight / 2 - (fRGBH / 2);
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
	if (GetTickCount() - Upd_t > 2000)
	{
		Upd_t = GetTickCount();

		UpdateFOV();

		//CL_AddReliableCommand(0, "s");

		if (bProcessClient) {
			_AddBot();
			bProcessClient = false;
		}

		//*(int *)0x820E1724 = 0x7D284B78;//infinite ammo
		//Cbuf_AddText(0, ";perk_bulletPenetrationMultiplier 999;perk_bulletDamage 999;");

		if (bXHair)
			*(char*)(*(int*)(0x825B8520) + 0x08) = 0x00;
		else
			*(char*)(*(int*)(0x825B8520) + 0x08) = 0x01;

		if (bDrawName) {
			*(char*)(*(int*)(0x825BE7CC) + 0x08) = 0x00;
			*(char*)(*(int*)(0x825BE7C8) + 0x08) = 0x00;
		}
		else {
			*(char*)(*(int*)(0x825BE7CC) + 0x08) = 0x01;
			*(char*)(*(int*)(0x825BE7C8) + 0x08) = 0x01;
		}

		if (bFlashFx) {
			*(char*)(*(int*)(0x825B8594) + 0x8) = 0x00;
			*(char*)(*(int*)(0x825B8540) + 0x8) = 0x00;
		}

		if (bKillfeed) {
			Cbuf_AddText(0, ";reset activeaction;set timescale 1;set con_gameMsgWindow0MsgTime 300;set con_gameMsgWindow0LineCount 8;");
		}
	}
}

void H_R_SetFrameFog()
{
	if (!*(int*)0x825B8638 || !*(int*)0x82682354 || !*(int*)0x825BE150)
		return;

	if (!bStructs)
		GetStructs();

	FuncUpdate();

	if (!Dvar_GetBool("cl_ingame"))
		return;

	if (!isEntityPlayer(cgArray_s->ClientNumber))
		return;

	if (bLegitbot && bRagebot)
		bLegitbot = false;

	if (bXHair && MenuVars.openState == 0)
	{
		if (isEntityPlayer(cgArray_s->ClientNumber))
		{
			float xHairSize = (8 + (cgArray_s->SpreadMultiplier / 4));

			float xHairWidth = ((cgArray_s->RefDef.Width / 2) - 2 + 71.75 + 8) - ((cgArray_s->RefDef.Width / 2) - 8 - 71.75) + 40;

			if (bXHairSpread)
			{
				DrawShader((cgArray_s->RefDef.Width / 2) - 8 - xHairSize, cgArray_s->RefDef.Height / 2 - 1, 8, 1, fclFlashMain, "white");
				DrawShader((cgArray_s->RefDef.Width / 2) - 1 + xHairSize, cgArray_s->RefDef.Height / 2 - 1, 8, 1, fclFlashMain, "white");

				DrawShader((cgArray_s->RefDef.Width / 2) - 1, cgArray_s->RefDef.Height / 2 - xHairSize - 8, 1, 8, fclFlashMain, "white");
				DrawShader((cgArray_s->RefDef.Width / 2) - 1, cgArray_s->RefDef.Height / 2 + xHairSize - 1, 1, 8, fclFlashMain, "white");
			}

			//drawMat(cgArray_s->RefDef.Width / 2 - 50, cgArray_s->RefDef.Height / 2, 100, 1.7, 0, colWHITE);
			//drawMat(cgArray_s->RefDef.Width / 2 - 50, 422, 50, 1.7, 0, colWHITE);
			//drawMat(cgArray_s->RefDef.Width / 2 - 2, cgArray_s->RefDef.Height / 2 - 50, 1.7, 100, 0, colWHITE);
			//drawMat(cgArray_s->RefDef.Width / 2 - 50, cgArray_s->RefDef.Height / 2 - 50, 1.7, 50, 0, colWHITE);

			DrawShader(cgArray_s->RefDef.Width / 2 - 1, cgArray_s->RefDef.Height / 2 - 15, 1, 30, fclFlashMain, "white");
			DrawShader(cgArray_s->RefDef.Width / 2 - 15, cgArray_s->RefDef.Height / 2 - 1, 30, 1, fclFlashMain, "white");
		}
	}

	_ESP();

	if (bRadar) {
		_Radar();
	}

	if (drawRadar) {
		Radar();
	}

	if (bCompass) {
		_Compass();
	}

	if (bShowHost) {
		//char _ping[64];

		char _fps[64];
		char _host[64];
		char _map[64];
		char _resolution[64];
		char _game[64];

		_snprintf(_host, 64, "Host: %s", cgArray_s->pCgs.hostName);
		_snprintf(_fps, 64, "FPS: %.0f", uicontext.FPS / 1.95641547);
		_snprintf(_map, 64, "Map: %s", UI_GetMapName(Dvar_GetString("ui_mapname")));
		_snprintf(_game, 64, "Game: %s", UI_GetGameTypeName(Dvar_GetString("ui_gametype")));
		_snprintf(_resolution, 64, "Resolution: %i x %i", uicontext.screenWidth, uicontext.screenHeight);

		SetTextWithBackground(_host, cgArray_s->RefDef.Width - TextWidth(_host, "fonts/hudbigfont") * 0.35 - 50, 30, "fonts/hudbigfont", 0.35, defaultText);
		SetTextWithBackground(_fps, cgArray_s->RefDef.Width - TextWidth(_fps, "fonts/hudbigfont") * 0.35 - 50, 50, "fonts/hudbigfont", 0.35, defaultText);
		SetTextWithBackground(_map, cgArray_s->RefDef.Width - TextWidth(_map, "fonts/hudbigfont") * 0.35 - 50, 70, "fonts/hudbigfont", 0.35, defaultText);
		SetTextWithBackground(_game, cgArray_s->RefDef.Width - TextWidth(_game, "fonts/hudbigfont") * 0.35 - 50, 90, "fonts/hudbigfont", 0.35, defaultText);
		SetTextWithBackground(_resolution, cgArray_s->RefDef.Width - TextWidth(_resolution, "fonts/hudbigfont") * 0.35 - 50, 110, "fonts/hudbigfont", 0.35, defaultText);


		//score_t *score = GetScoreForClient(cgArray_s->ClientNumber);
		//SetTextWithBackground(_ping, 50, cgArray_s->RefDef.Height - 170, "fonts/hudbigfont", 0.35, defaultText);

		if (MenuVars.openState == 0) {
			SetTextWithBackground("Target Details", cgArray_s->RefDef.Width - TextWidth("Target Details", "fonts/hudbigfont") * 0.35 - 50, 140, "fonts/hudbigfont", 0.35, defaultColor);

			if (ClosestPlayer != -1) {
				char _id[64];
				char _name[64];
				char _distance[64];
				char _visible[64];

				_snprintf(_id, 64, "ID: %i", ClosestPlayer);
				_snprintf(_name, 64, "Name: %s", cgArray_s->ClientInfo[ClosestPlayer].Name);
				_snprintf(_distance, 64, "Distance: %.1f", GetDistance(Centity_s[ClosestPlayer].Origin, Centity_s[cgArray_s->ClientNumber].Origin));
				_snprintf(_visible, 64, "Visible: %s", Aimtarget_isTargetVisible(0, &Centity_s[ClosestPlayer], autowallBox[1]) ? "Yes" : "No");

				SetTextWithBackground(_id, cgArray_s->RefDef.Width - TextWidth(_id, "fonts/hudbigfont") * 0.35 - 50, 160, "fonts/hudbigfont", 0.35, defaultText);
				SetTextWithBackground(_name, cgArray_s->RefDef.Width - TextWidth(_name, "fonts/hudbigfont") * 0.35 - 50, 180, "fonts/hudbigfont", 0.35, defaultText);
				SetTextWithBackground(_distance, cgArray_s->RefDef.Width - TextWidth(_distance, "fonts/hudbigfont") * 0.35 - 50, 200, "fonts/hudbigfont", 0.35, defaultText);
				SetTextWithBackground(_visible, cgArray_s->RefDef.Width - TextWidth(_visible, "fonts/hudbigfont") * 0.35 - 50, 220, "fonts/hudbigfont", 0.35, defaultText);

			}
			else {
				SetTextWithBackground("N/A", cgArray_s->RefDef.Width - TextWidth("N/A", "fonts/hudbigfont") * 0.35 - 50, 160, "fonts/hudbigfont", 0.35, defaultText);
			}
		}
	}

	if (bProximity) {
		//if (CloseToMe()) {
			//SetTextWithBackground("* Enemy Near *", cgArray_s->RefDef.Width / 2 - TextWidth("* Enemy Near *", "fonts/hudbigfont") / 2 * 0.35, 230, "fonts/hudbigfont", 0.35, colRED);
		//}
	}

	if (bVisible) {
		if (ClosestPlayer != -1 && Aimtarget_isTargetVisible(0, &Centity_s[ClosestPlayer], autowallBox[1])) {
			SetTextWithBackground("* Enemy Visible *", cgArray_s->RefDef.Width / 2 - TextWidth("* Enemy Visible *", "fonts/hudbigfont") / 2 * 0.35, 250, "fonts/hudbigfont", 0.35, colRED);
		}
	}

	if (bTriggerbot)
		_Triggerbot();
}

Detour<HRESULT> *H_Menu_PaintAllDetour;

HRESULT H_Menu_PaintAll(INT r3) {
	int linkRet;
	_asm mflr linkRet;

	H_Menu_PaintAllDetour->CallOriginal(r3);

	if (linkRet == 0x82276A98) {
		if (*(char*)0x831A11A5 == 0x01) {
			*(char*)0x831A11A5 = 0x31;
		}

		pgStructs();

		_DrawMenu();
	}
}

bool bDead;

DWORD dwRespawn;

void H_R_EndFrame()
{
	((void(*)(...))0x8234F6A0)(); //R_AddCmdEndOfList

	*(int*)(0x83AE2D34) = ((*(int*)(0x83AE2D34) + -1) & 1);

	GfxBackEndData* Current = *(GfxBackEndData**)(*(int*)(0x83AE2D00) + 0x15B4);

	Current->usedTotal = 0;
	Current->usedCritical = 0;
	Current->lastCmd = 0;

	*(int*)(0x83AE2C60) = 0;

	if (!(((int(*)(...))0x8223D220)() & 0xFF))
		return;

	if (*(int*)0x83CE7F00)
		return;

	((void(*)(...))0x82379BC8)(0x1B);

	if (!*(int*)0x825B8638 || !*(int*)0x82682354 || !*(int*)0x825BE150) return;
	if (!Dvar_GetBool("cl_ingame")) return;

	if (!bStructs)
		GetStructs();

	if (cgArray_s->Health <= 0)
		bDead = true;

	if (bDead && cgArray_s->Health > 0) {
		if (GetTickCount() - dwRespawn > 1000) {
			dwRespawn = GetTickCount();
			bDead = false;
			printf("Spawned\n");
		}
	}

	_Aimbot();
}

int __declspec(naked) H_CL_CreateNewCommandsStub(int r3)
{
	__asm
	{
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		blr
	}
}

int GetClosestAircraft() {
	int dwClosestAircraft = -1;
	for (int i = 0; i < 2048; i++) {
		if (Centity_s[i].Type != ET_PLANE && Centity_s[i].Type != ET_HELICOPTER)
			continue;

		if (!(Centity_s[i].Alive & 0x0C || Centity_s[i].Alive & 0x0D))
			continue;

		return i;
	}

	return -1;
}

#define ANGLE_DOWN 69.99999999999999f
#define ANGLE_UP -69.99999999999999f

bool bDelayShoot = false;
bool bDelayTrigger = false;
bool bBurstTrigger = false;
int dwShootDelay;
int dwBurstDelay;

bool bCNC_Return = false;

int H_CL_CreateNewCommands(int r3)
{
	if (!*(int*)0x825B8638 || !*(int*)0x82682354 || !*(int*)0x825BE150) { return H_CL_CreateNewCommandsStub(r3); }
	if (!Dvar_GetBool("cl_ingame")) return H_CL_CreateNewCommandsStub(r3);

	if (!bStructs)
		GetStructs();

	bCNC_Return = true;

	Usercmd_t* cur = &ClientActive->Usercmd[(ClientActive->CurrentCmdNumber) & 0x7F];
	Usercmd_t* old = &ClientActive->Usercmd[(ClientActive->CurrentCmdNumber - 1) & 0x7F];
	Usercmd_t* newCmd = &ClientActive->Usercmd[(ClientActive->CurrentCmdNumber + 2) & 0x7F];

	*old = *cur;
	--old->time;

	if (ClosestPlayer != -1) {
		if (bRagebot && bSilent) {
			float oldAngle = SHORT2ANGLE(old->viewAngles[1]);
			old->viewAngles[0] = ANGLE2SHORT(FinalAngles.x);
			old->viewAngles[1] = ANGLE2SHORT(FinalAngles.y);
			FixMovement(old, SHORT2ANGLE(old->viewAngles[1]), oldAngle, (float)old->fDir, (float)old->rDir);
		}

		if (bRapidFire && bRagebot && bAutoShoot || bRapidFire && bRagebot && bAutoShoot && bSilent)
			old->buttons &= ~1;

		if (bRagebot && bAutoShoot)
			old->buttons |= 1;
	}

	if (old->buttons & 1 && bNoSpread) {
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

	if (bLegitbot && bTriggerbot && bDelayTrigger)
		old->buttons |= 1;

	if (bAutoAim) {
		if (ClosestPlayer != -1)
			ClientActive->ADS = true;
		else
			ClientActive->ADS = false;
	}

	bTriggerShoot = false;

	if (bAntiAim && bRagebot) {
		if (cgArray_s->Weapon > 0 && !(Centity_s[cgArray_s->ClientNumber].Flags & FLAG_PRONE)) {
			newCmd = cur;

			int viableClient = GetAAClient();

			if (xAntiAim_c == 0 || yAntiAim_c == 0) {
				int dwHarrier = GetClosestAircraft();

				if (bHarrierRiot && dwHarrier != -1) {
					Vector3 Angle = vectoangles(Centity_s[dwHarrier].Origin - cgArray_s->RefDef.viewOrigin) - ClientActive->baseAngle;

					Angle.x = ANGLE_DOWN - ClientActive->baseAngle.x;
					Angle.y -= 180;

					newCmd->viewAngles[0] = ANGLE2SHORT(Angle.x);
					newCmd->viewAngles[1] = ANGLE2SHORT(Angle.y);
				}
				else {
					if (viableClient != -1) {
						Vector3 Pos = GetTagPos(viableClient, "j_head");
						Vector3 Angle = vectoangles(Pos - cgArray_s->RefDef.viewOrigin);
						Angle.x -= ClientActive->baseAngle[0];
						Angle.y -= ClientActive->baseAngle[1];

						Angle.y -= 170.0f;

						if (xAntiAim_c == 1)
							newCmd->viewAngles[1] = ANGLE2SHORT(Angle.y);

						if (yAntiAim_c == 1)
							newCmd->viewAngles[0] = ANGLE2SHORT(Angle.x);
					}
				}
			}

			if (xAntiAim_c == 2) {
				if (spinAngle > 360)
					spinAngle -= 360;

				spinAngle += fSpinSpeed;

				newCmd->viewAngles[1] = ANGLE2SHORT(spinAngle);
			}

			if (xAntiAim_c == 3)
				newCmd->viewAngles[1] -= ANGLE2SHORT(!(newCmd->time % 2) ? 180.0f : 0.0f);

			if (xAntiAim_c == 4)
				newCmd->viewAngles[1] -= ANGLE2SHORT(rand() % 2 ? 135.0f : 225.0f);

			if (xAntiAim_c == 5) {
				newCmd->viewAngles[1] -= ANGLE2SHORT(rand() % 2 ? 90.0f : -90.0f);
			}

			if (yAntiAim_c == 2 || yAntiAim_c == 3)
				newCmd->viewAngles[0] = ANGLE2SHORT((!(newCmd->time % 2) ? ANGLE_DOWN : ANGLE_UP) - ClientActive->baseAngle.x);

			if (yAntiAim_c == 4)
				newCmd->viewAngles[0] = ANGLE2SHORT(ANGLE_DOWN - ClientActive->baseAngle.x);

			if (yAntiAim_c == 5)
				newCmd->viewAngles[0] = ANGLE2SHORT(ANGLE_UP - ClientActive->baseAngle.x);

			if (zAntiAim_c == 1) {
				if (rollAngle > 360)
					rollAngle -= 360;

				rollAngle += fRollSpeed;

				newCmd->viewAngles[2] = ANGLE2SHORT(rollAngle);
			}

			if (zAntiAim_c == 2)
				newCmd->viewAngles[2] = ANGLE2SHORT(90.0f);

			if (zAntiAim_c == 3)
				newCmd->viewAngles[2] = ANGLE2SHORT(180.0f);

			if (xAntiAim_c == 7)
				newCmd->viewAngles[1] = ANGLE2SHORT(FloatMinMax(fRndXMin, fRndXMax));

			if (yAntiAim_c == 6)
				newCmd->viewAngles[0] = ANGLE2SHORT(FloatMinMax(ANGLE_UP, ANGLE_DOWN) - ClientActive->baseAngle.x);

			if (zAntiAim_c == 4)
				newCmd->viewAngles[2] = ANGLE2SHORT(FloatMinMax(0.0f, 360.0f));

			if (wallDetect_c > 0) {
				// Define client entity index
				int localClient = cgArray_s->ClientNumber;

				// If we have a target, and client is alive
				if (viableClient != -1 && isEntityPlayer(localClient)) {
					// Check if bullet trace returns false
					if (EntityWall(viableClient, cgArray_s->RefDef.viewOrigin, GetTagPos(viableClient, "tag_eye"), autowallBox[1]) && !Aimtarget_isTargetVisible(0, &Centity_s[viableClient], autowallBox[10])) {
						// Set fake Y angle
						newCmd->viewAngles[0] = ANGLE2SHORT(ANGLE_DOWN - ClientActive->baseAngle.x);
						newCmd->viewAngles[1] = ANGLE2SHORT(cgArray_s->ViewAngle.y + 55.0f);

						// Modify based on edge type
						if (wallDetect_c == 2)
							newCmd->viewAngles[1] -= ANGLE2SHORT(rand() ? 90.0f : -90.0f);

						if (wallDetect_c == 3)
							newCmd->viewAngles[1] -= ANGLE2SHORT(!(newCmd->time % 2) ? 170.0f : 0.0f);
					}
				}
			}

			if (!(cur->buttons & 1)) {
				if (xAntiAim_c == 3 || xAntiAim_c == 4 || yAntiAim_c == 3 || wallDetect_c == 3) {
					if (newCmd->time % 2)
						bCNC_Return = false;
				}
			}
		}
	}

	if (bCNC_Return)
		return H_CL_CreateNewCommandsStub(r3);
}


int __declspec(naked) H_CL_WritePacketStub(int r3)
{
	__asm
	{
		li r3, 1
		nop
		nop
		nop
		nop
		nop
		nop
		blr
	}
}

enum CommandMask
{
	CMD_MASK_FIRE = 0x00000001,
	CMD_MASK_AIM = 0x00080800,
	CMD_MASK_JUMP = 0x00000400
};

int dwAirTick = 0;
int dwStickTick = 0;
int dwLagTick = 0;
bool bInAir;
bool bStickWait;

bool bSendPacket;

int H_CL_WritePacket(int r3)
{
	if (!*(int*)0x825B8638 || !*(int*)0x82682354 || !*(int*)0x825BE150) { return H_CL_WritePacketStub(r3); }
	if (!Dvar_GetBool("cl_ingame")) return H_CL_WritePacketStub(r3);

	if (!bStructs)
		GetStructs();

	bSendPacket = true;

	Usercmd_t* cur = &ClientActive->Usercmd[(ClientActive->CurrentCmdNumber) & 0x7F];

	if (!(cur->buttons & 1)) {
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

	if (bSendPacket)
		return H_CL_WritePacketStub(r3);
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

Detour<HRESULT> *H_R_DrawIndexedPrimitiveDetour;
HRESULT H_R_DrawIndexedPrimitive(D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT IndexCount, char *pShader, int linkRet) {
	int playerTeam = 0;

	if (linkRet == 0x82398344)
	{
		if (pDevice && bChams) {
			if (!RedTexture || !YellowTexture || !SkyBlueTexture || !GreenTexture) {
				GenerateTexture(pDevice, &RedTexture, D3DCOLOR_RGBA(255, 0, 0, 255));
				GenerateTexture(pDevice, &YellowTexture, D3DCOLOR_RGBA(255, 255, 0, 255));
				GenerateTexture(pDevice, &SkyBlueTexture, D3DCOLOR_RGBA(0, 170, 255, 255));
				GenerateTexture(pDevice, &GreenTexture, D3DCOLOR_RGBA(0, 255, 0, 255));
			}

			if (strstr(pShader, "tf_141_") || (strstr(pShader, "_ally_tf141_") || (strstr(pShader, "udt") || (strstr(pShader, "sniper_ghillie") ||
				strstr(pShader, "us_army_") || (strstr(pShader, "seal_"))))))
				playerTeam = 1;

			else if (strstr(pShader, "opforce") || (strstr(pShader, "militia") || (strstr(pShader, "airborne_") || (strstr(pShader, "op_arctic") ||
				(strstr(pShader, "arctic_") || strstr(pShader, "arab") || strstr(pShader, "head_suren") || (strstr(pShader, "op_ghille")))))))
				playerTeam = 2;

			if (playerTeam == 1) {
				if (bWireframe) {
					pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

					pDevice->SetTexture(0, GreenTexture);

					H_R_DrawIndexedPrimitiveDetour->CallOriginal(pDevice, PrimitiveType, BaseVertexIndex, StartIndex, IndexCount);
				}

				if (bSolid) {
					pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

					pDevice->SetTexture(0, SkyBlueTexture);

					H_R_DrawIndexedPrimitiveDetour->CallOriginal(pDevice, PrimitiveType, BaseVertexIndex, StartIndex, IndexCount);
				}
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}

			if (playerTeam == 2) {
				if (bWireframe) {
					pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

					pDevice->SetTexture(0, RedTexture);

					H_R_DrawIndexedPrimitiveDetour->CallOriginal(pDevice, PrimitiveType, BaseVertexIndex, StartIndex, IndexCount);
				}

				if (bSolid) {
					pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

					pDevice->SetTexture(0, YellowTexture);

					H_R_DrawIndexedPrimitiveDetour->CallOriginal(pDevice, PrimitiveType, BaseVertexIndex, StartIndex, IndexCount);
				}
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}
		}
	}

	if (playerTeam == 0)
		return H_R_DrawIndexedPrimitiveDetour->CallOriginal(pDevice, PrimitiveType, BaseVertexIndex, StartIndex, IndexCount);
}

Detour<HRESULT> *H_DrawIndexedPrimitiveDetour;
HRESULT H_DrawIndexedPrimitive(INT pDevice, INT Args) {
	int linkRet;
	_asm mflr linkRet;

	char* pShader = **(char ***)((pDevice - 0x90) + 0xBC);
	D3DDevice *Device = *(D3DDevice **)(pDevice);

	return ((int(*)(...))0x820AF1D0)(Device, 4, 0, *(int*)(Args + 0x8), (*(int*)(Args + 0x4)) + ((*(int*)(Args + 0x4)) << 1), pShader, linkRet);
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

DWORD dwRapidMode;

DWORD dwStoreHealth;
DWORD dwCODDelay;
bool bCrouchState;

DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState)
{
	DWORD dwResult = XamInputGetStateHook_Stub(dwUserIndex, r4, pState);

	if (dwUserIndex != 0 /*|| dwResult != 0*/)
		return XInputGetStateEx(dwUserIndex, r4, pState);

	if (MenuVars.openState > 0) {
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_UP;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_DOWN;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_LEFT;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_RIGHT;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_A;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_B;
	}

	if (Dvar_GetBool("cl_ingame")) {
		if (MenuVars.openState > 0) {
			pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_UP;
			pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_DOWN;
			pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_LEFT;
			pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_RIGHT;
			pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_A;
			pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_B;
		}
	}

	if (Dvar_GetBool("cl_ingame") && cgArray_s != NULL) {
		if (bCrouchBot) {
			if (GetTickCount() - dwCrouchTime > (int)fCrouchInteval) {
				dwCrouchTime = GetTickCount();
				pState->Gamepad.wButtons |= XINPUT_GAMEPAD_B;
			}
		}

		if (bCrouchOnDmg && isEntityPlayer(cgArray_s->ClientNumber)) {
			if (cgArray_s->Health < dwStoreHealth) {
				bCrouchState = true;
				dwCODDelay = GetTickCount();
				pState->Gamepad.wButtons |= XINPUT_GAMEPAD_B;
			}

			dwStoreHealth = cgArray_s->Health;

			if (bCrouchState) {
				if (GetTickCount() - dwCODDelay > 600) {
					bCrouchState = false;
					pState->Gamepad.wButtons |= XINPUT_GAMEPAD_B;
				}
			}
		}

		if (bRagebot && (!bSilent && ClosestPlayer != -1) || bPlayerPriority[ClosestPlayer]) {
			pState->Gamepad.sThumbRX = 0;
			pState->Gamepad.sThumbRY = 0;
		}

		if (bJitterFire && GetAsyncKeyState(0x1338))
		{
			if (dwRapidMode > 4)
				dwRapidMode = 0;

			if (dwRapidMode == 0 || dwRapidMode == 3) // shoot
				pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_X;
			else if (dwRapidMode == 1) // reload
				pState->Gamepad.wButtons |= XINPUT_GAMEPAD_X;
			else if (dwRapidMode == 2 || dwRapidMode == 4) // Y
			{
				pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_X;
				pState->Gamepad.wButtons |= XINPUT_GAMEPAD_Y;
			}

			dwRapidMode++;
		}
	}

	return XInputGetStateEx(dwUserIndex, r4, pState);
}

void __declspec(naked) H_DrawPicStub(int x, int y, int width, int height, int xS1, int yS1, int xS2, int yS2, float *color, int material)
{
	__asm
	{
		li r3, 1
		nop
		li r4, 2
		nop
		nop
		li r6, 3
		nop
		blr
	}
}

Detour<HRESULT> *H_DrawTextDetour;
HRESULT H_DrawText(char* Text, int MaxCharacters, int Font, float X, float Y, float XScale, float YScale, float Angle, float* Color, int Style) {
	if (!strcmp(Text, "Xbox LIVE")) {
		X -= 150;
		Text = "Eclipse Framework";
		Color = fclFlashMain;
		Style = 3;
	}

	if (!strstr(Text, "\x01"))
		return H_DrawTextDetour->CallOriginal(Text, MaxCharacters, Font, X, Y, XScale, YScale, Angle, Color, Style);
	else
		return 0;
}

Detour<HRESULT> *CL_ConsolePrintDetour;
HRESULT CL_ConsolePrint(int localClientNum, int channel, const char *txt, int duration, int pixelWidth, int flags) {
	if (!strstr(txt, "\x01")) {
		return CL_ConsolePrintDetour->CallOriginal(localClientNum, channel, txt, duration, pixelWidth, flags);
	}
	else
		return 0;
}