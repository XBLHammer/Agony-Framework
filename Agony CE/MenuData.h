#include "Fade.h"

bool
bLegitbot = false,
bRapidFire = false,
bMultiBox = false,
bTriggerbot = false,
bBurstFire = false,
bAutoAim = false,
bRCS = false;

bool
bRagebot = false,
bSilent = false,
bSnapback = false,
bAutoShoot = false,
bPrediction = false,
bPointCorrection = false,
bNoSpread = false,
bNoRecoil = false,
bNoSway = false,
bAntiAntiAim = false,
bCrouchBot = false;


bool
bAntiAim = false,
bFakeLag = false,
bAirStuck = false;

bool
bDrawAxis = false,
bDrawAllies = false,
bBoxOutline = true,
bDrawBones = false,
bDrawName = false,
bDrawWeapon = false,
bDrawLines = false,
bDrawEntity = false,
bEntityLine = false,
bEntityName = false,
bRadar = false,
bCompass = false,
xfade = false,
bfademw2 = false,
bmapcolor,
bchickenchams = true,
bRadarAxis = false,
bRadarAlly = false,
bRadarEntity = false,
blazer = false,
bUAV = false,
bCompassAxis = false,
bCompassAlly = false,
bCompassEntity = false,
drawRadar = false,
drawEntites = false,
drawDeaths = false;

bool
bXHair = false,
bXHairSpread = false,
bFlashName = false,
bStealName = false,
bShowHost = false,
bProximity = false,
bVisible = false,
bUninfector = false;

bool bHarrierRiot = false;

float
fRndXMin = 0.0f,
fRndXMax = 360.0f,
fSpinSpeed = 20,
fRollSpeed = 15.0f;

bool
bFlashFx = false,
bPlayerList = false,
bSwitchTarget = false;

bool 
bTeleKill = false,
bNameSpam = false,
bNameSteal = false;

int dwSpamTick;

bool
bChams = true,
bwpColor = true,
bWireframe = true,
bSolid = false;

bool
bPlayerPriority[18],
bPlayerFriendly[18],
bPlayerBodyAim[18],
bSheildToPlayer[18];

bool bSnap = false;

float fFOVSize = 300.0f;
float fAimSpeed = 15.0f;
float fAimCurve = 3.0f;
float fPCorrection = -0.2f;
float fTriggerSeed = 1.5f;
float fTriggerDelay = 150.0f;
float fFOV = 85.0f;
float fStealSpeed = 100.0f;
float fLag = 200.0f;
float fPrediction = 10.0f;
float fRadarDist = 1.0f;
float fCompassSize = 200;

int Spinboi;

bool bKillfeed = false;

float fCrouchInteval = 600;
int dwCrouchTime;

bool bRespawn;
DWORD dwRespawnDelay;

int aimTags_c = 1;
int aimTags_s = 18;
char *aimTags[] =
{
	"j_head",
	"j_neck",
	"j_spineupper",
	"j_spinelower",
	"j_shoulder_ri",
	"j_shoulder_le",
	"j_elbow_ri",
	"j_elbow_le",
	"j_wrist_ri",
	"j_wrist_le",
	"j_hip_ri",
	"j_hip_le",
	"j_knee_ri",
	"j_knee_le",
	"j_ankle_ri",
	"j_ankle_le",
	"j_ball_ri",
	"j_ball_le",
};

int aimKeys_c = 0;
int aimKeys_s = 4;
char *aimKeys[] =
{
	"Autowall",
	"Visible",
	"When Aiming",
	"When Firing"
};

int xAntiAim_c = 0;
int xAntiAim_s = 8;
char *xAntiAim[] =
{
	"Off",
	"Riot",
	"Spin",
	"Fake-Static",
	"Jitter",
	"Fake-Jitter",
	"Fake-90",
	"J-Spin"
};

int yAntiAim_c = 0;
int yAntiAim_s = 7;
char *yAntiAim[] =
{
	"Off",
	"Riot",
	"Spin",
	"J-Down",
	"Down",
	"Up",
	"Rnd"
};

int zAntiAim_c = 0;
int zAntiAim_s = 5;
char *zAntiAim[] =
{
	"Off",
	"Roll",
	"Tilt",
	"Inverse",
	"Rnd"
};

int wallDetect_c = 0;
int wallDetect_s = 4;
char *wallDetect[] =
{
	"Off",
	"Normal",
	"Jitter",
	"Fake",
};

int cESPType_c = 0;
int cESPType_s = 6;
char *cESPType[] =
{
	"Off",
	"2D",
	"3D",
	"Corner",
	"Filled",
	"Pyramid"
};

float var_defaultColor[4] = { 1, 0, 0, 0.6 };
float var_defaultText[4] = { 1, 1, 1, .65 };
float var_defaultShader[4] = { 0, 0, 0, .25 };

/* Menu Colors */
float *defaultColor = Fade;
float *defaultText = var_defaultText;
float *defaultShader = var_defaultShader;

float *defaultEnemy = colorRedTrans;
float *defaultFriend = colorGreenTrans;
float *defaultVisible = colorYellowTrans;
float *defaultTarget = colorOrangeTrans;

bool bReset;
void ResetPlayers() {
	for (int i = 0; i < 18; i++) {
		bPlayerBodyAim[i] = false;
		bPlayerFriendly[i] = false;
		bPlayerPriority[i] = false;
		bSheildToPlayer[i] = false;
	}
	bReset = true;
}

bool bCrouchOnDmg,
bJitterFire;

#define aimBone MenuVars.Option_ToggleArr[0][7][*MenuVars.Option_ToggleArr_Cur[0][7]]
#define aimEvent *MenuVars.Option_ToggleArr_Cur[0][1]

char *szVersionNum = "1.0.1";
char *szMenuName = "Eclipse Framework";

float fclFlashMain[4] = { 0, 0, 1, 1 };

short autowallBox[22];
short multiBox[22];
short multiBoxbo1[4];
bool bPrecached;

bool bBezierSeedSet;

int 
MATERIAL_WHITE,
FONT_SMALLFONT;

float TextBackground[4] = {0,0,0,0.4f};