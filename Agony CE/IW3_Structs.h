#define FLAG_DEAD 0x02
#define FLAG_CROUCHED 0x04
#define FLAG_PRONE 0x08

typedef enum {
	ET_GENERAL,
	ET_PLAYER,
	ET_CORPSE,
	ET_ITEM,
	ET_MISSLE,
	ET_INVISIBLE_ENTITY,
	ET_SCRIPTMOVER,
	ET_SOUND_BLEND,
	ET_FX,
	ET_LOOP_FX,
	ET_PRIMARY_LIGHT,
	ET_TURRET,
	ET_HELICOPTER,
	ET_PLANE,
	ET_VEHICLE,
	ET_VEHICLE_COLLMAP,
	ET_VEHICLE_CORPSE,
	ET_VEHICLE_SPAWNER
} entityType_t;

typedef struct
{
	/* 0000 */ int X;
	/* 0004 */ int Y;
	/* 0008 */ int Width;
	/* 000C */ int Height;
	/* 0010 */ Vector2 Fov;
	/* 0018 */ Vector3 viewOrigin;
	/* 0024 */ Vector3 viewAxis[3];
	/* 0048 */
} RefDef_s;

typedef struct
{
	/* 0000 */ int infoValid;
	/* 0004 */ int nextValid;
	/* 0008 */ int clientNum;
	/* 000C */ char Name[32];
	/* 002C */ int Team;
	/* 0030 */ char _0x0030[0x24];
	/* 0054 */ char Model[64];
	/* 0094 */ char HeadModel[64];
	/* 00D4 */ char WeaponModel[64];
	/* 0114 */ char _0x0114[0x2E8];
	/* 03FC */ Vector3 viewAngle;
	/* 0408 */ char _0x0408[0x68];
	/* 0470 */ int State;
	/* 0474 */ char _0x0474[0x70];
	/* 04E4 */
} clientInfo_t;

typedef struct
{
	int Servertime;
} playerState_t;

typedef struct
{
	/* 0000 */ int ClientNumber;
	/* 0004 */ char _0x0004[0x198];
	/* 019C */ int Health;
	/* 01A0 */ char _0x0184[0x445A4];
	/* 44744 */ playerState_t playerState;
	/* 44748 */ char _0x44748[0x628];
	/* 44D70 */ float SpreadMultiplier;
	/* 44D74 */ char _0x44D74[0x2A34];
	/* 477A8 */ Vector3 ViewAngle;
	/* 477B4 */ char _0x477B4[0x114];
	/* 478C8 */ RefDef_s RefDef;
	/* 47910 */ char _0x47910[0xA1648];
	/* E8F58 */ clientInfo_t ClientInfo[18];
} cgArray_t, *pcgArray_t;

typedef struct
{
	/* 0000 */ int ClientIndex;
	/* 0004 */ int Team;
	/* 0008 */ int ModelIndex;
	/* 000C */ int attachModelIndex[6];
	/* 0024 */ int attachTagIndex[6];
	/* 003C */ char Name[32];
	/* 005C */ float maxSprintTimeMultiplier;
	/* 0060 */ int rank;
	/* 0064 */ int perks;
	/* 0068 */ int voiceConnectivityBits;
	/* 006C */ int clanIndex;
	/* 0070 */ char clanAbbrev[8];
	/* 0078 */ int attachedVehEntNum;
	/* 007C */ int attachedVehSlotIndex;
	/* 0080 */
} clientState_t;

typedef struct
{
	/* 0000 */ int time;
	/* 0004 */ int buttons;
	/* 0008 */ int viewAngles[3];
	/* 0014 */ char weapon;
	/* 0015 */ char offHand;
	/* 0016 */ char fDir;
	/* 0017 */ char rDir;
	/* 0018 */ char _0x0018[0x08];
	/* 0020 */
} Usercmd_t;

typedef struct
{
	/* 0000 */ char _0x0000[0x40];
	/* 0040 */ Vector3 Origin;
	/* 004C */ char _0x004C[0x3C];
	/* 0088 */ Vector3 baseAngle;
	/* 0094 */ char _0x0094[0x2549C];
	/* 25530 */ Vector3 viewAngle;
	/* 2553C */ char _0x2553C[0x40014];
	/* 65550 */ Usercmd_t Usercmd[128];
	/* 66550 */ int CurrentCmdNumber;
} ClientActive_t, *pClientActive_t;

typedef struct
{
	/* 0000 */ char _0x0000[0x02];
	/* 0002 */ char Alive;
	/* 0003 */ char _0x0003[0x19];
	/* 001C */ Vector3 Origin;
	/* 0028 */ char _0x0028[0x40];
	/* 0068 */ Vector3 NewOrigin;
	/* 0074 */ char _0x0074[0x4C];
	/* 00C0 */ int Handle;
	/* 00C4 */ int Type;
	/* 00C8 */ int Flags;
	/* 00CC */ char _0x00CC[0x0C];
	/* 00D8 */ Vector3 OldOrigin;
	/* 00E4 */ char _0x00E4[0xA2];
	/* 0184 */ short WeaponID;
	/* 0188 */ char _0x0188[0x2C];
	/* 01B4 */ char State;
	/* 01B5 */ char _0x01B5[0x1B];
	/* 01D0 */
} Centity_t, *pCentity_t;

struct trace_t
{
	float fraction;					//0x0000
	Vector3 normal;					//0x0004
	int surfaceFlags;				//0x0010
	int contents;					//0x0014
	const char *material;			//0x0018
	int hitType;					//0x001C
	unsigned short hitId;			//0x0020
	unsigned short modelIndex;		//0x0022
	unsigned short partName;		//0x0024
	unsigned short partGroup;		//0x0026
	bool allsolid;					//0x0028 allsolid
	bool startsolid;				//0x0029 startsolid
	char _0x002B[0x02];				//0x002B
}; // 0x002C

struct BulletFireParams
{
	int MaxEntNum;					// 0000
	int ignoreEntIndex;				// 0004
	float damageMultiplier;			// 0008
	int methodOfDeath;				// 000C
	Vector3 origStart;				// 0010
	Vector3 start;					// 0001C
	Vector3 end;					// 00028
	Vector3 dir;					// 00034								// 00040
};

typedef struct
{
	/* 0000 */ char _0x0000[0x20];
	/* 0020 */ char gamemode[4];
	/* 0024 */ char _0x0024[0x1C];
	/* 0040 */ char hostname[32];
	/* 0060 */ char _0x0060[0xE8];
	/* 0148 */ char mapname[50];
} Cgs_t, *pCgs_t;

struct UiContext
{
	char _0x0000[0x1C];
	int screenWidth;//0x1C
	int screenHeight;//0x20
	char _0x0024[0x4];
	float FPS;//0x28
};

pcgArray_t cgArray_s;
pCentity_t Centity_s;
pClientActive_t ClientActive;
pCgs_t pCgs;
UiContext uicontext;

void GetStructs() {
	cgArray_s = *(pcgArray_t *)0x823F28A0;
	Centity_s = *(pCentity_t *)0x823F5054;
	ClientActive = *(pClientActive_t *)0x82435AB8;
	pCgs = *(pCgs_t *)0x823F2890;
}

void pgStructs() {
	uicontext = *(UiContext*)0x849F2DF0;
}

// ClientActive = 82435AB8
// cgsArray_s = 823F2890