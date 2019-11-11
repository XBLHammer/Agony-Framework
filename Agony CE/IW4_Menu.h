void AddPlayerMenu(int i)
{
	addMenu(&MenuVars, "Player", 118.0f, 6);
	addOption(&MenuVars, "Blacklist", 0, 0, &bPlayerPriority[i]);
	addOption(&MenuVars, "Aim at body", 0, 0, &bPlayerBodyAim[i]);
	addOption(&MenuVars, "Whitelist", 0, 0, &bPlayerFriendly[i]);
	addOption(&MenuVars, "Face Sheild To Player", 0, 0, &bSheildToPlayer[i]);
}
/*
void BuildMenu()
{
//printf("[Tampered CE] Building menu structure.\n");


DrawText("pDowns", 1053.67, 37.19, "fonts/HudBigFont", 0.35, colWHITE);
DrawText("Main", 1070.00, 78.89, "fonts/HudBigFont", 0.35, colWHITE);
DrawText("Aimbot", 1077.72, 106.19, "fonts/HudBigFont", 0.35, colWHITE);
DrawText("Visuals", 1076.72, 134.19, "fonts/HudBigFont", 0.35, colWHITE);
DrawText("Other", 1084.72, 189.19, "fonts/HudBigFont", 0.35, colWHITE);
DrawText("Misc", 1071.31, 214.19, "fonts/HudBigFont", 0.35, colWHITE);
DrawText("Players", 1071.31, 242.19, "fonts/HudBigFont", 0.35, colWHITE);


initMenu();

addMenu(&MenuVars, "Legitbot", 280.0f);
addSubToggle(&MenuVars, &bLegitbot);

addGroup(&MenuVars, "Aimbot", 0, 0, 7);
addCombo(&MenuVars, "Aim Event", 0, 0, aimKeys, aimKeys_s, &aimKeys_c);
addBar(&MenuVars, "Aim FOV", 0, 0, &fFOVSize, 100, 500, 50);
addBar(&MenuVars, "Aim Speed", 0, 0, &fAimSpeed, 5, 30, 5);
addBar(&MenuVars, "Aim Curve", 0, 0, &fAimCurve, 0, 5, 1);

addGroup(&MenuVars, "Hitbox", 1, 0, 7);
addCombo(&MenuVars, "Hitbox", 1, 0, aimTags, aimTags_s, &aimTags_c);
addOption(&MenuVars, "Mutlibox", 1, 0, &bMultiBox);
addOption(&MenuVars, "Point Correction", 1, 0, &bPointCorrection);
addBar(&MenuVars, "Point Scale", 1, 0, &fPCorrection, 1.0f, 2.0f, 0.2f);

addGroup(&MenuVars, "Triggerbot", 2, 0, 7);
addOption(&MenuVars, "Enable", 2, 0, &bTriggerbot);
addBar(&MenuVars, "Seed", 2, 0, &fTriggerSeed, 1, 3, 0.5);
addOption(&MenuVars, "Burst Fire", 2, 0, &bBurstFire);
addBar(&MenuVars, "Trigger Delay", 2, 0, &fTriggerDelay, 0, 300, 50);
addOption(&MenuVars, "Auto-Aim", 2, 0, &bAutoAim);

addMenu(&MenuVars, "Ragebot", 450.0f);
addSubToggle(&MenuVars, &bRagebot);

addGroup(&MenuVars, "Aimbot", 0, 0, 6);
addOption(&MenuVars, "pSilent", 0, 0, &bSilent);
addOption(&MenuVars, "Snap", 0, 0, &bSnapback);
addCombo(&MenuVars, "Aim Event", 0, 0, aimKeys, aimKeys_s, &aimKeys_c);
addOption(&MenuVars, "Auto-Shoot", 0, 0, &bAutoShoot);
addOption(&MenuVars, "Anti-Anti-Aim", 0, 0, &bAntiAntiAim);

addGroup(&MenuVars, "Hitbox", 1, 0, 6);
addCombo(&MenuVars, "Hitbox", 1, 0, aimTags, aimTags_s, &aimTags_c);
addOption(&MenuVars, "Auto-Bone", 1, 0, &bMultiBox);
addOption(&MenuVars, "Point Correction", 1.2, 0, &bPointCorrection);
addBar(&MenuVars, "Point Scale", 1, 0, &fPCorrection, -1.2f, -9.0f, -0.2f);

addGroup(&MenuVars, "Adjustments", 2, 0, 10);
addOption(&MenuVars, "Prediction", 2, 0, &bPrediction);
addBar(&MenuVars, "Adjust Scale", 2, 0, &fPrediction, 0, 50, 20);
addOption(&MenuVars, "Remove Recoil", 2, 0, &bNoRecoil, ToggleRecoil);
addOption(&MenuVars, "Remove Sway", 2, 0, &bNoSway, ToggleSway);
addOption(&MenuVars, "Remove Spread", 2, 0, &bNoSpread);
addOption(&MenuVars, "Laser", 2, 0, &blaser, ToggleLaser);
addOption(&MenuVars, "UAV", 2, 0, &bUAV, ToggleUAV);
addOption(&MenuVars, "Rapid Fire", 2, 0, &bRapidFire);
addOption(&MenuVars, "RCS", 2, 0, &bRCS);

addGroup(&MenuVars, "Anti-Aim", 0, 1, 8);
addOption(&MenuVars, "Enable", 0, 1, &bAntiAim);
addCombo(&MenuVars, "Yaw", 0, 1, xAntiAim, xAntiAim_s, &xAntiAim_c);
addCombo(&MenuVars, "Pitch", 0, 1, yAntiAim, yAntiAim_s, &yAntiAim_c);
addCombo(&MenuVars, "Roll", 0, 1, zAntiAim, zAntiAim_s, &zAntiAim_c);
addCombo(&MenuVars, "Wall Detection", 0, 1, wallDetect, wallDetect_s, &wallDetect_c);

addGroup(&MenuVars, "AA Config", 1, 1, 8);
addOption(&MenuVars, "Aircraft Riot", 1, 1, &bHarrierRiot);
addBar(&MenuVars, "Rnd Min", 1, 1, &fRndXMin, 0, 180, 20);
addBar(&MenuVars, "Rnd Max", 1, 1, &fRndXMax, 180, 360, 20);
addBar(&MenuVars, "Spin Speed", 1, 1, &fSpinSpeed, 4, 28, 4);
addBar(&MenuVars, "Roll Speed", 1, 1, &fRollSpeed, 5, 20, 5);

addGroup(&MenuVars, "HvH", 2, 1, 8);
addOption(&MenuVars, "Fake Lag", 2, 1, &bFakeLag);
addBar(&MenuVars, "Lag Amount", 2, 1, &fLag, 0, 10000, 500);
addOption(&MenuVars, "Air Stuck", 2, 1, &bAirStuck);
addOption(&MenuVars, "Crouch Bot", 2, 1, &bCrouchBot);
addBar(&MenuVars, "Crouch Interval", 2, 1, &fCrouchInteval, 200, 1600, 200);
addOption(&MenuVars, "Crouch on Dmg", 2, 1, &bCrouchOnDmg);

addMenu(&MenuVars, "Visuals", 325.0f);
addGroup(&MenuVars, "Options", 0, 0, 13);
addCombo(&MenuVars, "Box Type", 0, 0, cESPType, cESPType_s, &cESPType_c);
addOption(&MenuVars, "Draw Bones", 0, 0, &bDrawBones);
addOption(&MenuVars, "Name/Distance", 0, 0, &bDrawName);
addOption(&MenuVars, "Draw Weapon", 0, 0, &bDrawWeapon);
addOption(&MenuVars, "Draw Snaplines", 0, 0, &bDrawLines);
addOption(&MenuVars, "Entity Names", 0, 0, &bEntityName);
addOption(&MenuVars, "Entity Snaplines", 0, 0, &bEntityLine);
addOption(&MenuVars, "Health Bar", 0, 0, &bRadar);
//addBar(&MenuVars, "Radar Distance", 0, 0, &fRadarDist, 10, 80, 10);
addOption(&MenuVars, "Compass", 0, 0, &bCompass);
addBar(&MenuVars, "Compass Size", 0, 0, &fCompassSize, 50, 200, 50);

addGroup(&MenuVars, "Filter", 1, 0, 6);
addOption(&MenuVars, "Draw Axis", 1, 0, &bDrawAxis);
addOption(&MenuVars, "Draw Allies", 1, 0, &bDrawAllies);
addOption(&MenuVars, "Draw Entities", 1, 0, &bDrawEntity);
//addOption(&MenuVars, "Radar Axis", 1, 0, &bRadarAxis);
//addOption(&MenuVars, "Radar Allies", 1, 0, &bRadarAlly);
//addOption(&MenuVars, "Radar Entities", 1, 0, &bRadarEntity);
addOption(&MenuVars, "Compass Axis", 1, 0, &bCompassAxis);
addOption(&MenuVars, "Compass Allies", 1, 0, &bCompassAlly);
addOption(&MenuVars, "Compass Entities", 1, 0, &bCompassEntity);

addGroup(&MenuVars, "Other", 2, 0, 8);
addOption(&MenuVars, "Draw Crosshair", 2, 0, &bXHair);
addOption(&MenuVars, "Crosshair Spread", 2, 0, &bXHairSpread);

addOption(&MenuVars, "Chams", 2, 0, &bChams);
addOption(&MenuVars, "Weapon Color", 2, 0, &bwpColor);
addOption(&MenuVars, "Solid", 2, 0, &bSolid);
addOption(&MenuVars, "Wireframe", 2, 0, &bWireframe);
addOption(&MenuVars, "Visible Warning", 2, 0, &bVisible);

addMenu(&MenuVars, "Misc.", 185.0f);
addBar(&MenuVars, "FOV", 0, 0, &fFOV, 65, 120, 5, SetFOV);
addOption(&MenuVars, "End Game", 0, 0, NULL, EndGame);
addOption(&MenuVars, "Info", 0, 0, &bShowHost);
addOption(&MenuVars, "Remove Flash Fx", 0, 0, &bFlashFx);
addOption(&MenuVars, "Jitter Fire", 0, 0, &bJitterFire);
addOption(&MenuVars, "Freeze All", 0, 0, NULL, FreezeAll);

addOption(&MenuVars, "Set Name", 1, 0, NULL, &doSetName);
//addOption(&MenuVars, "Custom CMD", 1, 0, NULL, &doCustomCmd);
addOption(&MenuVars, "Name Spam", 1, 0, &bNameSpam);
addOption(&MenuVars, "Name Stealer", 1, 0, &bNameSteal);
addOption(&MenuVars, "Swap Teams", 1, 0, NULL, &swapTeam);
addOption(&MenuVars, "Swap Target", 1, 0, &bSwitchTarget);
addOption(&MenuVars, "Spawn Bot", 1, 0, NULL, AddBotClient);
addOption(&MenuVars, "Crosshair Fade", 1, 0, &xfade);
addOption(&MenuVars, "UI Mods", 1, 0, &bfademw2);
addOption(&MenuVars, "Chicken Chams", 2, 0, &bchickenchams);
addOption(&MenuVars, "Map Color", 2, 0, &bmapcolor);

//	addGroup(&MenuVars, "Warnings", 2, 0, 2);
//addOption(&MenuVars, "Proximity Warning", 2, 0, &bProximity);
//	addOption(&MenuVars, "Visible Warning", 2, 0, &bVisible);

addMenu(&MenuVars, "Config.", 145.0f);
addGroup(&MenuVars, "Custom Config", 0, 0, 4);
addOption(&MenuVars, "Load Config", 0, 0, NULL, SetHvHConfig);
//addOption(&MenuVars, "Save Config", 0, 0, NULL, WriteINI);
//addOption(&MenuVars, "Load Config", 0, 0, NULL, ReadINI);

//	addGroup(&MenuVars, "Rage Config", 1, 0, 3);
//addOption(&MenuVars, "Public Rage", 1, 0, NULL, SetRageConfig);
//	addOption(&MenuVars, "HvH", 1, 0, NULL, SetHvHConfig);
//	addOption(&MenuVars, "Riot", 1, 0, NULL, SetRiotConfig);

//	addGroup(&MenuVars, "Legit Config", 2, 0, 3);
//	addOption(&MenuVars, "Assault", 2, 0, NULL, SetAssaultConfig);
//	addOption(&MenuVars, "Run-n-Gun", 2, 0, NULL, SetRunNGunConfig);
//	addOption(&MenuVars, "Sniping", 2, 0, NULL, SetSniperConfig);

addMenu(&MenuVars, "Settings", 145.0f);
addGroup(&MenuVars, "Menu Position", 0, 0, 4);
addOption(&MenuVars, "Menu Up", 0, 0, NULL, menuUp);
addOption(&MenuVars, "Menu Down", 0, 0, NULL, menuDown);
addOption(&MenuVars, "Menu Left", 0, 0, NULL, menuLeft);
addOption(&MenuVars, "Menu Right", 0, 0, NULL, menuRight);

addGroup(&MenuVars, "Menu Color", 1, 0, 4);
addOption(&MenuVars, "Main Color", 1, 0, NULL, openRGB, 0);
addOption(&MenuVars, "Header Color", 1, 0, NULL, openRGB, 7);
addOption(&MenuVars, "Shader Color", 1, 0, NULL, openRGB, 1);
addOption(&MenuVars, "Text Color", 1, 0, NULL, openRGB, 2);

addGroup(&MenuVars, "ESP Color", 2, 0, 4);
addOption(&MenuVars, "Enemy Color", 2, 0, NULL, openRGB, 3);
addOption(&MenuVars, "Friendly Color", 2, 0, NULL, openRGB, 4);
addOption(&MenuVars, "Visible Color", 2, 0, NULL, openRGB, 5);
addOption(&MenuVars, "Target Color", 2, 0, NULL, openRGB, 6);

addMenu(&MenuVars, "Players", 405.0f);

for (int i = 0; i < 18; i++)
{
addOption(&MenuVars, "Searching...", 0, 0, NULL, playerSub, i);
}

for (int i = 0; i < 18; i++) {
AddPlayerMenu(i);
}
}*/

bool test = false;
void BuildMenu()
{
	initMenu();

	addMenu(&MenuVars, "Legitbot", 280.0f);
	addSubToggle(&MenuVars, &bLegitbot);

	addGroup(&MenuVars, "Aimbot", 0, 0, 9);
	addCombo(&MenuVars, "Aim Event", 0, 0, aimKeys, aimKeys_s, &aimKeys_c);
	addBar(&MenuVars, "Aim FOV", 0, 0, &fFOVSize, 100, 500, 50);
	addBar(&MenuVars, "Aim Speed", 0, 0, &fAimSpeed, 5, 30, 5);
	addBar(&MenuVars, "Aim Curve", 0, 0, &fAimCurve, 0, 5, 1);
	addOption(&MenuVars, "Rapid Fire", 0, 0, &bRapidFire);
	addOption(&MenuVars, "RCS", 0, 0, &bRCS, ToggleRCS);

	addGroup(&MenuVars, "Hitbox", 1, 0, 6);
	addCombo(&MenuVars, "Hitbox", 1, 0, aimTags, aimTags_s, &aimTags_c);
	//addOption(&MenuVars, "Nothing", 1, 0, &test);
	addOption(&MenuVars, "Point Correction", 1, 0, &bPointCorrection);
	addBar(&MenuVars, "Point Scale", 1, 0, &fPCorrection, 1.0f, 2.0f, 0.2f);

	addGroup(&MenuVars, "Triggerbot", 2, 0, 7);
	addOption(&MenuVars, "Enable", 2, 0, &bTriggerbot);
	addBar(&MenuVars, "Seed", 2, 0, &fTriggerSeed, 1, 3, 0.5);
	addOption(&MenuVars, "Burst Fire", 2, 0, &bBurstFire);
	addBar(&MenuVars, "Trigger Delay", 2, 0, &fTriggerDelay, 0, 300, 50);
	addOption(&MenuVars, "Auto-Aim", 2, 0, &bAutoAim);

	addMenu(&MenuVars, "Ragebot", 450.0f);
	addSubToggle(&MenuVars, &bRagebot);

	addGroup(&MenuVars, "Aimbot", 0, 0, 6);
	addOption(&MenuVars, "pSilent", 0, 0, &bSilent);
	addOption(&MenuVars, "Snap", 0, 0, &bSnap);
	addCombo(&MenuVars, "Aim Event", 0, 0, aimKeys, aimKeys_s, &aimKeys_c);
	addOption(&MenuVars, "Auto-Shoot", 0, 0, &bAutoShoot);
	addOption(&MenuVars, "Anti-Anti-Aim", 0, 0, &bAntiAntiAim);

	addGroup(&MenuVars, "Hitbox", 1, 0, 5);
	addCombo(&MenuVars, "Hitbox", 1, 0, aimTags, aimTags_s, &aimTags_c);
	addOption(&MenuVars, "Mutlibox", 1, 0, &bMultiBox);
	addOption(&MenuVars, "Point Correction", 1, 0, &bPointCorrection);
	addBar(&MenuVars, "Point Scale", 1, 0, &fPCorrection, 1.0f, 2.0f, 0.2f);

	addGroup(&MenuVars, "Adjustments", 2, 0, 6);
	addOption(&MenuVars, "Pos. Adjustment", 2, 0, &bPrediction);
	addBar(&MenuVars, "Adjust Scale", 2, 0, &fPrediction, 0, 50, 10);
	addOption(&MenuVars, "Remove Recoil", 2, 0, &bNoRecoil, ToggleRecoil);
	addOption(&MenuVars, "Remove Sway", 2, 0, &bNoSway, ToggleSway);
	addOption(&MenuVars, "Remove Spread", 2, 0, &bNoSpread);

	addGroup(&MenuVars, "Anti-Aim", 0, 1, 7);
	addOption(&MenuVars, "Enable", 0, 1, &bAntiAim);
	addCombo(&MenuVars, "X", 0, 1, xAntiAim, xAntiAim_s, &xAntiAim_c);
	addCombo(&MenuVars, "Y", 0, 1, yAntiAim, yAntiAim_s, &yAntiAim_c);
	addCombo(&MenuVars, "Z", 0, 1, zAntiAim, zAntiAim_s, &zAntiAim_c);
	addCombo(&MenuVars, "Wall Detection", 0, 1, wallDetect, wallDetect_s, &wallDetect_c);

	addGroup(&MenuVars, "AA Settings", 1, 1, 8);
	addOption(&MenuVars, "Aircraft Riot", 1, 1, &bHarrierRiot);
	addBar(&MenuVars, "Rnd Min", 1, 1, &fRndXMin, 0, 180, 20);
	addBar(&MenuVars, "Rnd Max", 1, 1, &fRndXMax, 180, 360, 20);
	addBar(&MenuVars, "Spin Speed", 1, 1, &fSpinSpeed, 5, 100, 5);
	addBar(&MenuVars, "Roll Speed", 1, 1, &fRollSpeed, 5, 100, 5);

	addGroup(&MenuVars, "HvH", 2, 1, 8);
	addOption(&MenuVars, "Fake Lag", 2, 1, &bFakeLag);
	addBar(&MenuVars, "Lag Amount", 2, 1, &fLag, 100, 500, 100);
	addOption(&MenuVars, "Air Stuck", 2, 1, &bAirStuck);
	addOption(&MenuVars, "Crouch Bot", 2, 1, &bCrouchBot);
	addBar(&MenuVars, "Crouch Interval", 2, 1, &fCrouchInteval, 200, 1600, 200);
	addOption(&MenuVars, "Crouch on Dmg", 2, 1, &bCrouchOnDmg);

	addMenu(&MenuVars, "Visuals", 325.0f);
	addGroup(&MenuVars, "Options", 0, 0, 11);
	addCombo(&MenuVars, "Box Type", 0, 0, cESPType, cESPType_s, &cESPType_c);
	addOption(&MenuVars, "Draw Bones", 0, 0, &bDrawBones);
	addOption(&MenuVars, "Name/Distance", 0, 0, &bDrawName);
	addOption(&MenuVars, "Draw Weapon", 0, 0, &bDrawWeapon);
	addOption(&MenuVars, "Draw Snaplines", 0, 0, &bDrawLines);
	addOption(&MenuVars, "Entity Names", 0, 0, &bEntityName);
	addOption(&MenuVars, "Entity Snaplines", 0, 0, &bEntityLine);
	addOption(&MenuVars, "Health Bar", 0, 0, &bRadar);
	addOption(&MenuVars, "Compass", 0, 0, &bCompass);
	addBar(&MenuVars, "Compass Size", 0, 0, &fCompassSize, 50, 200, 50);

	addGroup(&MenuVars, "Filter", 1, 0, 6);
	addOption(&MenuVars, "Draw Axis", 1, 0, &bDrawAxis);
	addOption(&MenuVars, "Draw Allies", 1, 0, &bDrawAllies);
	addOption(&MenuVars, "Draw Entities", 1, 0, &bDrawEntity);
	addOption(&MenuVars, "Compass Axis", 1, 0, &bCompassAxis);
	addOption(&MenuVars, "Compass Allies", 1, 0, &bCompassAlly);
	addOption(&MenuVars, "Compass Entities", 1, 0, &bCompassEntity);

	addGroup(&MenuVars, "Radar Settings", 1, 1, 3);
	addOption(&MenuVars, "Toggle Radar", 1, 1, &drawRadar);
	addOption(&MenuVars, "Draw Entities", 1, 1, &drawEntites);
	addOption(&MenuVars, "Draw Deaths", 1, 1, &drawDeaths);

	addGroup(&MenuVars, "Other", 2, 0, 6);
	addOption(&MenuVars, "Draw Crosshair", 2, 0, &bXHair);
	addOption(&MenuVars, "Crosshair Spread", 2, 0, &bXHairSpread);

	addOption(&MenuVars, "Chams", 2, 0, &bChams);
	addOption(&MenuVars, "Weapon Color", 2, 0, &bwpColor);
	addOption(&MenuVars, "Solid", 2, 0, &bSolid);
	addOption(&MenuVars, "Wireframe", 2, 0, &bWireframe);

	addMenu(&MenuVars, "Misc.", 235.0f);
	addBar(&MenuVars, "FOV", 0, 0, &fFOV, 65, 120, 5, SetFOV);
	addOption(&MenuVars, "End Game", 0, 0, NULL, EndGame);
	addOption(&MenuVars, "Info", 0, 0, &bShowHost);
	addOption(&MenuVars, "Remove Flash Fx", 0, 0, &bFlashFx);
	addOption(&MenuVars, "Jitter Fire", 0, 0, &bJitterFire);
	addOption(&MenuVars, "Freeze All", 0, 0, NULL, FreezeAll);

	addOption(&MenuVars, "Set Name", 1, 0, NULL, &doSetName);
	//addOption(&MenuVars, "Custom CMD", 1, 0, NULL, &doCustomCmd);
	addOption(&MenuVars, "Name Spam", 1, 0, &bNameSpam);
	addOption(&MenuVars, "Name Stealer", 1, 0, &bNameSteal);
	addOption(&MenuVars, "Swap Teams", 1, 0, NULL, &swapTeam);
	addOption(&MenuVars, "Swap Target", 1, 0, &bSwitchTarget);
	addOption(&MenuVars, "Spawn Bot", 1, 0, NULL, AddBotClient);
	addOption(&MenuVars, "Crosshair Fade", 1, 0, &xfade);
	addOption(&MenuVars, "Chicken Chams", 1, 0, &bchickenchams);
	addOption(&MenuVars, "Map Color", 1, 0, &bmapcolor);

	addGroup(&MenuVars, "Onscreen Stuff", 2, 0, 3);
	addOption(&MenuVars, "Visible Warning", 2, 0, &bVisible);
	addOption(&MenuVars, "Long Killfeed", 2, 0, &bKillfeed);
	addOption(&MenuVars, "UI Mods", 2, 0, &bfademw2);

	addMenu(&MenuVars, "Config.", 125.0f);
	addGroup(&MenuVars, "Custom Config", 0, 0, 2);
	addOption(&MenuVars, "Save Config", 0, 0, NULL, WriteINI);
	addOption(&MenuVars, "Load Config", 0, 0, NULL, ReadINI);

	addGroup(&MenuVars, "Rage Config", 1, 0, 2);
	addOption(&MenuVars, "Public Rage", 1, 0, NULL, SetRageConfig);
	addOption(&MenuVars, "HvH", 1, 0, NULL, SetHvHConfig);

	addGroup(&MenuVars, "Legit Config", 2, 0, 3);
	addOption(&MenuVars, "Assault", 2, 0, NULL, SetAssaultConfig);
	addOption(&MenuVars, "Run-n-Gun", 2, 0, NULL, SetRunNGunConfig);
	addOption(&MenuVars, "Sniping", 2, 0, NULL, SetSniperConfig);

	addMenu(&MenuVars, "Settings", 150.0f);
	addGroup(&MenuVars, "Menu Position", 0, 0, 4);
	addOption(&MenuVars, "Menu Up", 0, 0, NULL, menuUp);
	addOption(&MenuVars, "Menu Down", 0, 0, NULL, menuDown);
	addOption(&MenuVars, "Menu Left", 0, 0, NULL, menuLeft);
	addOption(&MenuVars, "Menu Right", 0, 0, NULL, menuRight);

	addGroup(&MenuVars, "Menu Color", 1, 0, 4);
	addOption(&MenuVars, "Main Color", 1, 0, NULL, openRGB, 0);
	addOption(&MenuVars, "Header Color", 1, 0, NULL, openRGB, 7);
	addOption(&MenuVars, "Shader Color", 1, 0, NULL, openRGB, 1);
	addOption(&MenuVars, "Text Color", 1, 0, NULL, openRGB, 2);

	addGroup(&MenuVars, "ESP Color", 2, 0, 4);
	addOption(&MenuVars, "Enemy Color", 2, 0, NULL, openRGB, 3);
	addOption(&MenuVars, "Friendly Color", 2, 0, NULL, openRGB, 4);
	addOption(&MenuVars, "Visible Color", 2, 0, NULL, openRGB, 5);
	addOption(&MenuVars, "Target Color", 2, 0, NULL, openRGB, 6);

	addMenu(&MenuVars, "Players", 415.0f);

	for (int i = 0; i < 18; i++) {
		addOption(&MenuVars, "Searching...", 0, 0, NULL, playerSub, i);
	}

	for (int i = 0; i < 18; i++) {
		AddPlayerMenu(i);
	}
}