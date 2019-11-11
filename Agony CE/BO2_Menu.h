void AddPlayerMenu(int i)
{
	addMenu(&MenuVars, "Player", 100.0f, 6);
	addOption(&MenuVars, "Prioritize", 0, 0, &bPlayerPriority[i]);
	addOption(&MenuVars, "Aim at body", 0, 0, &bPlayerBodyAim[i]);
	addOption(&MenuVars, "Friendly", 0, 0, &bPlayerFriendly[i]);
}

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

	addGroup(&MenuVars, "Hitbox", 1, 0, 7);
	addCombo(&MenuVars, "Hitbox", 1, 0, aimTags, aimTags_s, &aimTags_c);
	addOption(&MenuVars, "Autobone", 1, 0, &bMultiBox);
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
	//addOption(&MenuVars, "Mutlibox", 1, 0, &bMultiBox);
	addOption(&MenuVars, "Point Correction", 1, 0, &bPointCorrection);
	addBar(&MenuVars, "Point Scale", 1, 0, &fPCorrection, 1.0f, 2.0f, 0.2f);

	addGroup(&MenuVars, "Adjustments", 2, 0, 6);
	addOption(&MenuVars, "Pos. Adjustment", 2, 0, &bPrediction);
	addBar(&MenuVars, "Adjust Scale", 2, 0, &fPrediction, 0, 50, 10);
	addOption(&MenuVars, "Remove Recoil", 2, 0, &bNoRecoil, ToggleRecoil);
	addOption(&MenuVars, "Remove Sway", 2, 0, &bNoSway, ToggleSway);
	addOption(&MenuVars, "Remove Spread", 2, 0, &bNoSpread);

	addGroup(&MenuVars, "Anti-Aim", 0, 1, 6);
	addOption(&MenuVars, "Enable", 0, 1, &bAntiAim);
	addCombo(&MenuVars, "Yaw", 0, 1, xAntiAim, xAntiAim_s, &xAntiAim_c);
	addCombo(&MenuVars, "Pitch", 0, 1, yAntiAim, yAntiAim_s, &yAntiAim_c);
	//addCombo(&MenuVars, "Roll", 0, 1, zAntiAim, zAntiAim_s, &zAntiAim_c);
	addCombo(&MenuVars, "Wall Detection", 0, 1, wallDetect, wallDetect_s, &wallDetect_c);

	addGroup(&MenuVars, "HvH", 2, 1, 6);
	addOption(&MenuVars, "Fake Lag", 2, 1, &bFakeLag);
	addBar(&MenuVars, "Lag Amount", 2, 1, &fLag, 100, 500, 100);
	addOption(&MenuVars, "Air Stuck", 2, 1, &bAirStuck);

	addMenu(&MenuVars, "Visuals", 325.0f);
	addGroup(&MenuVars, "Options", 0, 0, 13);
	addCombo(&MenuVars, "Box Type", 0, 0, cESPType, cESPType_s, &cESPType_c);
	addOption(&MenuVars, "Draw Bones", 0, 0, &bDrawBones);
	addOption(&MenuVars, "Name/Distance", 0, 0, &bDrawName);
	addOption(&MenuVars, "Draw Weapon", 0, 0, &bDrawWeapon);
	addOption(&MenuVars, "Draw Snaplines", 0, 0, &bDrawLines);
	addOption(&MenuVars, "Entity Names", 0, 0, &bEntityName);
	addOption(&MenuVars, "Entity Snaplines", 0, 0, &bEntityLine);
	addOption(&MenuVars, "Radar", 0, 0, &bRadar);
	addBar(&MenuVars, "Radar Distance", 0, 0, &fRadarDist, 10, 80, 10);
	addOption(&MenuVars, "Compass", 0, 0, &bCompass);
	addBar(&MenuVars, "Compass Size", 0, 0, &fCompassSize, 50, 200, 50);

	addGroup(&MenuVars, "Filter", 1, 0, 9);
	addOption(&MenuVars, "Draw Axis", 1, 0, &bDrawAxis);
	addOption(&MenuVars, "Draw Allies", 1, 0, &bDrawAllies);
	addOption(&MenuVars, "Draw Entities", 1, 0, &bDrawEntity);
	addOption(&MenuVars, "Radar Axis", 1, 0, &bRadarAxis);
	addOption(&MenuVars, "Radar Allies", 1, 0, &bRadarAlly);
	addOption(&MenuVars, "Radar Entities", 1, 0, &bRadarEntity);
	addOption(&MenuVars, "Compass Axis", 1, 0, &bCompassAxis);
	addOption(&MenuVars, "Compass Allies", 1, 0, &bCompassAlly);
	addOption(&MenuVars, "Compass Entities", 1, 0, &bCompassEntity);

	addGroup(&MenuVars, "Other", 2, 0, 2);
	addOption(&MenuVars, "Draw Crosshair", 2, 0, &bXHair);
	addOption(&MenuVars, "Crosshair Spread", 2, 0, &bXHairSpread);

	addMenu(&MenuVars, "Misc.", 225.0f);
	addBar(&MenuVars, "FOV", 0, 0, &fFOV, 65, 125, 20, SetFOV);
	addOption(&MenuVars, "End Game", 0, 0, NULL, &EndGame);
	addOption(&MenuVars, "Target Details", 0, 0, &bShowHost);

	addGroup(&MenuVars, "Warnings", 2, 0, 2);
	addOption(&MenuVars, "Proximity Warning", 2, 0, &bProximity);
	addOption(&MenuVars, "Visible Warning", 2, 0, &bVisible);

	addMenu(&MenuVars, "Config.", 125.0f);
	addGroup(&MenuVars, "Custom Config", 0, 0, 3);
	addOption(&MenuVars, "Save Config", 0, 0, NULL, WriteINI);
	addOption(&MenuVars, "Load Config", 0, 0, NULL, ReadINI);

	addGroup(&MenuVars, "Rage Config", 1, 0, 3);
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
		addOption(&MenuVars, "Not Connected", 0, 0, NULL, playerSub, i);
	}

	for (int i = 0; i < 18; i++) {
		AddPlayerMenu(i);
	}
}