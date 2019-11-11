const char *szIniPath = "HDD:\\EclipseSettings.ini";

void WriteINI(int)
{
	if (XIniRW.WOpenINI(szIniPath)) {
		XNotify(L"[User] Config Saved!");
		XIniRW.WriteInt("aimbot", "aimevent", aimKeys_c);
		XIniRW.WriteInt("aimbot", "hitbox", aimTags_c);
		XIniRW.WriteBool("aimbot", "multibox", bMultiBox);
		XIniRW.WriteBool("aimbot", "pcorrection", bPointCorrection);
		XIniRW.WriteFloat("aimbot", "pscale", fPCorrection);
		XIniRW.WriteBool("lbot", "active", bLegitbot);
		XIniRW.WriteFloat("lbot", "aimfov", fFOVSize);
		XIniRW.WriteFloat("lbot", "aimspeed", fAimSpeed);
		XIniRW.WriteFloat("lbot", "aimcurve", fAimCurve);
		XIniRW.WriteBool("lbot", "rapidfire", bRapidFire);
		XIniRW.WriteBool("lbot", "rcs", bRCS);
		XIniRW.WriteBool("tbot", "active", bTriggerbot);
		XIniRW.WriteFloat("tbot", "seed", fTriggerSeed);
		XIniRW.WriteBool("tbot", "burst", bBurstFire);
		XIniRW.WriteFloat("tbot", "delay", fTriggerDelay);
		XIniRW.WriteBool("tbot", "aim", bAutoAim);
		XIniRW.WriteBool("rbot", "active", bRagebot);
		XIniRW.WriteBool("rbot", "psilent", bSilent);
		XIniRW.WriteBool("rbot", "snap", bSnapback);
		XIniRW.WriteBool("rbot", "autoshoot", bAutoShoot);
		XIniRW.WriteBool("rbot", "antiaa", bAntiAntiAim);
		XIniRW.WriteBool("rbot", "posadjustment", bPrediction);
		XIniRW.WriteFloat("rbot", "adjustscale", fPrediction);
		XIniRW.WriteBool("rbot", "norecoil", bNoRecoil);
		XIniRW.WriteBool("rbot", "nosway", bNoSway);
		XIniRW.WriteBool("rbot", "nospread", bNoSpread);
		XIniRW.WriteBool("aa", "active", bAntiAim);
		XIniRW.WriteInt("aa", "yaw", xAntiAim_c);
		XIniRW.WriteInt("aa", "pitch", yAntiAim_c);
		XIniRW.WriteInt("aa", "roll", zAntiAim_c);
		XIniRW.WriteInt("aa", "edge", wallDetect_c);
		XIniRW.WriteBool("aa", "aircraft", bHarrierRiot);
		XIniRW.WriteFloat("aa", "rndmin", fRndXMin);
		XIniRW.WriteFloat("aa", "rndmax", fRndXMax);
		XIniRW.WriteFloat("aa", "spinspeed", fSpinSpeed);
		XIniRW.WriteFloat("aa", "rollspeed", fRollSpeed);
		XIniRW.WriteBool("hvh", "fakelag", bFakeLag);
		XIniRW.WriteFloat("hvh", "lagamount", fLag);
		XIniRW.WriteBool("hvh", "airstuck", bAirStuck);
		XIniRW.WriteBool("hvh", "crouchbot", bCrouchBot);
		XIniRW.WriteFloat("hvh", "crouchtime", fCrouchInteval);
		XIniRW.WriteBool("hvh", "crouchdmg", bCrouchOnDmg);
		XIniRW.WriteInt("visuals", "boxtype", cESPType_c);
		XIniRW.WriteBool("visuals", "bones", bDrawBones);
		XIniRW.WriteBool("visuals", "name", bDrawName);
		XIniRW.WriteBool("visuals", "weapon", bDrawWeapon);
		XIniRW.WriteBool("visuals", "lines", bDrawLines);
		XIniRW.WriteBool("visuals", "entname", bEntityName);
		XIniRW.WriteBool("visuals", "entline", bEntityLine);
		XIniRW.WriteBool("visuals", "radar", bRadar);
		XIniRW.WriteFloat("visuals", "radardist", fRadarDist);
		XIniRW.WriteBool("visuals", "compass", bCompass);
		XIniRW.WriteFloat("visuals", "compasssize", fCompassSize);
		XIniRW.WriteBool("visfilter", "axis", bDrawAxis);
		XIniRW.WriteBool("visfilter", "allies", bDrawAllies);
		XIniRW.WriteBool("visfilter", "entities", bDrawEntity);
		XIniRW.WriteBool("visfilter", "radaraxis", bRadarAxis);
		XIniRW.WriteBool("visfilter", "radarallies", bRadarAlly);
		XIniRW.WriteBool("visfilter", "radarentities", bRadarEntity);
		XIniRW.WriteBool("visfilter", "compassaxis", bCompassAxis);
		XIniRW.WriteBool("visfilter", "compassallies", bCompassAlly);
		XIniRW.WriteBool("visfilter", "compassentities", bCompassEntity);
		XIniRW.WriteBool("visother", "xhair", bXHair);
		XIniRW.WriteBool("visother", "xhairspread", bXHairSpread);
		XIniRW.WriteBool("visother", "chams", bChams);
		XIniRW.WriteBool("visother", "wireframe", bWireframe);
		XIniRW.WriteBool("visother", "solid", bSolid);
		XIniRW.WriteBool("radarsettings", "extRadar", drawRadar);
		XIniRW.WriteBool("radarsettings", "drawEnt", drawEntites);
		XIniRW.WriteFloat("misc", "fov", fFOV);
		XIniRW.WriteBool("misc", "showhost", bShowHost);
		XIniRW.WriteBool("misc", "flashfx", bFlashFx);
		XIniRW.WriteBool("misc", "proxwarning", bProximity);
		XIniRW.WriteBool("misc", "viswarning", bVisible);
		XIniRW.WriteFloat("menu", "mainr", Fade[0]);
		XIniRW.WriteFloat("menu", "maing", Fade[1]);
		XIniRW.WriteFloat("menu", "mainb", Fade[2]);
		XIniRW.WriteFloat("menu", "headr", colGRAY[0]);
		XIniRW.WriteFloat("menu", "headg", colGRAY[1]);
		XIniRW.WriteFloat("menu", "headb", colGRAY[2]);
		XIniRW.WriteFloat("menu", "shaderr", defaultShader[0]);
		XIniRW.WriteFloat("menu", "shaderg", defaultShader[1]);
		XIniRW.WriteFloat("menu", "shaderb", defaultShader[2]);
		XIniRW.WriteFloat("menu", "textr", defaultText[0]);
		XIniRW.WriteFloat("menu", "textg", defaultText[1]);
		XIniRW.WriteFloat("menu", "textb", defaultText[2]);
		XIniRW.WriteFloat("menu", "enemyr", defaultEnemy[0]);
		XIniRW.WriteFloat("menu", "enemyg", defaultEnemy[1]);
		XIniRW.WriteFloat("menu", "enemyb", defaultEnemy[2]);
		XIniRW.WriteFloat("menu", "friendr", defaultFriend[0]);
		XIniRW.WriteFloat("menu", "friendg", defaultFriend[1]);
		XIniRW.WriteFloat("menu", "friendb", defaultFriend[2]);
		XIniRW.WriteFloat("menu", "visibler", defaultVisible[0]);
		XIniRW.WriteFloat("menu", "visibleg", defaultVisible[1]);
		XIniRW.WriteFloat("menu", "visibleb", defaultVisible[2]);
		XIniRW.WriteFloat("menu", "targetr", defaultTarget[0]);
		XIniRW.WriteFloat("menu", "targetg", defaultTarget[1]);
		XIniRW.WriteFloat("menu", "targetb", defaultTarget[2]);

		if (!XIniRW.WCloseINI())
			XNotify(L"Failed to write to EclipseSettings.ini!");
	}
}

void UpdateINI(int) {
	switch (XamGetCurrentTitleId())
	{
	case 0x41560817:
		IW4MP::ToggleRCS(0); IW4MP::ToggleRecoil(0); IW4MP::ToggleSway(0); IW4MP::SetFOV(0);
		break;
	case 0x415608CB:
		//IW5MP::ToggleRCS(0);
		IW5MP::ToggleRecoil(0); IW5MP::ToggleSway(0); IW5MP::SetFOV(0);
		break;
	case 0x415608FC:
		GHO::ToggleRCS(0); GHO::ToggleRecoil(0); GHO::ToggleSway(0); GHO::SetFOV(0);
		break;
	case 0x41560914:
		AW::ToggleRCS(0); AW::ToggleRecoil(0); AW::ToggleSway(0); AW::SetFOV(0);
		break;
	case 0x41560855:
		BO1::ToggleRCS(0); BO1::ToggleRecoil(0); BO1::ToggleSway(0); BO1::SetFOV(0);
		break;
	case 0x415608C3:
		BO2::ToggleRCS(0); BO2::ToggleRecoil(0); BO2::ToggleSway(0); BO2::SetFOV(0);
		break;
	case 0x4156081C:
		WAW::ToggleRCS(0); WAW::ToggleRecoil(0); WAW::ToggleSway(0); WAW::SetFOV(0);
		break;
	case 0x415607E6:
		IW3MP::ToggleRCS(0); IW3MP::ToggleRecoil(0); IW3MP::ToggleSway(0); IW3MP::SetFOV(0);
		break;
	}
}

void ReadINI(int) {
	if (XIniRW.ROpenINI(szIniPath)) {
		XNotify(L"[User] Config Loaded!");
		aimKeys_c = XIniRW.ReadInt("aimbot", "aimevent");
		aimTags_c = XIniRW.ReadInt("aimbot", "hitbox");
		bMultiBox = XIniRW.ReadBool("aimbot", "multibox");
		bPointCorrection = XIniRW.ReadBool("aimbot", "pcorrection");
		fPCorrection = XIniRW.ReadFloat("aimbot", "pscale");
		bLegitbot = XIniRW.ReadBool("lbot", "active");
		fFOVSize = XIniRW.ReadFloat("lbot", "aimfov");
		fAimSpeed = XIniRW.ReadFloat("lbot", "aimspeed");
		fAimCurve = XIniRW.ReadFloat("lbot", "aimcurve");
		bRapidFire = XIniRW.ReadBool("lbot", "rapidfire");
		bRCS = XIniRW.ReadBool("lbot", "rcs");
		bTriggerbot = XIniRW.ReadBool("tbot", "active");
		fTriggerSeed = XIniRW.ReadFloat("tbot", "seed");
		bBurstFire = XIniRW.ReadBool("tbot", "burst");
		fTriggerDelay = XIniRW.ReadFloat("tbot", "delay");
		bAutoAim = XIniRW.ReadBool("tbot", "aim");
		bRagebot = XIniRW.ReadBool("rbot", "active");
		bSilent = XIniRW.ReadBool("rbot", "psilent");
		bSnapback = XIniRW.ReadBool("rbot", "snap");
		bAutoShoot = XIniRW.ReadBool("rbot", "autoshoot");
		bAntiAntiAim = XIniRW.ReadBool("rbot", "antiaa");
		bPrediction = XIniRW.ReadBool("rbot", "posadjustment");
		fPrediction = XIniRW.ReadFloat("rbot", "adjustscale");
		bNoRecoil = XIniRW.ReadBool("rbot", "norecoil");
		if (bNoRecoil)
		{
			IW4MP::ToggleRecoil(0);
		}
		bNoSway = XIniRW.ReadBool("rbot", "nosway");
		if (bNoSway)
		{
			IW4MP::ToggleSway(0);
		}
		bNoSpread = XIniRW.ReadBool("rbot", "nospread");
		bAntiAim = XIniRW.ReadBool("aa", "active");
		xAntiAim_c = XIniRW.ReadInt("aa", "yaw");
		yAntiAim_c = XIniRW.ReadInt("aa", "pitch");
		zAntiAim_c = XIniRW.ReadInt("aa", "roll");
		wallDetect_c = XIniRW.ReadInt("aa", "edge");
		bHarrierRiot = XIniRW.ReadBool("aa", "aircraft");
		fRndXMin = XIniRW.ReadFloat("aa", "rndmin");
		fRndXMax = XIniRW.ReadFloat("aa", "rndmax");
		fSpinSpeed = XIniRW.ReadFloat("aa", "spinspeed");
		bFakeLag = XIniRW.ReadBool("hvh", "fakelag");
		fLag = XIniRW.ReadFloat("hvh", "lagamount");
		bAirStuck = XIniRW.ReadBool("hvh", "airstuck");
		bCrouchBot = XIniRW.ReadBool("hvh", "crouchbot");
		fCrouchInteval = XIniRW.ReadFloat("hvh", "crouchtime");
		bCrouchOnDmg = XIniRW.ReadBool("hvh", "crouchdmg");
		cESPType_c = XIniRW.ReadInt("visuals", "boxtype");
		bDrawBones = XIniRW.ReadBool("visuals", "bones");
		bDrawName = XIniRW.ReadBool("visuals", "name");
		bDrawWeapon = XIniRW.ReadBool("visuals", "weapon");
		bDrawLines = XIniRW.ReadBool("visuals", "lines");
		bEntityName = XIniRW.ReadBool("visuals", "entname");
		bEntityLine = XIniRW.ReadBool("visuals", "entline");
		bRadar = XIniRW.ReadBool("visuals", "radar");
		fRadarDist = XIniRW.ReadFloat("visuals", "radardist");
		bCompass = XIniRW.ReadBool("visuals", "compass");
		fCompassSize = XIniRW.ReadFloat("visuals", "compasssize");
		bDrawAxis = XIniRW.ReadBool("visfilter", "axis");
		bDrawAllies = XIniRW.ReadBool("visfilter", "allies");
		bDrawEntity = XIniRW.ReadBool("visfilter", "entities");
		bRadarAxis = XIniRW.ReadBool("visfilter", "radaraxis");
		bRadarAlly = XIniRW.ReadBool("visfilter", "radarallies");
		bRadarEntity = XIniRW.ReadBool("visfilter", "radarentities");
		bCompassAxis = XIniRW.ReadBool("visfilter", "compassaxis");
		bCompassAlly = XIniRW.ReadBool("visfilter", "compassallies");
		bCompassEntity = XIniRW.ReadBool("visfilter", "compassentities");
		bXHair = XIniRW.ReadBool("visother", "xhair");
		bXHairSpread = XIniRW.ReadBool("visother", "xhairspread");
		bChams = XIniRW.ReadBool("visother", "chams");
		bWireframe = XIniRW.ReadBool("visother", "wireframe");
		bSolid = XIniRW.ReadBool("visother", "solid");
		drawRadar = XIniRW.ReadBool("radarsettings", "extRadar");
		drawEntites = XIniRW.ReadBool("radarsettings", "drawEnt");
		fFOV = XIniRW.ReadFloat("misc", "fov");
		bShowHost = XIniRW.ReadBool("misc", "showhost");
		bFlashFx = XIniRW.ReadBool("misc", "flashfx");
		bProximity = XIniRW.ReadBool("misc", "proxwarning");
		bVisible = XIniRW.ReadBool("misc", "viswarning");
		Fade[0] = XIniRW.ReadFloat("menu", "mainr");
		Fade[1] = XIniRW.ReadFloat("menu", "maing");
		Fade[2] = XIniRW.ReadFloat("menu", "mainb");
		colGRAY[0] = XIniRW.ReadFloat("menu", "headr");
		colGRAY[1] = XIniRW.ReadFloat("menu", "headg");
		colGRAY[2] = XIniRW.ReadFloat("menu", "headb");
		defaultShader[0] = XIniRW.ReadFloat("menu", "shaderr");
		defaultShader[1] = XIniRW.ReadFloat("menu", "shaderg");
		defaultShader[2] = XIniRW.ReadFloat("menu", "shaderb");
		defaultText[0] = XIniRW.ReadFloat("menu", "textr");
		defaultText[1] = XIniRW.ReadFloat("menu", "textg");
		defaultText[2] = XIniRW.ReadFloat("menu", "textb");
		defaultEnemy[0] = XIniRW.ReadFloat("menu", "enemyr");
		defaultEnemy[1] = XIniRW.ReadFloat("menu", "enemyg");
		defaultEnemy[2] = XIniRW.ReadFloat("menu", "enemyb");
		defaultFriend[0] = XIniRW.ReadFloat("menu", "friendr");
		defaultFriend[1] = XIniRW.ReadFloat("menu", "friendg");
		defaultFriend[2] = XIniRW.ReadFloat("menu", "friendb");
		defaultVisible[0] = XIniRW.ReadFloat("menu", "visibler");
		defaultVisible[1] = XIniRW.ReadFloat("menu", "visibleg");
		defaultVisible[2] = XIniRW.ReadFloat("menu", "visibleb");
		defaultTarget[0] = XIniRW.ReadFloat("menu", "targetr");
		defaultTarget[1] = XIniRW.ReadFloat("menu", "targetg");
		defaultTarget[2] = XIniRW.ReadFloat("menu", "targetb");

		if (!XIniRW.RCloseINI())
			XNotify(L"[User] Config Failed To Load!");
	}
	//UpdateINI(0);
}

void PresetINI(const char *iniPath) {
	//!strcmp(iniPath, "HDD:\\TamperedCE\\hvh.ini") && 
	if (XIniRW.ROpenINI(iniPath)) {
		aimKeys_c = XIniRW.ReadInt("aimbot", "aimevent");
		aimTags_c = XIniRW.ReadInt("aimbot", "hitbox");
		bMultiBox = XIniRW.ReadBool("aimbot", "multibox");
		bPointCorrection = XIniRW.ReadBool("aimbot", "pcorrection");
		fPCorrection = XIniRW.ReadFloat("aimbot", "pscale");
		bLegitbot = XIniRW.ReadBool("lbot", "active");
		fFOVSize = XIniRW.ReadFloat("lbot", "aimfov");
		fAimSpeed = XIniRW.ReadFloat("lbot", "aimspeed");
		fAimCurve = XIniRW.ReadFloat("lbot", "aimcurve");
		bRapidFire = XIniRW.ReadBool("lbot", "rapidfire");
		bRCS = XIniRW.ReadBool("lbot", "rcs");
		bTriggerbot = XIniRW.ReadBool("tbot", "active");
		fTriggerSeed = XIniRW.ReadFloat("tbot", "seed");
		bBurstFire = XIniRW.ReadBool("tbot", "burst");
		fTriggerDelay = XIniRW.ReadFloat("tbot", "delay");
		bAutoAim = XIniRW.ReadBool("tbot", "aim");
		bRagebot = XIniRW.ReadBool("rbot", "active");
		bSilent = XIniRW.ReadBool("rbot", "psilent");
		bSnapback = XIniRW.ReadBool("rbot", "snap");
		bAutoShoot = XIniRW.ReadBool("rbot", "autoshoot");
		bAntiAntiAim = XIniRW.ReadBool("rbot", "antiaa");
		bPrediction = XIniRW.ReadBool("rbot", "posadjustment");
		fPrediction = XIniRW.ReadFloat("rbot", "adjustscale");
		bNoRecoil = XIniRW.ReadBool("rbot", "norecoil");
		bNoSway = XIniRW.ReadBool("rbot", "nosway");
		bNoSpread = XIniRW.ReadBool("rbot", "nospread");
		bAntiAim = XIniRW.ReadBool("aa", "active");
		xAntiAim_c = XIniRW.ReadInt("aa", "yaw");
		yAntiAim_c = XIniRW.ReadInt("aa", "pitch");
		zAntiAim_c = XIniRW.ReadInt("aa", "roll");
		wallDetect_c = XIniRW.ReadInt("aa", "edge");
		bHarrierRiot = XIniRW.ReadBool("aa", "aircraft");
		fRndXMin = XIniRW.ReadFloat("aa", "rndmin");
		fRndXMax = XIniRW.ReadFloat("aa", "rndmax");
		fSpinSpeed = XIniRW.ReadFloat("aa", "spinspeed");
		fRollSpeed = XIniRW.ReadFloat("aa", "rollspeed");
		bFakeLag = XIniRW.ReadBool("hvh", "fakelag");
		fLag = XIniRW.ReadFloat("hvh", "lagamount");
		bAirStuck = XIniRW.ReadBool("hvh", "airstuck");
		bCrouchBot = XIniRW.ReadBool("hvh", "crouchbot");
		fCrouchInteval = XIniRW.ReadFloat("hvh", "crouchtime");
		bCrouchOnDmg = XIniRW.ReadBool("hvh", "crouchdmg");
		cESPType_c = XIniRW.ReadInt("visuals", "boxtype");
		bDrawBones = XIniRW.ReadBool("visuals", "bones");
		bDrawName = XIniRW.ReadBool("visuals", "name");
		bDrawWeapon = XIniRW.ReadBool("visuals", "weapon");
		bDrawLines = XIniRW.ReadBool("visuals", "lines");
		bEntityName = XIniRW.ReadBool("visuals", "entname");
		bEntityLine = XIniRW.ReadBool("visuals", "entline");
		bRadar = XIniRW.ReadBool("visuals", "radar");
		fRadarDist = XIniRW.ReadFloat("visuals", "radardist");
		bCompass = XIniRW.ReadBool("visuals", "compass");
		fCompassSize = XIniRW.ReadFloat("visuals", "compasssize");
		bDrawAxis = XIniRW.ReadBool("visfilter", "axis");
		bDrawAllies = XIniRW.ReadBool("visfilter", "allies");
		bDrawEntity = XIniRW.ReadBool("visfilter", "entities");
		bRadarAxis = XIniRW.ReadBool("visfilter", "radaraxis");
		bRadarAlly = XIniRW.ReadBool("visfilter", "radarallies");
		bRadarEntity = XIniRW.ReadBool("visfilter", "radarentities");
		bCompassAxis = XIniRW.ReadBool("visfilter", "compassaxis");
		bCompassAlly = XIniRW.ReadBool("visfilter", "compassallies");
		bCompassEntity = XIniRW.ReadBool("visfilter", "compassentities");
		bXHair = XIniRW.ReadBool("visother", "xhair");
		bXHairSpread = XIniRW.ReadBool("visother", "xhairspread");
		bChams = XIniRW.ReadBool("visother", "chams");
		bWireframe = XIniRW.ReadBool("visother", "wireframe");
		bSolid = XIniRW.ReadBool("visother", "solid");
		fFOV = XIniRW.ReadFloat("misc", "fov");
		bShowHost = XIniRW.ReadBool("misc", "showhost");
		bFlashFx = XIniRW.ReadBool("misc", "flashfx");
		bProximity = XIniRW.ReadBool("misc", "proxwarning");
		bVisible = XIniRW.ReadBool("misc", "viswarning");
		Fade[0] = XIniRW.ReadFloat("menu", "mainr");
		Fade[1] = XIniRW.ReadFloat("menu", "maing");
		Fade[2] = XIniRW.ReadFloat("menu", "mainb");
		colGRAY[0] = XIniRW.ReadFloat("menu", "headr");
		colGRAY[1] = XIniRW.ReadFloat("menu", "headg");
		colGRAY[2] = XIniRW.ReadFloat("menu", "headb");
		defaultShader[0] = XIniRW.ReadFloat("menu", "shaderr");
		defaultShader[1] = XIniRW.ReadFloat("menu", "shaderg");
		defaultShader[2] = XIniRW.ReadFloat("menu", "shaderb");
		defaultText[0] = XIniRW.ReadFloat("menu", "textr");
		defaultText[1] = XIniRW.ReadFloat("menu", "textg");
		defaultText[2] = XIniRW.ReadFloat("menu", "textb");
		defaultEnemy[0] = XIniRW.ReadFloat("menu", "enemyr");
		defaultEnemy[1] = XIniRW.ReadFloat("menu", "enemyg");
		defaultEnemy[2] = XIniRW.ReadFloat("menu", "enemyb");
		defaultFriend[0] = XIniRW.ReadFloat("menu", "friendr");
		defaultFriend[1] = XIniRW.ReadFloat("menu", "friendg");
		defaultFriend[2] = XIniRW.ReadFloat("menu", "friendb");
		defaultVisible[0] = XIniRW.ReadFloat("menu", "visibler");
		defaultVisible[1] = XIniRW.ReadFloat("menu", "visibleg");
		defaultVisible[2] = XIniRW.ReadFloat("menu", "visibleb");
		defaultTarget[0] = XIniRW.ReadFloat("menu", "targetr");
		defaultTarget[1] = XIniRW.ReadFloat("menu", "targetg");
		defaultTarget[2] = XIniRW.ReadFloat("menu", "targetb");

		if (!XIniRW.RCloseINI())
			printf("Ini could not be closed.\n");
	}

	//UpdateINI(0);
}

void SetRageConfig(int) {
	PresetINI("HDD:\\TamperedCE\\rage.ini");
}

void SetHvHConfig(int) {
	PresetINI("HDD:\\TamperedCE\\hvh.ini");
}

void SetAssaultConfig(int) {
	PresetINI("HDD:\\TamperedCE\\assault.ini");
}

void SetRunNGunConfig(int) {
	PresetINI("HDD:\\TamperedCE\\runngun.ini");
}

void SetSniperConfig(int) {
	PresetINI("HDD:\\TamperedCE\\sniper.ini");
}

void SetRiotConfig(int) {
	PresetINI("HDD:\\TamperedCE\\riot.ini");
}