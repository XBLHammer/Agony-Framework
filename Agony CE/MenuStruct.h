struct Vars
{
	/* Navigation Logic */
	static const int Max_Sub = 30, Max_Opt = 35;
	int currentMenu;
	int previousMenu[Max_Sub], currentOption[Max_Sub], optionCount[Max_Sub], displayCount[Max_Sub];
	int openState;

	/* Display Logic */
	const char* Menu_Title[Max_Sub];
	const char* Option_Text[Max_Sub][Max_Opt];
	int Offset_Column[Max_Sub][Max_Opt];
	int Offset_Row[Max_Sub][Max_Opt];
	float MenuH[Max_Sub];
	float *RGBColor;
	int RGBScroll;

	/* Group Boxes */
	int GroupIndex[Max_Sub];
	int GroupHeight[Max_Sub][Max_Opt];
	int gOffset_Column[Max_Sub][Max_Opt];
	int gOffset_Row[Max_Sub][Max_Opt];
	const char *GroupName[Max_Sub][Max_Opt];

	/* Functions (voids) */
	void(*Option_Function[Max_Sub][Max_Opt])(int);
	int Option_Param1[Max_Sub][Max_Opt];

	/* Booleans */
	bool* Option_Toggle[Max_Sub][Max_Opt];
	bool* Sub_Toggle[Max_Sub];

	/* Combo Boxes (string arrays) */
	char **Option_ToggleArr[Max_Sub][Max_Opt];
	int Option_ToggleArr_Size[Max_Sub][Max_Opt];
	int *Option_ToggleArr_Cur[Max_Sub][Max_Opt];
	bool bComboBox[Max_Sub][Max_Opt];
	int iComboScroll;
	int iComboMax;
	char **cComboData;

	/* Status Bars (floats) */
	float *fBarValue[Max_Sub][Max_Opt];
	float fBarMin[Max_Sub][Max_Opt];
	float fBarMax[Max_Sub][Max_Opt];
	float fBarMod[Max_Sub][Max_Opt];

}; Vars MenuVars;

int MenuIndex = -1;

void initMenu() {
	MenuIndex = -1;

	MenuVars.currentMenu = NULL;
	MenuVars.openState = NULL;
	MenuVars.iComboScroll = NULL;
	MenuVars.iComboMax = NULL;
	MenuVars.cComboData = NULL;

	for (int i = 0; i < MenuVars.Max_Sub; i++)
	{
		MenuVars.previousMenu[i] = NULL;
		MenuVars.currentOption[i] = NULL;
		MenuVars.optionCount[i] = NULL;
		MenuVars.displayCount[i] = NULL;

		MenuVars.Menu_Title[i] = NULL;

		MenuVars.GroupIndex[i] = NULL;

		MenuVars.Sub_Toggle[i] = NULL;

		for (int c = 0; c < MenuVars.Max_Opt; c++) {
			MenuVars.Option_Text[i][c] = NULL;
			MenuVars.Offset_Column[i][c] = NULL;
			MenuVars.Offset_Row[i][c] = NULL;

			MenuVars.Option_Function[i][c] = NULL;
			MenuVars.Option_Param1[i][c] = NULL;
			MenuVars.Option_Toggle[i][c] = NULL;

			MenuVars.GroupHeight[i][c] = NULL;
			MenuVars.GroupName[i][c] = NULL;
			MenuVars.gOffset_Column[i][c] = NULL;
			MenuVars.gOffset_Row[i][c] = NULL;

			MenuVars.Option_ToggleArr[i][c] = NULL;
			MenuVars.Option_ToggleArr_Size[i][c] = NULL;
			MenuVars.Option_ToggleArr_Cur[i][c] = NULL;
			MenuVars.bComboBox[i][c] = NULL;

			MenuVars.fBarValue[i][c] = NULL;
			MenuVars.fBarMin[i][c] = NULL;
			MenuVars.fBarMax[i][c] = NULL;
			MenuVars.fBarMod[i][c] = NULL;
		}
	}
}

void SetComboOption()
{
	int currentSub = MenuVars.currentMenu;
	MenuVars.iComboScroll = *MenuVars.Option_ToggleArr_Cur[currentSub][MenuVars.currentOption[currentSub]];
	MenuVars.iComboMax = MenuVars.Option_ToggleArr_Size[currentSub][MenuVars.currentOption[currentSub]];
	MenuVars.cComboData = MenuVars.Option_ToggleArr[currentSub][MenuVars.currentOption[currentSub]];

	MenuVars.bComboBox[currentSub][MenuVars.currentOption[currentSub]] = true;
}

void addMenu(Vars *MenuStruct, const char* Name, float MenuH, int Previous = -1)
{
	MenuIndex++;

	MenuStruct->MenuH[MenuIndex] = MenuH;
	MenuStruct->Menu_Title[MenuIndex] = Name;
	MenuStruct->previousMenu[MenuIndex] = Previous;
	MenuStruct->currentOption[MenuIndex] = 0;
}

void addGroup(Vars *MenuStruct, const char* Name, int Column, int Row, int Height)
{
	int GroupIndex = MenuStruct->displayCount[MenuIndex];
	MenuStruct->GroupName[MenuIndex][GroupIndex] = Name;
	MenuStruct->GroupHeight[MenuIndex][GroupIndex] = Height;
	MenuStruct->gOffset_Column[MenuIndex][GroupIndex] = Column;
	MenuStruct->gOffset_Row[MenuIndex][GroupIndex] = Row;
	MenuStruct->displayCount[MenuIndex]++;
}

void addBar(Vars *MenuStruct, const char *Name, int Column, int Row, float *value, float min, float max, float mod, void(*Function)(int) = NULL, int Param = -1)
{
	int Index = MenuStruct->optionCount[MenuIndex];
	MenuStruct->Offset_Column[MenuIndex][Index] = Column;
	MenuStruct->Offset_Row[MenuIndex][Index] = Row;
	MenuStruct->Option_Text[MenuIndex][Index] = Name;
	MenuStruct->Option_Function[MenuIndex][Index] = Function;
	MenuStruct->Option_Toggle[MenuIndex][Index] = NULL;
	MenuStruct->Option_Param1[MenuIndex][Index] = Param;
	MenuStruct->Option_ToggleArr[MenuIndex][Index] = NULL;
	MenuStruct->Option_ToggleArr_Size[MenuIndex][Index] = NULL;
	MenuStruct->fBarValue[MenuIndex][Index] = value;
	MenuStruct->fBarMin[MenuIndex][Index] = min;
	MenuStruct->fBarMax[MenuIndex][Index] = max;
	MenuStruct->fBarMod[MenuIndex][Index] = mod;
	MenuStruct->optionCount[MenuIndex]++;
}

void addCombo(Vars *MenuStruct, const char* Name, int Column, int Row, char **Array = NULL, int ArraySize = NULL, int *ArrayCur = 0, void(*Function)(int) = NULL, int Param = -1)
{
	int Index = MenuStruct->optionCount[MenuIndex];
	MenuStruct->Offset_Column[MenuIndex][Index] = Column;
	MenuStruct->Offset_Row[MenuIndex][Index] = Row;
	MenuStruct->Option_Text[MenuIndex][Index] = Name;
	MenuStruct->Option_Function[MenuIndex][Index] = Function;
	MenuStruct->Option_Toggle[MenuIndex][Index] = NULL;
	MenuStruct->Option_Param1[MenuIndex][Index] = Param;
	MenuStruct->Option_ToggleArr[MenuIndex][Index] = Array;
	MenuStruct->Option_ToggleArr_Size[MenuIndex][Index] = ArraySize;
	MenuStruct->Option_ToggleArr_Cur[MenuIndex][Index] = ArrayCur;
	MenuStruct->optionCount[MenuIndex]++;
}

void addOption(Vars *MenuStruct, const char* Name, int Column, int Row, bool* Toggle = NULL, void(*Function)(int) = NULL, int Param = -1)
{
	int Index = MenuStruct->optionCount[MenuIndex];
	MenuStruct->Offset_Column[MenuIndex][Index] = Column;
	MenuStruct->Offset_Row[MenuIndex][Index] = Row;
	MenuStruct->Option_Text[MenuIndex][Index] = Name;
	MenuStruct->Option_Function[MenuIndex][Index] = Function;
	MenuStruct->Option_Toggle[MenuIndex][Index] = Toggle;
	MenuStruct->Option_Param1[MenuIndex][Index] = Param;
	MenuStruct->Option_ToggleArr[MenuIndex][Index] = NULL;
	MenuStruct->Option_ToggleArr_Size[MenuIndex][Index] = NULL;
	MenuStruct->optionCount[MenuIndex]++;
}

void addSubToggle(Vars *MenuStruct, bool* Toggle = NULL)
{
	MenuStruct->Sub_Toggle[MenuIndex] = Toggle;
	MenuStruct->optionCount[MenuIndex]++;
}

void openSub(int Menu) {
	MenuVars.currentMenu = Menu;
}

void openRGB(int Index) {
	MenuVars.openState = 2;
	MenuVars.RGBScroll = 0;

	switch (Index) {
	case 0:
		MenuVars.RGBColor = Fade;
		break;
	case 1:
		MenuVars.RGBColor = defaultShader;
		break;
	case 2:
		MenuVars.RGBColor = defaultText;
		break;
	case 3:
		MenuVars.RGBColor = defaultEnemy;
		break;
	case 4:
		MenuVars.RGBColor = defaultFriend;
		break;
	case 5:
		MenuVars.RGBColor = defaultVisible;
		break;
	case 6:
		MenuVars.RGBColor = defaultTarget;
		break;
	case 7:
		MenuVars.RGBColor = colGRAY;
		break;
	default:
		break;
	}
}