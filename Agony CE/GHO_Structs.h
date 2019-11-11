#define FLAG_CROUCHED 0x04
#define FLAG_PRONE 0x08

enum entityType_t
{
	ET_GENERAL = 0x0,
	ET_PLAYER = 0x1,
	ET_PLAYER_CORPSE = 0x2,
	ET_ITEM = 0x3,
	ET_MISSLE = 0x4,
	ET_INVISIBLE = 0x5,
	ET_SCRIPTMOVER = 0x6,
	ET_SOUND_BLEND = 0x7,
	ET_FX = 0x8,
	ET_LOOP_FX = 0x9,
	ET_PRIMARY_LIGHT = 0xA,
	ET_TURRET = 0xB,
	ET_HELICOPTER = 0xC,
	ET_PLANE = 0xD,
	ET_VEHICLE = 0xE,
	ET_VEHICLE_COLLMAP = 0xF,
	ET_VEHICLE_CORPSE = 0x10,
	ET_VEHICLE_SPAWNER = 0x11,
	ET_AGENT = 0x12,
	ET_AGENT_CORPSE = 0x13,
	ET_EVENTS = 0x14,
};

typedef struct cgs_t
{
	unsigned char _0x0000[36];
	const char GameType[4]; //0x0024 
	unsigned char _0x0028[28];
	const char HostName[32]; //0x0044 
	unsigned char _0x0064[228];
	unsigned long MaxClients; //0x0148 
	unsigned char _0x014C[4];
	const char MapName[40]; //0x0150 
	unsigned char _0x0178[712];
}cgs_t, *pcgs_t;//Size=0x0440

typedef struct Usercmd_t
{
	int time;
	int buttons;
	int viewAngles[3];
	int weapon;
	int offHand;
	char fDir;
	char rDir;
	char padding[0x1E];
} Usercmd_t;

typedef struct//0xA9210000
{
	unsigned char _0x0000[0x80];
	int ServerTime; //0x0080 
	unsigned char _0x0084[0x18];
	Vector3 Orign; //0x009C 
	unsigned char _0x00A8[0x3C];
	Vector3 baseAngle; //0x00E4 
	unsigned char _0x00F0[0x31E0];
	Vector3 viewAngle; //0x32D0
	Usercmd_t Usercmd[128];
	int CurrentCmdNumber;
	unsigned char _0x32DC[0xAAA4];
	bool ADS;
} ClientActive_t;

#pragma pack(push, 2)
typedef struct//0xBB2948B0
{
	unsigned char _0x0000[2]; //0x0000 
	unsigned char Alive; //0x0002 
	unsigned char _0x0003[17];
	Vector3 Origin; //0x0014 
	unsigned char _0x0020[60];
	int Flags; //0x005C 
	unsigned char _0x0060[12];
	Vector3 NewOrigin; //0x006C 
	unsigned char _0x0078[24];
	Vector3 viewAngle; //0x0090 
	unsigned char _0x009C[44];
	int Type; //0x00C8 
	unsigned char _0x00CC[16];
	Vector3 OldOrigin; //0x00DC 
	unsigned char _0x00E8[24];
	Vector3 OldAngles; //0x0100 
	unsigned char _0x010C[32];
	int PreviousWeaponIndex; //0x012C 
	unsigned char _0x0130[88];
	int WeaponID; //0x0188 
	unsigned char _0x018C[59];
	unsigned char State; //0x01C7 
	unsigned char _0x01C8[0x24];
}Centity_t, *pCentity_t;
#pragma pack(pop)

enum CommandMask
{
	CMD_MASK_FIRE = 0x00000001,
	CMD_MASK_MELEE = 0x00000004,
	CMD_MASK_SPRINT = 0x00002002,
	CMD_MASK_RELOAD = 0x00000020,
	CMD_MASK_AIM = 0x00080800,
	CMD_MASK_JUMP = 0x00000400,
	CMD_MASK_CROUCH = 0x00000200,
	CMD_MASK_PRONE = 0x00000100
};

typedef struct refdef_s
{
	char _0x0000[0x08];
	unsigned long Width; //0x0008
	unsigned long Height; //0x000C 
	Vector2 Fov; //0x0010 
	Vector3 viewOrigin; //0x0018 
	Vector3 viewAxis[3]; //0x0024
	unsigned char _0x0048[12];
	unsigned long Ping; //0x054
} RefDef_t;//Size=0x0080 

typedef struct clientInfo_t // 0xB943C
{
	unsigned long Team; //0x0004 
	char padding01[0xC];
	char Model[0x25];
	char padding02[0x1B];
	char HeadModel[32];
	char padding03[0x52C];
} clientinfo_t;

typedef struct playerName_t//cgArray +  0x368B4
{
	char Name[32]; //0x00
	char padding00[0xD0];
}playerName_t, *pplayerName_t;//Size=0xF0

typedef struct//0xBB397780
{
	unsigned long Servertime; //0x0000 
	unsigned char _0x0004[8];
	unsigned long Stance; //0x000C 
	unsigned char _0x0010[12];
	Vector3 Origin; //0x001C 
	unsigned char _0x0028[340];
	unsigned long ClientNumber; //0x017C 
	unsigned char _0x0180[0x4];
	Vector3 ViewAngle; // 0x184
	unsigned char _0x0190[0x38];
	unsigned long Health; //0x01C8 
	unsigned long cNum;			 //0x017C
	unsigned char _0x01CC[4];
	unsigned long MaxHealth; //0x01D0 
	unsigned char _0x01D4[0x254];
	float SpreadMultiplier;
	char padding01[0x36488];
	playerName_t Names[18];
	char padding02[0x35BA8];
	refdef_s RefDef;
	char padding03[0x4BEA8];
	clientInfo_t ClientInfo[18];
} cgArray_t; //Size=0x01D4


struct BulletFireParams
{
	int MaxEntNum;
	int ignoreEntIndex;
	float damageMultiplier;
	int methodOfDeath;
	int crackCocaine;
	Vector3 origStart;
	Vector3 start;
	Vector3 end;
	Vector3 dir;
};

struct trace_t
{
	float fraction;
	char Buf04[0x60];
};

ClientActive_t* ClientActive;
pCentity_t Centity_s;
cgArray_t* cgArray_s;