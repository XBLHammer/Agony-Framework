#include "stdafx.h"

namespace BO3
{

struct Vector2 {
	float x, y;

	Vector2() {
		x = y = 0.0f;
	}

	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	float distance(Vector2 &Vector) {
		return sqrt(distanceEx(Vector));
	}

	float distanceEx(Vector2 &Vector) {
		float _x = this->x - Vector.x, _y = this->y - Vector.y;
		return ((_x * _x) + (_y * _y));
	}
};

struct Vector3 {
	float x, y, z;

	Vector3() {
		x = y = z = 0.0f;
	}

	Vector3(float x, float y, float z) {
		this->x = x; this->y = y; this->z = z;
	}

	bool operator==(Vector3 &Vector) {
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}

	Vector3& operator+(Vector3 &Vector) {
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}

	Vector3& operator-(Vector3 &Vector) {
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}

	float distance(Vector3 &Vector) {
		return sqrt(distanceEx(Vector));
	}

	float distanceEx(Vector3 &Vector) {
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}

	float dotProduct(Vector3 &Vector) {
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
};

struct Vector4 {
	float a, b, c, d;

	Vector4() {
		a = b = c = d = 0.0f;
	}

	Vector4(float a, float b, float c, float d) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}
};

// angle conversions
#define GetPointer(X) *(DWORD*)(X);
#define GetPointer(X) *(DWORD*)(X);
#define M_1PI 3.14159265359f
#define M_2PI 6.28318530718f
#define AngleToShort(X) ((int)((X) * 65536 / 360) & 65535)
#define	ShortToAngle(X) ((X) * (360 / 65536))

// Some engine colors
static Vector4
whiteBO3 = Vector4(1, 1, 1, 1),
blackBO3 = Vector4(0, 0, 0, 1),
L_blackBO3 = Vector4(0, 0, 0, 0.2),
L_red2BO3 = Vector4(1, 0, 0, 0.4),
BlueStormzBO3 = Vector4(0.118, 0.639, 0.902, 1),
L_green2BO3 = Vector4(0, 1, 0, 0.4),
redBO3 = Vector4(1, 0, 0, 1),
greenBO3 = Vector4(0, 1, 0, 1),
blueBO3 = Vector4(0, 0, 1, 1),
yellowBO3 = Vector4(1, 1, 0, 1),
greyBO3 = Vector4(1.0f, 1.0f, 1.0f, 0.50f);

template<typename T> union XAssetPoolEntryBO3 {
	T entry;
	T *next;
};

template<typename T, int size> struct XAssetPoolBO3 {
	T *freeHead;
	XAssetPoolEntryBO3<T> entries[size];
};

enum XAssetTypeBO3 {
	physpresetBO3,
	physconstraintsBO3,
	destructibledefBO3,
	xanimBO3,
	xmodelBO3,
	xmodelmeshBO3,
	materialBO3,
	pixelshaderBO3,
	techsetBO3,
	imageBO3,
	soundBO3,
	sound_patchBO3,
	col_mapBO3,
	com_mapBO3,
	game_mapBO3,
	map_entsBO3,
	gfx_mapBO3,
	lightdefBO3,
	lensflaredefBO3,
	ui_mapBO3,
	fontBO3,
	fonticonBO3,
	localizeBO3,
	weaponBO3,
	weapondefBO3,
	weaponvariantBO3,
	weaponfullBO3,
	cgmediatableBO3,
	playersoundstableBO3,
	playerfxtableBO3,
	sharedweaponsoundsBO3,
	attachmentBO3,
	attachmentuniqueBO3,
	weaponcamoBO3,
	customizationtableBO3,
	customizationtable_feimagesBO3,
	customizationtablecolorBO3,
	snddriverglobalsBO3,
	fxBO3,
	fx_aliasBO3,
	tagfxBO3,
	klfBO3,
	impactsfxtableBO3,
	impactsoundstableBO3,
	player_characterBO3,
	aitypeBO3,
	characterBO3,
	xmodelaliasBO3,
	rawfileBO3,
	stringtableBO3,
	structuredtableBO3,
	leaderboarddefBO3,
	ddlBO3,
	glassesBO3,
	texturelistBO3,
	scriptparsetreeBO3,
	keyvaluepairsBO3,
	vehicleBO3,
	addon_map_entsBO3,
	tracerBO3,
	skinnedvertsBO3,
	slugBO3,
	surfacefxtableBO3,
	surfacesounddefBO3,
	footsteptableBO3,
	entityfximpactsBO3,
	entitysoundimpactsBO3,
	zbarrierBO3,
	vehiclefxdefBO3,
	vehiclesounddefBO3,
	typeinfoBO3,
	scriptbundleBO3,
	scriptbundlelistBO3,
	rumbleBO3,
	bulletpenetrationBO3,
	locdmgtableBO3,
	aimtableBO3,
	animselectortableBO3,
	animmappingtableBO3,
	animstatemachineBO3,
	behaviortreeBO3,
	behaviorstatemachineBO3,
	ttfBO3,
	lightdescriptionBO3,
	shellshockBO3,
	xcamBO3,
	bgcacheBO3,
	texturecomboBO3,
	flametableBO3,
	bitfieldBO3,
	attachmentcosmeticvariantBO3,
	maptableBO3,
	maptableloadingimagesBO3,
	medalBO3,
	medaltableBO3,
	objectiveBO3,
	objectivelistBO3,
	umbra_tomeBO3,
	navmeshBO3,
	navvolumeBO3,
	binaryhtmlBO3,
	laserBO3,
	beamBO3,
	streamerhintBO3,
	texture_atlasBO3,
	gfx_map_trzoneBO3,
	col_map_trzoneBO3,
	stringBO3,
	assetlistBO3,
	reportBO3,
	dependBO3
};

#pragma pack(push, 2)
struct GlyphBO3 {
	unsigned __int16 letter;
	char x0;
	char y0;
	char dx;
	char pixelWidth;
	char pixelHeight;
	float s0;
	float t0;
	float s1;
	float t1;
};
#pragma pack(pop)

struct KerningPairsBO3 {
	unsigned __int16 wFirst;
	unsigned __int16 wSecond;
	int iKernAmount;
};

struct Font_sBO3 {
	const char *fontName;
	int pixelHeight;
	int isScalingAllowed;
	int glyphCount;
	int kerningPairsCount;
	/*Material *material;
	Material *glowMaterial;*/
	void *material;
	void *glowMaterial;
	GlyphBO3 *glyphs;
	KerningPairsBO3 *kerningPairs;
};


struct RawFileBO3 {
	const char *name;
	int length;
	const char *buffer;
};

union XAssetHeaderBO3 {
	Font_sBO3 *font;
	RawFileBO3 *rawfile;
	void *data;
};

#pragma pack(push, 1)

enum entityType_tBO3 {
	ET_GENERALBO3,
	ET_PLAYERBO3,
	ET_PLAYER_CORPSEBO3,
	ET_ITEMBO3,
	ET_MISSILEBO3,
	ET_PLAYER_INVISIBLEBO3,
	ET_SCRIPTMOVERBO3,
	ET_SOUND_BLENDBO3,
	ET_FXBO3,
	ET_LOOP_FXBO3,
	ET_PRIMARY_LIGHTBO3,
	ET_LENSFLAREBO3,
	ET_REFLECTION_PROBEBO3,
	ET_HELICOPTERBO3,
	ET_PLANEBO3,
	ET_VEHICLEBO3,
	ET_VEHICLE_SPAWNERBO3,
	ET_VEHICLE_CORPSEBO3,
	ET_ACTORBO3,
	ET_ACTOR_SPAWNERBO3,
	ET_ACTOR_CORPSEBO3,
	ET_STREAMER_HINTBO3,
	ET_ZBARRIERBO3,
	ET_TRIGGERBO3
};

struct cached_client_tag_tBO3 {
	int time; // 0x0000
	Vector3 lastLocalTagOrigin; // 0x0004
	int visible; // 0x0010 doesnt update
	int predictedTime; // 0x0014
	Vector3 predictedPosition; // 0x0018
	Vector3 predictedAngles; // 0x0024
}; // size: 0x30

struct ClientTagCacheBO3 {
	cached_client_tag_tBO3 aim_head_tag; // 0x0000
	cached_client_tag_tBO3 aim_highest_tag; // 0x0030
}; // size: 0x60 possibly different
C_ASSERT(sizeof(ClientTagCacheBO3) == 0x60);

enum flags_tBO3 {
	FLAG_STANDINGBO3 = 0x02,
	FLAG_CROUCHBO3 = 0x04,
	FLAG_PRONEBO3 = 0x08,
	FLAG_SPRINTINGBO3 = 0x20000,
	FLAG_DEATHBO3 = 0x40000, // cant use this bc its reset during killcam
	FLAG_ADSBO3 = 0x80000
};

struct centity_sBO3 {
	BYTE _0x0000[40];
	Vector3 origin; // 0x0028
	Vector3 angles; // 0x0034
	BYTE _0x0040[536]; //0x0040 - 0x0258
	int clientNumber; // 0x0258
	BYTE _0x025C[4]; // 0x025C
	int flags; // 0x0260
	BYTE _0x0264[300]; // 0x0264 - 0x0390
	int weapon; // 0x0390
	BYTE _0x0394[45]; // 0x0394
	BYTE eType; // 0x03C1
	BYTE _0x03C2[58]; // 0x03C2 - 0x03F4
	ClientTagCacheBO3 *clientTagCache; // 0x03F4
	BYTE _0x03FC[480]; // 0x0454 - 0x0638
	BYTE alive; // 0x0638
	BYTE _0x063C[95]; // 0x063C
}; // size: 0x640
C_ASSERT(sizeof(centity_sBO3) == 0x640);

enum buttonsBO3 {
	BT_LTBO3 = 0x100080,
	BT_RTBO3 = 0x80000000
};

struct usercmd_sBO3 {
	int time; // 0x0000
	int buttons; // 0x0004
	BYTE _0x0008[8];
	int angles[3]; // 0x0010
	BYTE _0x001C[36];
}; // size: 0x40

struct clientActive_tBO3 {
	BYTE _0x0000[208];
	Vector3 origin; // 0x00D0
	Vector3 velocity; // 0x00DC
	BYTE _0x00E8[0x15C - 0xE8];
	Vector3 spawnAngles; // 0x015C
	BYTE _0x0168[0x31A0 - 0x168];
	Vector3 viewAngles; // 0x31A0
	BYTE _0x31AC[0x231BC - 0x31AC];
	usercmd_sBO3 usercmds[128]; // 0x231BC
	int commandNumber; // 0x251BC

	usercmd_sBO3 *getUserCmd(int i) {
		return &usercmds[i & 0x7F];
	}

	usercmd_sBO3 *getUserCmd() {
		return getUserCmd(this->commandNumber);
	}

}; // size: custom

struct cgs_tBO3 {
	int viewX; // 0x0000
	int viewY; // 0x0004
	int viewWidth; // 0x0008
	int viewHeight; // 0x000C
	float viewAspect; // 0x0010
	BYTE _0x0014[24];
	int localServer; // 0x002C
	char gametype[32]; // 0x0030
	char hostname[256]; // 0x0050
	int maxClients; // 0x0150
	BYTE _0x0154[4];
	char mappath[64]; // 0x0158
	char mapname[64]; // 0x0198
}; // size: custom

struct refdef_sBO3 {
	int x; // 0x0000
	int y; // 0x0004
	int width; // 0x0008
	int height; // 0x000C
	BYTE _0x0010[100];
	float zoomProgress; // 0x0074
	float tanHalfFovX; // 0x0078
	float tanHalfFovY; // 0x007C
	BYTE _0x0080[4];
	Vector3 viewOrigin; // 0x0084
	BYTE _0x0090[16];
	Vector3 viewAxis[3]; // 0x00A0
	BYTE _0x00C4[4];
	int time; // 0x00C8
}; // size: custom: 0xCC

struct clientInfo_tBO3 {
	int infoValid; // 0x0000
	int nextValid; // 0x0004
	int clientNumber; // 0x0008
	char name[32]; // 0x000C
	int team; // 0x002C
	int oldteam; // 0x0030
	int ffateam; // 0x0034
	int lastrank; // 0x0038
	BYTE _0x003C[36];
	char clantag[4]; // 0x0060
	BYTE _0x0064[4];
	int ping; // 0x0068
	int status_icon; // 0x006C
	int place; // 0x0070
	int score; // 0x0074
	int kills; // 0x0078
	int assists; // 0x007C
	int deaths; // 0x0080
	BYTE _0x0084[68];
	int health; // 0x00C8
	BYTE _0x00CC[1308];
	long long flags; // 0x05E8
	BYTE _0x05F0[908];
	int weapon; // 0x097C
}; // size: 0x980
C_ASSERT(sizeof(clientInfo_tBO3) == 0x980);

struct playerState_sBO3 {
	BYTE _0x0000[4];
	int cmdTime; // 0x0004
	BYTE _0x0008[88];
	Vector3 origin; // 0x0060
	Vector3 velocity; // 0x006C
	BYTE _0x0078[592];
	float weaponPosFraction; //0x02C8
}; // size: custom: 0x02CC

struct cg_sBO3 {
	int clientNumber; // 0x0000
	int localClientNumber; // 0x0004
	BYTE _0x0008[156];
	int stanceState; // 0x00A4
	BYTE _0x00A8[24];
	Vector3 origin; // 0x00C0
	Vector3 velocity; // 0x00CC
	BYTE _0x00D8[0x2C180 - 0xD8];
	playerState_sBO3 ps; // 0x2C180
	BYTE _0x2C44C[0x32550 - 0x2C44C];
	refdef_sBO3 refdef;  // 0x32550
	BYTE _0x3261C[0x54E10 - 0x3261C];
	clientInfo_tBO3 ci[12]; // 0x54E10
	BYTE _0x5C010[0x675A0 - 0x5C010];
	float aimSpreadScale; // 0x675A0
};

/*struct game_shit_s  {
	cgs_t *cgs;
	BYTE _one[0x14];
	cg_s *cg;
	BYTE _two[0x10];
	centity_s *cents;
	BYTE _three[0x15701A4];
	clientActive_t *client;
};*/

struct GfxCmdDrawText2DBO3 {
	BYTE _0x0000[12];
	float x; // 0x000C
	float y; // 0x0010
	float w; // 0x0014
	BYTE _0x0018[8];
	Font_sBO3 *font; // 0x0020
	float xScale; // 0x0024
	float yScale; // 0x0028
	int color; // 0x002C
	int maxChars; // 0x0030
	int renderFlags; // 0x0034
	BYTE _0x0038[12];
	int glowForceColor; // 0x0044
	int fxDecayDuration; // 0x0048
	int fxRedactDecayStartTime; // 0x004C
	int fxRedactDecayDuration; // 0x0050
	BYTE _0x0054[16];
	float padding; // 0x0064
	int text; // 0x0068
};

enum TraceHitTypeBO3 : int {
	TRACE_HITTYPE_NONEBO3 = 0x00,
	TRACE_HITTYPE_ENTITYBO3 = 0x01,
	TRACE_HITTYPE_DYNENT_MODELBO3 = 0x02,
	TRACE_HITTYPE_DYNENT_BRUSHBO3 = 0x03,
	TRACE_HITTYPE_GLASSBO3 = 0x04,
};

// i could easily do the rest but im lazy
struct trace_tBO3 {
	BYTE _0x0000[16];
	float fraction; // 0x0010
	BYTE _0x0014[44];
};

struct BulletFireParamsBO3 {
	int weaponEntIndex; // 0x00
	int ignoreEntIndex; // 0x04
	float damageMultiplier; // 0x08
	int methodOfDeath; // 0x0C
	Vector3 origStart; // 0x10
	Vector3 start; // 0x1C
	Vector3 end; // 0x28
	Vector3 dir; // 0x34
	BYTE _0x40[12];
}; // size: 0x4C

#pragma pack(pop)

/////////////////////////////////////// BO3 Menu /////////////////////////////////////

char tagnamesBO3[20][32] = {
	"j_helmet",
	"j_head",
	"j_neck",
	"j_shoulder_le",
	"j_shoulder_ri",
	"j_elbow_le",
	"j_elbow_ri",
	"j_wrist_le",
	"j_wrist_ri",
	"j_gun",
	"j_mainroot",
	"j_spineupper",
	"j_spinelower",
	"j_spine4",
	"j_hip_le",
	"j_hip_ri",
	"j_knee_le",
	"j_knee_ri",
	"j_ankle_le",
	"j_ankle_ri"
};

const char *(*vaBO3)(const char *format, ...)
= (const char *(*)(const char *, ...))0x826BECE0; //TU8

short(*SL_GetStringOfSizeBO3)(const char *text, int user, int length)
= (short(*)(const char *, int, int))0x822D2248; //TU8

bool(*CG_DObjGetWorldTagPosBO3)(centity_sBO3 *entity, int obj, short tagname, Vector3 &pos)
= (bool(*)(centity_sBO3 *, int, short, Vector3 &))0x8221ACF0; //TU8

void(*CG_LocationalTraceBO3)(trace_tBO3 *results, Vector3 &start, Vector3 &end, int passEntityNumber, int contentMask, bool checkRopes, int *context)
= (void(*)(trace_tBO3 *, Vector3 &, Vector3 &, int, int, bool, int *))0x82285838; //TU8

bool(*BulletPenetrateCheckBO3)(BulletFireParamsBO3 *bp)
= (bool(*)(BulletFireParamsBO3 *))0x82271A60; //TU8

void(*FireBulletPenetrateBO3)(int localClientNumber, BulletFireParamsBO3 *bp, int weapon, int passEntityNumber, Vector3 &tracerStart, bool drawTracer)
= (void(*)(int, BulletFireParamsBO3 *, int, int, Vector3 &, bool))0x82272708; //TU8

GfxCmdDrawText2DBO3 *(*AddBaseDrawTextCmdBO3)(const char *text, int maxChars, Font_sBO3 *font, float x, float y, float xScale, float yScale, Vector4 &color, int style)
= (GfxCmdDrawText2DBO3 *(*)(const char *, int, Font_sBO3 *, float, float, float, float, Vector4 &, int))0x824AE7C0; //TU8

void(*SetDrawText2DGlowParmsBO3)(GfxCmdDrawText2DBO3 *cmd, Vector4 &color, Vector4 &glowColor)
= (void(*)(GfxCmdDrawText2DBO3 *, Vector4 &, Vector4 &))0x824AE910; //TU8

int(*UI_TextWidthBO3)(const char *text, int maxChars, Font_sBO3 *font, float scale)
= (int(*)(const char *, int, Font_sBO3 *, float))0x826A1F20; //TU8

void(*CG_DrawRotatedPicPhysicalBO3)(int scrPlace, float x, float y, float width, float height, float angle, Vector4 &color, void *material, int)
= (void(*)(int, float, float, float, float, float, Vector4 &, void *, int))0x82210468; //TU8

void(*BG_GetSpreadForWeaponBO3)(playerState_sBO3 *ps, int weapon, float *minSpread, float *maxSpread)
= (void(*)(playerState_sBO3 *, int, float *, float *))0x821DC870; //TU8


XAssetHeaderBO3(*DB_FindXAssetHeaderBO3)(XAssetTypeBO3 type, const char *name, bool createIfMissing, int waitTime)
= (XAssetHeaderBO3(*)(XAssetTypeBO3, const char *, bool, int))0x82328110; //TU8

bool BO3ProximityWarning(float PlayerDisctance)
{
	if (PlayerDisctance <= 10)
		return true;

	else return false;
}

cg_sBO3 *cgBO3;
cgs_tBO3 *cgsBO3;
centity_sBO3 *centsBO3;
clientActive_tBO3 *clientBO3;

bool CanDrawTargetedESPBO3 = false;
bool DrawTargetDetailsBO3 = false;
bool FirstTimeInGameBO3 = false;
bool openBO3 = false;
int scrollBO3 = 0, maxoptionsBO3 = 6;
char optionsBO3[][32] = {
	"Aimbot Options",
	"ESP Options",
	"No Recoil",
	"Advanced UAV",
	"No Sway",
	"Crosshair"
};
bool boptionsBO3[6] = { false };
bool *norecoilBO3 = &boptionsBO3[2];
bool *advanceduavBO3 = &boptionsBO3[3];
bool *noswayBO3 = &boptionsBO3[4];

int ESPscrollBO3 = 0, ESPmaxoptionsBO3 = 7;
char ESPoptionsBO3[][32] = {
	"ESP Type:",
	"ESP Details",
	"ESP Bones",
	"ESP Health",
	"ESP Team:",
	"Snap Line Pos:",
	"Snap Line Team:",
};
bool ESPboptionsBO3[7] = { false };
bool *ESPNamesBO3 = &ESPboptionsBO3[1];
bool *ESPBonesBO3 = &ESPboptionsBO3[2];
bool *ESPHealthBO3 = &ESPboptionsBO3[3];

int AimscrollBO3 = 0, AimmaxoptionsBO3 = 7;
char AimoptionsBO3[][32] = {
	"Aimbot Type:",
	"Auto Aim",
	"No Spread",
	"Spin Bot",
	"Visible Warning",
	"Proximity Warning",
	"Target Details"
};
bool AimboptionsBO3[7] = { false };
bool *AutoAimBO3 = &AimboptionsBO3[1];
bool *nospreadBO3 = &AimboptionsBO3[2];
bool *SpinBotBO3 = &AimboptionsBO3[3];
bool *VisibleWarningBO3 = &AimboptionsBO3[4];
bool *ProximityWarningBO3 = &AimboptionsBO3[5];
bool *TargetDetailsBO3 = &AimboptionsBO3[6];

char AimbotTypeBO3[6][32] = {
	"Nearest",
	"Auto Wall",
	"Crosshair",
	"Silant Aim",
	"Favor Visible",
	"OFF"
};

char espTypeBO3[4][32] = {
	"2D",
	"3D",
	"Pyramid",
	"OFF"
};

char ESPTeamTypeBO3[4][32] = {
	"Enemy",
	"Friendly",
	"Both",
	"OFF"
};

char SnapLineTypeBO3[4][32] = {
	"Middle",
	"Bottom",
	"Top",
	"OFF"
};

char SnapLineTeamTypeBO3[4][32] = {
	"Enemy",
	"Friendly",
	"Both",
	"OFF"
};

char CrossHairTypeBO3[3][32] = {
	"+",
	"X",
	"OFF"
};

int BO3_MAIN = 0, BO3_AIMBOT = 1, BO3_ESP = 2;
int currentBO3 = BO3_MAIN;
int BO3_NEAREST = 0, BO3_ONSCREEN = 1, BO3_CROSSHAIR = 2, BO3_SILANT_AIM = 3, BO3_FAVOR_VISIBLE = 4, BO3_AIMBOT_OFF = 5;
int CurrentBO3Aimbot = BO3_AIMBOT_OFF;
int BO3_TWO_D = 0, BO3_THREE_D = 1, BO3_PYRAMID = 2, BO3_ESP_OFF = 3;
int CurrentBO3ESP = BO3_ESP_OFF;
int ESPEnemyBO3 = 0, ESPFriendlyBO3 = 1, ESPBothBO3 = 2, ESPOffBO3 = 3;
int ESPBO3 = ESPOffBO3;
int SnapLineMiddleBO3 = 0, SnapLineBottomBO3 = 1, SnapLineTopBO3 = 2, SnapLinesOffBO3 = 3;
int SnapLinePosBO3 = SnapLinesOffBO3;
int SnapLineEnemyBO3 = 0, SnapLineFriendlyBO3 = 1, SnapLineTeamBothBO3 = 2, SnapLineTeamOffBO3 = 3;
int SnapLineTeamBO3 = SnapLineTeamOffBO3;
int PlusCrosshairBO3 = 0, XCrosshairBO3 = 1, CrosshairOffBO3 = 2;
int CrossHairBO3 = CrosshairOffBO3;

bool isInGameBO3() {
	//	Dvar_FindDvar = (DWORD (__cdecl*)(char*))0x826B6C38;
	//	Dvar_GetBool = (BOOL (__cdecl*)(DWORD))0x826B4A20;
	////	SamuraiPrint("Dvar: %04X", Dvar_FindDvar("cl_ingame"));
	//	if (Dvar_GetBool(Dvar_FindDvar("cl_ingame"))) SamuraiPrint("True");
	return !*(WORD *)0x8447A32C && centsBO3 && cgBO3 && cgsBO3; //TU8
}

short registerTagBO3(const char *tagname) {
	return SL_GetStringOfSizeBO3(tagname, 1, strlen(tagname) + 1);
}

bool getTagPosBO3(centity_sBO3 *entityBO3, short tagname, Vector3 &pos) {
	int clientObjMap1 = 0x83EC1440; //TU8
	int r11 = *(short *)(clientObjMap1 + (entityBO3->clientNumber << 1));

	if (!r11)
		return false;

	int objBuf1 = 0x83E71440; //TU8
	int dobj = objBuf1 + (r11 * 0xA0);
	return CG_DObjGetWorldTagPosBO3(entityBO3, dobj, tagname, pos);
}

short j_headBO3, j_helmetBO3, j_ankle_riBO3, j_ankle_leBO3;
bool getHeadPosBO3(centity_sBO3 *entityBO3, Vector3 &headpos) {
	if (!j_headBO3)
		j_headBO3 = registerTagBO3("j_head");

	return getTagPosBO3(entityBO3, j_headBO3, headpos);
}

bool getNamedTagPosBO3(centity_sBO3 *entityBO3, Vector3 &headpos, const char* tag) {
	short tmp = registerTagBO3(tag);

	return getTagPosBO3(entityBO3, tmp, headpos);
}

float getEntityHeightBO3(centity_sBO3 *entityBO3) {
	if (!j_helmetBO3)
		j_helmetBO3 = registerTagBO3("j_helmet");

	Vector3 helmetpos;
	if (getTagPosBO3(entityBO3, j_helmetBO3, helmetpos)) {
		// add a little so we dont interfere with bone esp
		return (helmetpos.z - entityBO3->origin.z) + 2.0f;
	}

	return 62.0f;
}

// quake 3 source is killa mate
void vectorAnglesBO3(Vector3 &vector, Vector3 &angles) {
	float forward, yaw, pitch;

	if (vector.x == 0 && vector.y == 0.0f) {
		yaw = 0.0f;
		if (vector.z > 0.0f) {
			pitch = 90.0f;
		}
		else {
			pitch = 270.0f;
		}
	}
	else {
		if (vector.x) {
			yaw = (float)(atan2(vector.y, vector.x) * (180.0f / M_1PI)); // degress from radians
		}
		else if (vector.y > 0.0f) {
			yaw = 90.0f;
		}
		else {
			yaw = 270.0f;
		}

		if (yaw < 0.0f) {
			yaw += 360.0f;
		}

		forward = sqrt((vector.x * vector.x) + (vector.y * vector.y));
		pitch = (float)(atan2(vector.z, forward) * (180.0f / M_1PI)); // degress from radians

		if (pitch < 0.0f) {
			pitch += 360.0f;
		}
	}

	angles.x = -pitch; // weird ass pitches
	angles.y = yaw;
	angles.z = 0.0f;
}
void angleVectorsBO3(Vector3 &angles, Vector3 *forward, Vector3 *right, Vector3 *up) {
	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = angles.y * (M_2PI / 360.0f);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles.x * (M_2PI / 360.0f);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles.z * (M_2PI / 360.0f);
	sr = sin(angle);
	cr = cos(angle);

	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right) {
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up) {
		up->x = (cr*sp*cy + -sr * -sy);
		up->y = (cr*sp*sy + -sr * cy);
		up->z = cr * cp;
	}
}

bool isEntityVisibleBO3(centity_sBO3 *entityBO3) {
	Vector3 headpos;
	if (!getHeadPosBO3(entityBO3, headpos))
		return false;

	trace_tBO3 trace;
	CG_LocationalTraceBO3(&trace, cgBO3->refdef.viewOrigin, headpos, cgBO3->clientNumber, 0x280F803, false, 0);

	return (trace.fraction >= 0.95f); // fraction of material between two points
}

void angleVectors1(Vector3 &angles, Vector3 *forward, Vector3 *right, Vector3 *up) {
	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = angles.y * (M_PI * 2.0f / 360.0f);
	sy = sinf(angle);
	cy = cosf(angle);
	angle = angles.x * (M_PI * 2.0f / 360.0f);
	sp = sinf(angle);
	cp = cosf(angle);
	angle = angles.z * (M_PI * 2.0f / 360.0f);
	sr = sinf(angle);
	cr = cosf(angle);

	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right) {
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up) {
		up->x = (cr*sp*cy + -sr * -sy);
		up->y = (cr*sp*sy + -sr * cy);
		up->z = cr * cp;
	}
}


bool(*CG_DObjGetWorldTagPosBO31)(centity_sBO3 *entity, int obj, short tagname, Vector3 &pos)
= (bool(*)(centity_sBO3 *, int, short, Vector3 &))0x8221ACF0; //TU8

Vector3 NullVec;
Vector3 Vec, aVec;
Vector3 GetTagPos1(int EntNum, SHORT Tag) {

	int clientObjMap1 = 0x83EC1440; //TU8
	int r11 = *(short *)(clientObjMap1 + (EntNum << 1));

	int objBuf1 = 0x83E71440; //TU8
	int dobj = objBuf1 + (r11 * 0xA0);
	Vector3 NullVec;
	Vector3 Vec, aVec;
	CG_DObjGetWorldTagPosBO31(&centsBO3[EntNum], dobj, Tag, Vec);

	return Vec;
}

bool canKillEntityBO3(centity_sBO3 *entityBO3) {
	Vector3 headpos;

	BulletFireParamsBO3 bp;
	bp.weaponEntIndex = 0x2BE;
	bp.ignoreEntIndex = cgBO3->localClientNumber;
	bp.damageMultiplier = 1.0f;
	bp.methodOfDeath = 1;
	bp.start = cgBO3->refdef.viewOrigin;
	bp.origStart = cgBO3->refdef.viewOrigin;

	j_headBO3 = registerTagBO3("j_head");

	bp.end = GetTagPos1(entityBO3->clientNumber, j_headBO3);

	Vector3 angles;
	angleVectors1(headpos - cgBO3->refdef.viewOrigin, &angles, &bp.dir, NULL);

	if (!BulletPenetrateCheckBO3(&bp))
		return false;

	// stop shit
	*(short *)0x8269EBE0 = 0x4800; // CG_SpawnTracer //TU8
	*(int *)0x8227165C = 0x48000084; // CG_BulletHitEvent //TU8

	FireBulletPenetrateBO3(0, &bp, centsBO3[cgBO3->clientNumber].weapon, cgBO3->clientNumber, cgBO3->refdef.viewOrigin, false);

	// restore shit
	*(short *)0x8269EBE0 = 0x4099; // CG_SpawnTracer //TU8
	*(int *)0x8227165C = 0x41820040; // CG_BulletHitEvent //TU8

	return (bp.ignoreEntIndex == entityBO3->clientNumber);// && bp.damageMultiplier > 0.80f);
}

int findClosestClientBO3() {
	int closestClient = -1;
	float lastDistance = 1000000.0f;
	for (int i = 0; i < cgsBO3->maxClients; i++) {
		if (i == cgBO3->clientNumber) // client is our own
			continue;

		if (cgBO3->ci[i].team == cgBO3->ci[cgBO3->clientNumber].team) // team check
			if (cgBO3->ci[i].team != 0) // ffa
				continue;

		if (!(centsBO3[i].alive & 2) || cgBO3->ci[i].health < 1) // alive check
			continue;

		if(!isEntityVisibleBO3(&centsBO3[i]) ) // visibility check
		continue;

		if (!canKillEntityBO3(&centsBO3[i]) && CurrentBO3Aimbot == BO3_FAVOR_VISIBLE) // auto wall mate
		{
			continue;
		}

		float d = clientBO3->origin.distance(centsBO3[i].origin);
		if (d < lastDistance) {
			lastDistance = d;
			closestClient = i;
		}
	}

	return closestClient;
}

int findFavorVisibleClientBO3(BOOL visibleclient = TRUE) {
	int closestClient = -1;
	float lastDistance = 1000000.0f;
	for (int i = 0; i < cgsBO3->maxClients; i++) {
		if (i == cgBO3->clientNumber) // client is our own
			continue;

		if (cgBO3->ci[i].team == cgBO3->ci[cgBO3->clientNumber].team) // team check
			if (cgBO3->ci[i].team != 0) // ffa
				continue;

		if (!(centsBO3[i].alive & 2) || cgBO3->ci[i].health < 1) // alive check
			continue;

		if (!isEntityVisibleBO3(&centsBO3[i]) && visibleclient == TRUE) // visibility check
			continue;

		float d = clientBO3->origin.distance(centsBO3[i].origin);
		if (d < lastDistance) {
			lastDistance = d;
			closestClient = i;
		}
	}

	if (visibleclient == TRUE && closestClient == -1)
	{
		return findFavorVisibleClientBO3(FALSE);
	}
	return closestClient;
}

bool worldToScreenBO3(Vector3 &world, Vector2 &screen) {
	// bool CG_CalcNamePosition(int localClientNumber, float *origin, float *x, float *y);

	refdef_sBO3 *refdefBO3 = &cgBO3->refdef;

	Vector3 delta = world - refdefBO3->viewOrigin, projections;
	projections.x = delta.dotProduct(refdefBO3->viewAxis[0]);
	projections.y = delta.dotProduct(refdefBO3->viewAxis[1]);
	projections.z = delta.dotProduct(refdefBO3->viewAxis[2]);

	if (projections.x > 0.0f) {
		// scrPlace->realViewportBase is usually null anyway
		int cx = refdefBO3->width / 2, cy = refdefBO3->height / 2;
		float x = projections.y / refdefBO3->tanHalfFovX;
		screen.x = cx * (1.0f - (x / projections.x));
		float y = projections.z / refdefBO3->tanHalfFovY;
		screen.y = cy * (1.0f - (y / projections.x));

		return true;
	}

	return false;
}

bool aimlol;
VOID BO3_Aimbot()
{
	cgBO3 = (cg_sBO3*)GetPointer(0x82E819D8); //TU8
	cgsBO3 = (cgs_tBO3*)GetPointer(0x82E819C0); //TU8
	centsBO3 = (centity_sBO3*)GetPointer(0x82E819EC); //TU8
	clientBO3 = (clientActive_tBO3*)GetPointer(0x84475F74); //TU8
	if (isInGameBO3()) {
		usercmd_sBO3 *cmdBO3 = clientBO3->getUserCmd();
		if (CurrentBO3Aimbot != BO3_AIMBOT_OFF && CurrentBO3Aimbot != BO3_FAVOR_VISIBLE)
		{
			int cc = findClosestClientBO3();
			if (cc != -1) {
				Vector3 headpos, angles, newangles;
				getNamedTagPosBO3(&centsBO3[cc], headpos, "j_neck");
				vectorAnglesBO3(headpos - cgBO3->refdef.viewOrigin, angles);
				newangles = angles - clientBO3->spawnAngles;
				if (CurrentBO3Aimbot == BO3_SILANT_AIM) {
					cmdBO3->angles[0] = AngleToShort(newangles.x);
					cmdBO3->angles[1] = AngleToShort(newangles.y);
				}
				else {
					clientBO3->viewAngles = newangles;
				}
				DrawTargetDetailsBO3 = true;
				aimlol = true;
			}
			else
			{
				DbgPrint("lol\n");
				aimlol = false;
			}
		}

		if (CurrentBO3Aimbot != BO3_AIMBOT_OFF && CurrentBO3Aimbot == BO3_FAVOR_VISIBLE)
		{
			usercmd_sBO3 *cmdBO3 = clientBO3->getUserCmd();
			int cc = findFavorVisibleClientBO3();
			if (cc != -1) {
				Vector3 headpos, angles, newangles;
				getNamedTagPosBO3(&centsBO3[cc], headpos, "j_neck");
				vectorAnglesBO3(headpos - cgBO3->refdef.viewOrigin, angles);
				newangles = angles - clientBO3->spawnAngles;
				clientBO3->viewAngles = newangles;
				DrawTargetDetailsBO3 = true;
				aimlol = true;
			}
			else
			{
				DbgPrint("lol\n");
				aimlol = false;
			}
		}
	}
}

void compensateSpreadBO3(usercmd_sBO3 *cmdBO3) {
	float minSpread, maxSpread, pitch, yaw;
	int weapon = centsBO3[cgBO3->clientNumber].weapon;
	BG_GetSpreadForWeaponBO3(&cgBO3->ps, weapon, &minSpread, &maxSpread);

	float aimSpreadScale = cgBO3->aimSpreadScale / 255.0f;
	float aimSpreadAmount = minSpread + ((maxSpread - minSpread) * aimSpreadScale);

	pitch *= aimSpreadAmount;
	yaw *= aimSpreadAmount;

	cmdBO3->angles[0] += AngleToShort(pitch);
	cmdBO3->angles[1] += AngleToShort(yaw);
}

int __declspec(naked) CL_WritePacketHookStubBO3(int localClientNumber) {
	__asm {
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

	if (isInGameBO3()) {
		if (aimlol)
		{
			pState->Gamepad.bLeftTrigger = 255;
			pState->Gamepad.bRightTrigger = 255;
		}
	}

	return dwResult;
}


int CL_WritePacketHookBO3(int localClientNumber) {
	cgBO3 = (cg_sBO3*)GetPointer(0x82E819D8); //TU8
	cgsBO3 = (cgs_tBO3*)GetPointer(0x82E819C0); //TU8
	centsBO3 = (centity_sBO3*)GetPointer(0x82E819EC); //TU8
	clientBO3 = (clientActive_tBO3*)GetPointer(0x84475F74); //TU8
	if (isInGameBO3()) {
		usercmd_sBO3 *cmdBO3 = clientBO3->getUserCmd();

		Vector3 SpinBotView;
		int SpinBotAngles = 0;

		SpinBotAngles++; // * a number will increase speed
		if (SpinBotAngles > 359 && SpinBotAngles < 361) {
			SpinBotAngles = 0;
		}

		SpinBotView.y = SpinBotAngles;

		if (*SpinBotBO3)
		{
			cmdBO3->angles[1] = AngleToShort(SpinBotView.y);
		}

		if (*nospreadBO3)
		{
			compensateSpreadBO3(cmdBO3);
		}
	}

	return CL_WritePacketHookStubBO3(localClientNumber);
}

Font_sBO3 *registerFontBO3(const char *fontname) {
	return DB_FindXAssetHeaderBO3(fontBO3, fontname, 0, -1).font;
}
void *registerMaterialBO3(const char *materialname) {
	return DB_FindXAssetHeaderBO3(materialBO3, materialname, 0, -1).data;
}

Font_sBO3 *smallFontBO3, *smallDevFontBO3;
void *whiteMaterialBO3;
short tagsBO3[20] = { 0 }; // for bone esp

void registerAssetsBO3() {
	if (!smallFontBO3)
		smallFontBO3 = registerFontBO3("fonts/smallFont");

	if (!smallDevFontBO3)
		smallDevFontBO3 = registerFontBO3("fonts/smallDevFont");

	if (!whiteMaterialBO3)
		whiteMaterialBO3 = registerMaterialBO3("white");
}

float getDistanceWorldToScreenBO3(Vector3 &p1, Vector3 &p2) {
	Vector2 xy1, xy2;
	if (worldToScreenBO3(p1, xy1) && worldToScreenBO3(p2, xy2)) {
		return xy1.distance(xy2);
	}
}
float getEntityWidthScreenBO3(centity_sBO3 *entityBO3) {
	Vector3 p1 = entityBO3->origin, p2 = entityBO3->origin;
	p2.z += 35.0f;
	return getDistanceWorldToScreenBO3(p1, p2);
}

void BO3_DrawText(const char *text, float x, float y, Font_sBO3 *font, Vector4 &color) {
	AddBaseDrawTextCmdBO3(text, 0x7FFFFFFF, font, x, y, 1.0f, 1.0f, color, 0);
}
void BO3_DrawText(const char *text, float x, float y, float xScale, float yScale, Font_sBO3 *font, Vector4 &color) {
	AddBaseDrawTextCmdBO3(text, 0x7FFFFFFF, font, x, y, xScale, yScale, color, 0);
}
void drawMaterialBO3(float x, float y, float width, float height, float angle, Vector4 &color) {
	CG_DrawRotatedPicPhysicalBO3(0x83088EC0, x, y, width, height, angle, color, whiteMaterialBO3, 0); //TU8
}
void drawLineBO3(float x1, float y1, float x2, float y2, float width, Vector4 &color) {
	float x, y, angle, l1, l2, h1;
	h1 = y2 - y1;
	l1 = x2 - x1;
	l2 = sqrt(l1 * l1 + h1 * h1);
	x = x1 + ((l1 - l2) / 2);
	y = y1 + (h1 / 2);
	angle = (float)atan(h1 / l1) * (180 / 3.14159265358979323846);
	drawMaterialBO3(x, y, l2, width, angle, color);
}
void drawRectangleBO3(float x, float y, float width, float height, float lineWidth, Vector4 &color) {
	drawMaterialBO3(x, y, width, lineWidth, 0.0f, color);
	drawMaterialBO3(x + width, y, lineWidth, height, 0.0f, color);
	drawMaterialBO3(x, y + height - lineWidth, width, lineWidth, 0.0f, color);
	drawMaterialBO3(x, y, lineWidth, height, 0.0f, color);
}
void drawBoxLineBO3(Vector3 &center, float x1, float y1, float z1, float x2, float y2, float z2, Vector4& color) {
	Vector2 xy1, xy2;
	if (worldToScreenBO3(Vector3(center.x + x1, center.y + y1, center.z + z1), xy1) &&
		worldToScreenBO3(Vector3(center.x + x2, center.y + y2, center.z + z2), xy2)) {
		drawLineBO3(xy1.x, xy1.y, xy2.x, xy2.y, 2.5f, color);
	}
}
void draw3DBoxBO3(centity_sBO3 *entity, Vector4 &color) {
	float w = 15.0f, h = getEntityHeightBO3(entity);

	drawBoxLineBO3(entity->origin, -w, -w, 0, w, -w, 0, color);
	drawBoxLineBO3(entity->origin, -w, -w, 0, -w, w, 0, color);
	drawBoxLineBO3(entity->origin, w, w, 0, w, -w, 0, color);
	drawBoxLineBO3(entity->origin, w, w, 0, -w, w, 0, color);

	drawBoxLineBO3(entity->origin, -w, -w, 0, -w, -w, h, color);
	drawBoxLineBO3(entity->origin, -w, w, 0, -w, w, h, color);
	drawBoxLineBO3(entity->origin, w, -w, 0, w, -w, h, color);
	drawBoxLineBO3(entity->origin, w, w, 0, w, w, h, color);

	drawBoxLineBO3(entity->origin, -w, -w, h, w, -w, h, color);
	drawBoxLineBO3(entity->origin, -w, -w, h, -w, w, h, color);
	drawBoxLineBO3(entity->origin, w, w, h, w, -w, h, color);
	drawBoxLineBO3(entity->origin, w, w, h, -w, w, h, color);
}

void drawPyramidBO3(centity_sBO3 *entity, Vector4 &color) {
	float w = 15.0f, h = getEntityHeightBO3(entity) + 10;

	drawBoxLineBO3(entity->origin, -w, -w, 0, w, -w, 0, color);
	drawBoxLineBO3(entity->origin, -w, -w, 0, -w, w, 0, color);
	drawBoxLineBO3(entity->origin, w, w, 0, w, -w, 0, color);
	drawBoxLineBO3(entity->origin, w, w, 0, -w, w, 0, color);

	drawBoxLineBO3(entity->origin, -w, -w, 0, 0, 0, h, color);
	drawBoxLineBO3(entity->origin, -w, w, 0, 0, 0, h, color);
	drawBoxLineBO3(entity->origin, w, -w, 0, 0, 0, h, color);
	drawBoxLineBO3(entity->origin, w, w, 0, 0, 0, h, color);
}

void draw2DBoxBO3(centity_sBO3 *entity, Vector4 &color) {
	float w = 15.0f, h = getEntityHeightBO3(entity);

	drawBoxLineBO3(entity->origin, -w, 0, 0, w, 0, 0, color);
	drawBoxLineBO3(entity->origin, -w, 0, 0, -w, 0, h, color);
	drawBoxLineBO3(entity->origin, w, 0, 0, w, 0, h, color);
	drawBoxLineBO3(entity->origin, -w, 0, h, w, 0, h, color);
}

void draw2DFilledBoxBO3(centity_sBO3 *entity, Vector4 &color, Vector4 &color2) {
	float w = 15.0f, h = getEntityHeightBO3(entity);
	Vector2 xy1, xy2;
	if (worldToScreenBO3(Vector3(entity->origin.x - w, entity->origin.y + 0, entity->origin.z + 0), xy1) &&
		worldToScreenBO3(Vector3(entity->origin.x + w, entity->origin.y + 0, entity->origin.z + h), xy2)) {
		drawLineBO3(xy1.x, xy1.y, xy2.x, xy2.y, 2.5f, color2);
		drawBoxLineBO3(entity->origin, -w, 0, 0, w, 0, 0, color);
		drawBoxLineBO3(entity->origin, -w, 0, 0, -w, 0, h, color);
		drawBoxLineBO3(entity->origin, w, 0, 0, w, 0, h, color);
		drawBoxLineBO3(entity->origin, -w, 0, h, w, 0, h, color);
	}
}


void drawHealthBO3(centity_sBO3 *entity) {
	Vector2 screen;
	if (worldToScreenBO3(entity->origin, screen)) {
		float w = getEntityWidthScreenBO3(entity), health = ((float)cgBO3->ci[entity->clientNumber].health / 100.0f);
		float cw = w / 2.0f, wh = w / 8.0f;
		drawMaterialBO3(screen.x - cw, screen.y, w, wh, 0, greenBO3);
		drawMaterialBO3(screen.x - cw, screen.y, w * health, wh, 0, greenBO3);
		drawRectangleBO3((screen.x - cw), screen.y, w + 1.0f, wh + 1.0f, 0.5f, blackBO3);
	}
}
void drawBoneLineBO3(centity_sBO3 *entity, short tagname1, short tagname2, Vector4& color) {
	Vector3 world1, world2;
	if (getTagPosBO3(entity, tagname1, world1) && getTagPosBO3(entity, tagname2, world2)) {
		Vector2 xy1, xy2;
		if (worldToScreenBO3(world1, xy1) && worldToScreenBO3(world2, xy2)) {
			float w = 1.0f; // + cgBO3->ps.weaponPosFraction; // for ads
			drawLineBO3(xy1.x, xy1.y, xy2.x, xy2.y, w, color);
		}
	}
}

void drawBonesBO3(centity_sBO3 *entity, Vector4 color) {
	if (!tagsBO3[0]) {
		for (int i = 0; i < 20; i++)
			tagsBO3[i] = registerTagBO3(tagnamesBO3[i]);
	}

	Vector3 tagpos1, tagpos2;

	// top: j_helmet to j_neck
	drawBoneLineBO3(entity, tagsBO3[0], tagsBO3[1], color);
	drawBoneLineBO3(entity, tagsBO3[1], tagsBO3[2], color);

	// left arm: j_neck to j_wrist_le
	drawBoneLineBO3(entity, tagsBO3[2], tagsBO3[3], color);
	drawBoneLineBO3(entity, tagsBO3[3], tagsBO3[5], color);
	drawBoneLineBO3(entity, tagsBO3[5], tagsBO3[7], color);

	// right arm: j_neck to j_wrist_ri
	drawBoneLineBO3(entity, tagsBO3[2], tagsBO3[4], color);
	drawBoneLineBO3(entity, tagsBO3[4], tagsBO3[6], color);
	drawBoneLineBO3(entity, tagsBO3[6], tagsBO3[8], color);

	// center: j_neck to j_spinelower
	drawBoneLineBO3(entity, tagsBO3[2], tagsBO3[10], color);
	drawBoneLineBO3(entity, tagsBO3[10], tagsBO3[11], color);
	drawBoneLineBO3(entity, tagsBO3[11], tagsBO3[12], color);
	drawBoneLineBO3(entity, tagsBO3[12], tagsBO3[13], color);



	// left leg: j_spine4 to j_ankle_le
	drawBoneLineBO3(entity, tagsBO3[13], tagsBO3[14], color);
	drawBoneLineBO3(entity, tagsBO3[14], tagsBO3[16], color);
	drawBoneLineBO3(entity, tagsBO3[16], tagsBO3[18], color);

	// right leg: j_spine4 to j_ankle_ri
	drawBoneLineBO3(entity, tagsBO3[13], tagsBO3[15], color);
	drawBoneLineBO3(entity, tagsBO3[15], tagsBO3[17], color);
	drawBoneLineBO3(entity, tagsBO3[17], tagsBO3[19], color);
}

void ClientDetailsBO3()
{
	registerAssetsBO3();

	if (isInGameBO3())
	{
		if (*TargetDetailsBO3)
		{
			drawMaterialBO3(105.0f, 245.0f, 250.0f, 60.0f, 0, L_blackBO3);
			drawRectangleBO3(105.0f, 245.0f, 250.0f, 60.0f, 2.0f, L_red2BO3);
			BO3_DrawText("Target Details:", 105.0f, 241.0f, smallDevFontBO3, whiteBO3);

			int ClientValid = findClosestClientBO3();
			centity_sBO3 *entity = &centsBO3[ClientValid];

			char* targettext;
			if (DrawTargetDetailsBO3)
			{
				char targetbuffer[3096];
				float d = cgBO3->origin.distance(entity->origin) * 0.0254f;
				sprintf(targetbuffer, "Name: %s\nDistance: %0.2fm", cgBO3->ci[ClientValid].name, d);
				if (targetbuffer != "")
					targettext = targetbuffer;
				else
					targettext = "Target Details Error";
				DrawTargetDetailsBO3 = false;
			}
			else
			{
				targettext = "Name: N/A\nDistance: N/A";
			}
			BO3_DrawText(targettext, 115.0f, 275.0f, smallDevFontBO3, whiteBO3);
		}
	}
}

void BO3_Draw()
{
	int CenterX = 1280 / 2;
	int CenterY = 720 / 2;
	float x = cgBO3->refdef.width, y = cgBO3->refdef.height;
	float cx = x / 2.0f, cy = y / 2.0f;

	registerAssetsBO3();

	if (isInGameBO3())
	{
		if (CrossHairBO3 == PlusCrosshairBO3)
		{
			drawLineBO3(cx, cy - 20.0f, cx, cy + 20.0f, 3.0f, whiteBO3);
			drawLineBO3(cx - 20.0f, cy, cx + 20.0f, cy, 3.0f, whiteBO3);
		}
		else if (CrossHairBO3 == XCrosshairBO3)
		{
			drawLineBO3(625, 345, 638, 358, 2.0f, yellowBO3);
			drawLineBO3(655, 345, 642, 358, 2.0f, yellowBO3);
			drawLineBO3(625, 375, 638, 362, 2.0f, yellowBO3);
			drawLineBO3(655, 375, 642, 362, 2.0f, yellowBO3);
		}

		for (int i = 0; i < cgsBO3->maxClients; i++)
		{
			Vector2 screen, screenh;
			centity_sBO3 *entity = &centsBO3[i];
			if (worldToScreenBO3(entity->origin, screen)) {
				if (i == cgBO3->clientNumber) // client is our own
					continue;

				if (!(entity->alive & 2) || cgBO3->ci[i].health < 1) // alive check
					continue;

				if (cgBO3->ci[i].team == cgBO3->ci[cgBO3->clientNumber].team)
				{
					if (ESPBO3 == ESPFriendlyBO3 || ESPBO3 == ESPBothBO3)
					{
						if (*ESPNamesBO3) {
							Vector3 headpos;
							getHeadPosBO3(entity, headpos);
							if (worldToScreenBO3(headpos, screenh)) {
								float d = cgBO3->origin.distance(entity->origin) * 0.0254f;
								const char *text = vaBO3("%s [%0.2fm]", cgBO3->ci[i].name, d);
								float w = UI_TextWidthBO3(text, 0x7FFFFFFF, smallDevFontBO3, 0.75f);
								BO3_DrawText(text, screenh.x - (w / 4.0f), screenh.y, 0.75f, 0.75f, smallDevFontBO3, whiteBO3); // name
							}
						}

						if (*ESPBonesBO3)
							drawBonesBO3(entity, whiteBO3);

						if (CurrentBO3ESP == BO3_TWO_D)
						{
							//BO2_DrawPlayerBox(BO2_Entities[i], mTag, fWidth, change_color);
						}
						else if (CurrentBO3ESP == BO3_THREE_D)
						{
							draw3DBoxBO3(entity, greenBO3);
						}
						else if (CurrentBO3ESP == BO3_PYRAMID)
						{
							drawPyramidBO3(entity, greenBO3);
						}

						if (*ESPHealthBO3)
							drawHealthBO3(entity);
					}

					if (SnapLineTeamBO3 == SnapLineFriendlyBO3 || SnapLineTeamBO3 == SnapLineTeamBothBO3)
					{
						if (SnapLinePosBO3 == SnapLineMiddleBO3)
						{
							drawLineBO3(CenterX, CenterY, screen.x, screen.y, 2.0f, greenBO3);
						}
						else if (SnapLinePosBO3 == SnapLineBottomBO3)
						{
							drawLineBO3(CenterX, 700.0f, screen.x, screen.y, 2.0f, greenBO3);
						}
						else if (SnapLinePosBO3 == SnapLineTopBO3)
						{
							drawLineBO3(CenterX, 30.0f, screen.x, screen.y, 2.0f, greenBO3);
						}
					}
				}
				else
				{
					Vector4 color = canKillEntityBO3(entity) ? blueBO3 : redBO3;

					if (ESPBO3 == ESPEnemyBO3 || ESPBO3 == ESPBothBO3)
					{
						if (*ESPNamesBO3) {
							Vector3 headpos;
							getHeadPosBO3(entity, headpos);
							if (worldToScreenBO3(headpos, screenh)) {
								float d = cgBO3->origin.distance(entity->origin) * 0.0254f;
								const char *text = vaBO3("%s [%0.2fm]", cgBO3->ci[i].name, d);
								float w = UI_TextWidthBO3(text, 0x7FFFFFFF, smallDevFontBO3, 0.75f);
								BO3_DrawText(text, screenh.x - (w / 4.0f), screenh.y, 0.75f, 0.75f, smallDevFontBO3, whiteBO3); // name
							}
						}

						if (*ESPBonesBO3)
							drawBonesBO3(entity, whiteBO3);

						if (CurrentBO3ESP == BO3_TWO_D)
						{
							//BO2_DrawPlayerBox(BO2_Entities[i], mTag, fWidth, change_color);
						}
						else if (CurrentBO3ESP == BO3_THREE_D)
						{
							draw3DBoxBO3(entity, color);
						}
						else if (CurrentBO3ESP == BO3_PYRAMID)
						{
							drawPyramidBO3(entity, color);
						}

						if (*ESPHealthBO3)
							drawHealthBO3(entity);
					}

					if (SnapLineTeamBO3 == SnapLineEnemyBO3 || SnapLineTeamBO3 == SnapLineTeamBothBO3)
					{
						if (SnapLinePosBO3 == SnapLineMiddleBO3)
						{
							drawLineBO3(CenterX, CenterY, screen.x, screen.y, 2.0f, color);
						}
						else if (SnapLinePosBO3 == SnapLineBottomBO3)
						{
							drawLineBO3(CenterX, 700.0f, screen.x, screen.y, 2.0f, color);
						}
						else if (SnapLinePosBO3 == SnapLineTopBO3)
						{
							drawLineBO3(CenterX, 30.0f, screen.x, screen.y, 2.0f, color);
						}
					}

					if (*VisibleWarningBO3)
					{
						if (isEntityVisibleBO3(&centsBO3[i]))
						{
							char msg[250];
							sprintf(msg, "*Enemy Visible*");
							BO3_DrawText(msg, CenterX - 60, CenterY + 150, smallDevFontBO3, redBO3);
						}
					}

					if (*ProximityWarningBO3)
					{
						float d = cgBO3->origin.distance(entity->origin) * 0.0254f;
						if (BO3ProximityWarning(d))
						{
							char msg[250];
							sprintf(msg, "Proximity Warning!");
							BO3_DrawText(msg, CenterX - strlen(msg) * 2.5, CenterY + 170, smallDevFontBO3, redBO3);
						}
					}
				}
			}
		}
	}
}

XINPUT_STATE XInputStateBO3;
short currentButtonBO3, previousButtonBO3;
#define buttonHitBO3(button) ((currentButtonBO3 & ~previousButtonBO3) & button)
void updateInputBO3() {
	XInputGetState(0, &XInputStateBO3);
	previousButtonBO3 = currentButtonBO3;
	currentButtonBO3 = ~XInputStateBO3.Gamepad.wButtons & 0xFBFF;

	if (buttonHitBO3(XINPUT_GAMEPAD_DPAD_LEFT)) {
		openBO3 = !openBO3;
	}

	if (openBO3) {
		if (currentBO3 == BO3_AIMBOT || currentBO3 == BO3_ESP) {
			if (buttonHitBO3(XINPUT_GAMEPAD_B)) {
				currentBO3 = BO3_MAIN;
			}
		}

		if (buttonHitBO3(XINPUT_GAMEPAD_DPAD_UP)) {
			if (currentBO3 == BO3_MAIN)
			{
				scrollBO3--;
				if (scrollBO3 == -1) {
					scrollBO3 = maxoptionsBO3 - 1;
				}
			}
			else
			{
				if (currentBO3 == BO3_AIMBOT)
				{
					AimscrollBO3--;
					if (AimscrollBO3 == -1) {
						AimscrollBO3 = AimmaxoptionsBO3 - 1;
					}
				}
				else
				{
					if (currentBO3 == BO3_ESP)
					{
						ESPscrollBO3--;
						if (ESPscrollBO3 == -1) {
							ESPscrollBO3 = ESPmaxoptionsBO3 - 1;
						}
					}
				}
			}
		}

		if (buttonHitBO3(XINPUT_GAMEPAD_DPAD_DOWN)) {
			if (currentBO3 == BO3_MAIN)
			{
				scrollBO3++;
				if (scrollBO3 == maxoptionsBO3) {
					scrollBO3 = 0;
				}
			}
			else
			{
				if (currentBO3 == BO3_AIMBOT)
				{
					AimscrollBO3++;
					if (AimscrollBO3 == AimmaxoptionsBO3) {
						AimscrollBO3 = 0;
					}
				}
				else
				{
					if (currentBO3 == BO3_ESP)
					{
						ESPscrollBO3++;
						if (ESPscrollBO3 == ESPmaxoptionsBO3) {
							ESPscrollBO3 = 0;
						}
					}
				}
			}
		}

		if (buttonHitBO3(XINPUT_GAMEPAD_X)) {
			if (currentBO3 == BO3_MAIN)
			{
				if (scrollBO3 == 0)
				{
					currentBO3 = BO3_AIMBOT;
				}
				else
				{
					if (scrollBO3 == 1)
					{
						currentBO3 = BO3_ESP;
					}
					else
					{
						if (scrollBO3 == 5)
						{
							switch (CrossHairBO3) {
							case 0:
								CrossHairBO3 = XCrosshairBO3;
								break;
							case 1:
								CrossHairBO3 = CrosshairOffBO3;
								break;
							case 2:
								CrossHairBO3 = PlusCrosshairBO3;
								break;
							default:
								CrossHairBO3 = CrosshairOffBO3;
								break;
							}
						}
						else
						{
							boptionsBO3[scrollBO3] = !boptionsBO3[scrollBO3];
						}
					}
				}
			}
			else
			{
				if (currentBO3 == BO3_AIMBOT)
				{
					if (AimscrollBO3 == 0) {
						switch (CurrentBO3Aimbot) {
						case 0:
							CurrentBO3Aimbot = BO3_ONSCREEN;
							break;
						case 1:
							CurrentBO3Aimbot = BO3_CROSSHAIR;
							break;
						case 2:
							CurrentBO3Aimbot = BO3_SILANT_AIM;
							break;
						case 3:
							CurrentBO3Aimbot = BO3_FAVOR_VISIBLE;
							break;
						case 4:
							CurrentBO3Aimbot = BO3_AIMBOT_OFF;
							break;
						case 5:
							CurrentBO3Aimbot = BO3_NEAREST;
							break;
						default:
							CurrentBO3Aimbot = BO3_AIMBOT_OFF;
							break;
						}
					}
					else {
						AimboptionsBO3[AimscrollBO3] = !AimboptionsBO3[AimscrollBO3];
					}
				}
				else
				{
					if (currentBO3 == BO3_ESP)
					{
						if (ESPscrollBO3 == 0) {
							switch (CurrentBO3ESP) {
							case 0:
								CurrentBO3ESP = BO3_THREE_D;
								break;
							case 1:
								CurrentBO3ESP = BO3_PYRAMID;
								break;
							case 2:
								CurrentBO3ESP = BO3_ESP_OFF;
								break;
							case 3:
								CurrentBO3ESP = BO3_TWO_D;
								break;
							default:
								CurrentBO3ESP = BO3_ESP_OFF;
								break;
							}
						}
						else if (ESPscrollBO3 == 4) {
							switch (ESPBO3) {
							case 0:
								ESPBO3 = ESPFriendlyBO3;
								break;
							case 1:
								ESPBO3 = ESPBothBO3;
								break;
							case 2:
								ESPBO3 = ESPOffBO3;
								break;
							case 3:
								ESPBO3 = ESPEnemyBO3;
								break;
							default:
								ESPBO3 = ESPOffBO3;
								break;
							}
						}
						else if (ESPscrollBO3 == 5) {
							switch (SnapLinePosBO3) {
							case 0:
								SnapLinePosBO3 = SnapLineBottomBO3;
								break;
							case 1:
								SnapLinePosBO3 = SnapLineTopBO3;
								break;
							case 2:
								SnapLinePosBO3 = SnapLinesOffBO3;
								break;
							case 3:
								SnapLinePosBO3 = SnapLineMiddleBO3;
								break;
							default:
								SnapLinePosBO3 = SnapLinesOffBO3;
								break;
							}
						}
						else if (ESPscrollBO3 == 6) {
							switch (SnapLineTeamBO3) {
							case 0:
								SnapLineTeamBO3 = SnapLineFriendlyBO3;
								break;
							case 1:
								SnapLineTeamBO3 = SnapLineTeamBothBO3;
								break;
							case 2:
								SnapLineTeamBO3 = SnapLineTeamOffBO3;
								break;
							case 3:
								SnapLineTeamBO3 = SnapLineEnemyBO3;
								break;
							default:
								SnapLineTeamBO3 = SnapLineTeamOffBO3;
								break;
							}
						}
						else {
							ESPboptionsBO3[ESPscrollBO3] = !ESPboptionsBO3[ESPscrollBO3];
						}
					}
				}
			}
		}
	}
}

void updateOptionsBO3()
{
	//All TU7/8
	/*if (*redboxes)
	{
		*(int *)0x82610920 = 0x60000000;//Red Box 1
		*(int *)0x82610948 = 0x60000000;//Red Box 2
	}
	else
	{
		*(int *)0x82610920 = 0x418200DC;//Red Box 1
		*(int *)0x82610948 = 0x418200B4;//Red Box 2
	}*/
	if (*norecoilBO3)
	{
		*(int *)0x82279CB8 = 0x60000000; // nop //TU6
	}
	else
	{
		*(int *)0x82279CB8 = 0x386BD480; // bl BG_WeaponFireRecoil
	}
	if (*advanceduavBO3)
	{
		*(int *)0x8228BC78 = 0x60000000; // nop
	}
	else
	{
		*(int *)0x8228BC78 = 0x817C9338; // beq
	}
	if (*noswayBO3)
	{
		*(int *)0x82201008 = 0x60000000; // nop
		*(int *)0x822017C4 = 0x60000000; // nop
	}
	else
	{
		*(int *)0x82201008 = 0x554B1838; // bl BG_SetWeaponMovementAngles
		*(int *)0x822017C4 = 0x394A0001; // bl BG_CalculateViewMovement_BobAngles
	}
}

void BO3_Menu_Hook()
{
	int CenterX = 1280 / 2;
	int CenterY = 720 / 2;
	float middleBO3 = 950.0f;
	float centerBO3 = 100.0f;
	float bottomBO3 = 700.0f;

	registerAssetsBO3();
	updateInputBO3();
	updateOptionsBO3();

	if (isInGameBO3())
	{
		if (!FirstTimeInGameBO3)
		{
			openBO3 = false;
			currentBO3 = 0;
			CurrentBO3ESP = 3;
			CurrentBO3Aimbot = 5;
			scrollBO3 = 0;
			AimscrollBO3 = 0;
			ESPscrollBO3 = 0;
			SnapLinePosBO3 = 3;
			SnapLineTeamBO3 = 3;
			CrossHairBO3 = 2;
			ESPBO3 = 3;
			CrossHairBO3 = 2;
			FirstTimeInGameBO3 = true;
		}

		if (openBO3)
		{
			if (currentBO3 == BO3_MAIN)
			{
				drawMaterialBO3(middleBO3 - 1, centerBO3, 250.0f, 30.0f + (maxoptionsBO3 * 30.0f), 0, L_blackBO3);
				drawRectangleBO3(middleBO3 - 1, centerBO3, 250.0f, 30.0f + (maxoptionsBO3 * 30.0f), 2.0f, L_red2BO3);
				BO3_DrawText("Synergy Engine", middleBO3 + 20, centerBO3 - 1, smallFontBO3, redBO3);
				BO3_DrawText("Press D-PAD Left To ^1Close^7 Synergy Engine", 30.0f, bottomBO3, smallFontBO3, whiteBO3);

				for (int i = 0; i < maxoptionsBO3; i++) {
					if (i == scrollBO3) {
						BO3_DrawText(optionsBO3[i], middleBO3 + 20, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, L_red2BO3);
					}
					else {
						BO3_DrawText(optionsBO3[i], middleBO3 + 20, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, whiteBO3);
					}
					if (i == 0)
					{
						// fix
					}
					else if (i == 1)
					{
						// fix
					}
					else if (i == 5)
					{
						BO3_DrawText(CrossHairTypeBO3[CrossHairBO3], middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, CrossHairBO3 == CrosshairOffBO3 ? L_red2BO3 : BlueStormzBO3);
					}
					else if (boptionsBO3[i])
					{
						BO3_DrawText("ON", middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, L_green2BO3);
					}
					else
					{
						BO3_DrawText("OFF", middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, L_red2BO3);
					}
				}
			}
			else
			{
				if (currentBO3 == BO3_AIMBOT)
				{
					drawMaterialBO3(middleBO3 - 1, centerBO3, 250.0f, 30.0f + (AimmaxoptionsBO3 * 30.0f), 0, L_blackBO3);
					drawRectangleBO3(middleBO3 - 1, centerBO3, 250.0f, 30.0f + (AimmaxoptionsBO3 * 30.0f), 2.0f, L_red2BO3);
					BO3_DrawText("Aimbot Options", middleBO3 + 20, centerBO3 - 1, smallFontBO3, redBO3);
					BO3_DrawText("Press D-PAD Left To ^1Close^7 Synergy Engine", 30.0f, bottomBO3, smallFontBO3, whiteBO3);

					for (int i = 0; i < AimmaxoptionsBO3; i++) {
						if (i == AimscrollBO3) {
							BO3_DrawText(AimoptionsBO3[i], middleBO3 + 20, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, L_red2BO3);
						}
						else {
							BO3_DrawText(AimoptionsBO3[i], middleBO3 + 20, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, whiteBO3);
						}
						if (i == 0) {
							BO3_DrawText(AimbotTypeBO3[CurrentBO3Aimbot], middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, CurrentBO3Aimbot == BO3_AIMBOT_OFF ? L_red2BO3 : BlueStormzBO3);
						}
						else {
							if (AimboptionsBO3[i])
							{
								BO3_DrawText("ON", middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, L_green2BO3);
							}
							else
							{
								BO3_DrawText("OFF", middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, L_red2BO3);
							}
						}
					}
				}
				else
				{
					if (currentBO3 == BO3_ESP)
					{
						drawMaterialBO3(middleBO3 - 1, centerBO3, 250.0f, 30.0f + (ESPmaxoptionsBO3 * 30.0f), 0, L_blackBO3);
						drawRectangleBO3(middleBO3 - 1, centerBO3, 250.0f, 30.0f + (ESPmaxoptionsBO3 * 30.0f), 2.0f, L_red2BO3);
						BO3_DrawText("ESP Options", middleBO3 + 20, centerBO3 - 1, smallFontBO3, redBO3);
						BO3_DrawText("Press D-PAD Left To ^1Close^7 Synergy Engine", 30.0f, bottomBO3, smallFontBO3, whiteBO3);

						for (int i = 0; i < ESPmaxoptionsBO3; i++) {
							if (i == ESPscrollBO3) {
								BO3_DrawText(ESPoptionsBO3[i], middleBO3 + 20, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, L_red2BO3);
							}
							else {
								BO3_DrawText(ESPoptionsBO3[i], middleBO3 + 20, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, whiteBO3);
							}
							if (i == 0) {
								BO3_DrawText(espTypeBO3[CurrentBO3ESP], middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, CurrentBO3ESP == BO3_ESP_OFF ? L_red2BO3 : BlueStormzBO3);
							}
							else if (i == 4) {
								BO3_DrawText(ESPTeamTypeBO3[ESPBO3], middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, ESPBO3 == ESPOffBO3 ? L_red2BO3 : BlueStormzBO3);
							}
							else if (i == 5) {
								BO3_DrawText(SnapLineTypeBO3[SnapLinePosBO3], middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, SnapLinePosBO3 == SnapLinesOffBO3 ? L_red2BO3 : BlueStormzBO3);
							}
							else if (i == 6) {
								BO3_DrawText(SnapLineTeamTypeBO3[SnapLineTeamBO3], middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, SnapLineTeamBO3 == SnapLineTeamOffBO3 ? L_red2BO3 : BlueStormzBO3);
							}
							else {
								if (ESPboptionsBO3[i])
								{
									BO3_DrawText("ON", middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, L_green2BO3);
								}
								else
								{
									BO3_DrawText("OFF", middleBO3 + 190, centerBO3 + 40.0f + (30.0f * i), smallFontBO3, L_red2BO3);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			BO3_DrawText("Press D-PAD Left To ^2Open^7 Synergy Engine", 30.0f, bottomBO3, smallFontBO3, whiteBO3);//Bottom shit
		}
	}
	else
	{
		openBO3 = false;
	}
}

void BO3_CL_RenderScenehk()
{
	BO3_Menu_Hook();
	BO3_Draw();
	BO3_Aimbot();
	ClientDetailsBO3();
}
}