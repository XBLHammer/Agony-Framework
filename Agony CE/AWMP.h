namespace AW
{
#include "AW_MenuFunc.h"
#include "AW_Structs.h"
#include "AW_Functions.h"
#include "AW_Menu.h"
#include "AW_ESP.h"
#include "AW_Aimbot.h"
#include "AW_Hook.h"

	int dwNameTick;
	int dwStealTick;
	int dwClientName;

	void Agony_Monitor()
	{
		if (Dvar_GetBool("cl_ingame"))
		{
			if (bFlashName) {
				if (GetTickCount() - dwNameTick > 100) {
					dwNameTick = GetTickCount();
					dwColorIndex++;
					if (dwColorIndex > 5)
						dwColorIndex = 1;

					char szTempCT[16];
					_snprintf(szTempCT, 16, "%s%i", "^", dwColorIndex);
					szCT = szTempCT;

					SetGT();
				}
			}

			if (bStealName) {
				if (GetTickCount() - dwStealTick > (int)fStealSpeed) {
					dwStealTick = GetTickCount();

				lblGetName:
					if (dwClientName >= 17)
						dwClientName = 0;
					else
						dwClientName++;

					char *szName = cgArray_s->ClientInfo[dwClientName].Name;
					if (strcmp(szName, "")) {
						szGT = szName;

						SetGT();
					}
					else
						goto lblGetName;
				}
			}

			int CurrentMenu = MenuVars.currentMenu,
				CurrentOption = MenuVars.currentOption[CurrentMenu],
				MaxOption = MenuVars.optionCount[CurrentMenu],
				PreviousMenu = MenuVars.previousMenu[CurrentMenu];

			if (MenuVars.openState == 1)
			{
				if (!MenuVars.bComboBox[CurrentMenu][CurrentOption])
				{
					if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) && CurrentOption > 0) {
						MenuVars.currentOption[CurrentMenu]--;
						UI_PlaySound(0, "match_countdown_tick", 0);
					}
					else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) && CurrentOption == 0) {
						MenuVars.currentOption[CurrentMenu] = MaxOption - 1;
						UI_PlaySound(0, "match_countdown_tick", 0);
					}

					if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) && CurrentOption < MaxOption - 1) {
						MenuVars.currentOption[CurrentMenu]++;
						UI_PlaySound(0, "match_countdown_tick", 0);
					}
					else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) && CurrentOption == MaxOption - 1) {
						MenuVars.currentOption[CurrentMenu] = 0;
						UI_PlaySound(0, "match_countdown_tick", 0);
					}

					if (InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && CurrentMenu > 0 && CurrentMenu <= 6) {
						CurrentMenu--;
						openSub(CurrentMenu);
						UI_PlaySound(0, "match_countdown_tick", 0);
					}
					if (InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT && CurrentMenu >= 0 && CurrentMenu < 6) {
						CurrentMenu++;
						openSub(CurrentMenu);
						UI_PlaySound(0, "match_countdown_tick", 0);
					}
				}
				else
				{
					if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) && MenuVars.iComboScroll > 0) {
						MenuVars.iComboScroll--;
						UI_PlaySound(0, "match_countdown_tick", 0);
					}
					if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) && MenuVars.iComboScroll < MenuVars.iComboMax - 1) {
						MenuVars.iComboScroll++;
						UI_PlaySound(0, "match_countdown_tick", 0);
					}
				}

				if (GetAsyncKeyState(XINPUT_GAMEPAD_A))
				{
					UI_PlaySound(0, "mp_killstreak_radar", 0);
					updatePlayerList();

					if (MenuVars.Option_Toggle[CurrentMenu][CurrentOption] != NULL)
						*MenuVars.Option_Toggle[CurrentMenu][CurrentOption] = !*MenuVars.Option_Toggle[CurrentMenu][CurrentOption];

					if (MenuVars.Sub_Toggle[CurrentMenu] != NULL && CurrentOption == 0)
						*MenuVars.Sub_Toggle[CurrentMenu] = !*MenuVars.Sub_Toggle[CurrentMenu];

					if (MenuVars.fBarValue[CurrentMenu][CurrentOption] != NULL)
					{
						if (*MenuVars.fBarValue[CurrentMenu][CurrentOption] >= MenuVars.fBarMax[CurrentMenu][CurrentOption])
							*MenuVars.fBarValue[CurrentMenu][CurrentOption] = MenuVars.fBarMin[CurrentMenu][CurrentOption];
						else
							*MenuVars.fBarValue[CurrentMenu][CurrentOption] += MenuVars.fBarMod[CurrentMenu][CurrentOption];
					}

					if (MenuVars.Option_ToggleArr[CurrentMenu][CurrentOption] != NULL)
					{
						if (MenuVars.bComboBox[CurrentMenu][CurrentOption]) {
							*MenuVars.Option_ToggleArr_Cur[CurrentMenu][CurrentOption] = MenuVars.iComboScroll;

							MenuVars.iComboScroll = 0;
							MenuVars.iComboMax = 0;
							MenuVars.cComboData = NULL;

							MenuVars.bComboBox[CurrentMenu][CurrentOption] = false;
						}
						else
							SetComboOption();
					}

					if (MenuVars.Option_Function[CurrentMenu][CurrentOption] != NULL)
						MenuVars.Option_Function[CurrentMenu][CurrentOption](MenuVars.Option_Param1[CurrentMenu][CurrentOption]);

				}
				if (GetAsyncKeyState(XINPUT_GAMEPAD_B))
				{
					UI_PlaySound(0, "mp_card_slide", 0);
					updatePlayerList();

					if (!MenuVars.bComboBox[CurrentMenu][CurrentOption])
					{
						if (PreviousMenu == -1) {
							MenuVars.openState = 0;
							while (GetAsyncKeyState(XINPUT_GAMEPAD_B))
								Sleep(20);
						}
						else MenuVars.currentMenu = MenuVars.previousMenu[CurrentMenu];
					}
					else {
						MenuVars.bComboBox[CurrentMenu][CurrentOption] = false;
						MenuVars.iComboScroll = 0;
					}
				}
				while (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) || GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) || GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_LEFT) || GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_RIGHT) || GetAsyncKeyState(XINPUT_GAMEPAD_B) || GetAsyncKeyState(XINPUT_GAMEPAD_A)) {
					Sleep(20);
				}
			}
			else if (MenuVars.openState == 2) {
				if (GetAsyncKeyState(XINPUT_GAMEPAD_B))
					MenuVars.openState = 1;

				if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) && MenuVars.RGBScroll > 0)
					MenuVars.RGBScroll--;
				else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) && MenuVars.RGBScroll == 0)
					MenuVars.RGBScroll = 2;

				if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) && MenuVars.RGBScroll < 2)
					MenuVars.RGBScroll++;
				else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) && MenuVars.RGBScroll == 2)
					MenuVars.RGBScroll = 0;

				if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_LEFT) && MenuVars.RGBColor[MenuVars.RGBScroll] > 0.0f)
					MenuVars.RGBColor[MenuVars.RGBScroll] -= 0.025f;

				if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_RIGHT) && MenuVars.RGBColor[MenuVars.RGBScroll] < 1.0f)
					MenuVars.RGBColor[MenuVars.RGBScroll] += 0.025f;

				while (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) || GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) || GetAsyncKeyState(XINPUT_GAMEPAD_B) || GetAsyncKeyState(XINPUT_GAMEPAD_A)) {
					Sleep(20);
				}
			}
			else
			{
				if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) && GetAsyncKeyState(XINPUT_GAMEPAD_RIGHT_THUMB)) {
					UI_PlaySound(0, "mp_ingame_summary", 0);
					updatePlayerList();

					MenuVars.openState = 1;
					while (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) || GetAsyncKeyState(XINPUT_GAMEPAD_RIGHT_THUMB)) {
						Sleep(20);
					}
				}
			}
		}
		else
		{
			if (iLagTime > 0)
				iLagTime = 0;
		}
	}
}