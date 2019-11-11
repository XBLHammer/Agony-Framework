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

/* dvar->flags */
#define DVAR_ARCHIVE		(1 << 0)	//0x0001
#define DVAR_USERINFO		(1 << 1)	//0x0002
#define DVAR_SERVERINFO		(1 << 2)	//0x0004
#define DVAR_SYSTEMINFO		(1 << 3)	//0x0008
#define DVAR_INIT		(1 << 4)	//0x0010
#define DVAR_LATCH		(1 << 5)	//0x0020
#define DVAR_ROM		(1 << 6)	//0x0040
#define DVAR_CHEAT		(1 << 7)	//0x0080
#define DVAR_DEVELOPER		(1 << 8)	//0x0100
#define DVAR_SAVED		(1 << 9)	//0x0200
#define DVAR_NORESTART		(1 << 10)	//0x0400
#define DVAR_CHANGEABLE_RESET	(1 << 12)	//0x1000
#define DVAR_EXTERNAL		(1 << 14)	//0x4000
#define DVAR_AUTOEXEC		(1 << 15)	//0x8000

enum dvarType_t
{
	DVAR_TYPE_INVALID = 0x0,
	DVAR_TYPE_BOOL = 0x1,
	DVAR_TYPE_FLOAT = 0x2,
	DVAR_TYPE_FLOAT_2 = 0x3,
	DVAR_TYPE_FLOAT_3 = 0x4,
	DVAR_TYPE_FLOAT_4 = 0x5,
	DVAR_TYPE_INT = 0x6,
	DVAR_TYPE_ENUM = 0x7,
	DVAR_TYPE_STRING = 0x8,
	DVAR_TYPE_COLOR = 0x9,
	DVAR_TYPE_INT64 = 0xA,
	DVAR_TYPE_LINEAR_COLOR_RGB = 0xB,
	DVAR_TYPE_COLOR_XYZ = 0xC,
	DVAR_TYPE_COUNT = 0xD,
};

union DvarLimits
{
	struct {
		int stringCount;
		const char **strings;
	} enumeration;

	struct {
		int min;
		int max;
	} integer;

	struct {
		float min;
		float max;
	} value, vector;

	struct {
		INT64 min;
		INT64 max;
	} integer64;
};

union DvarValue
{
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	INT64 integer64;
	INT64 unsignedInt64;
	float value;
	float vectorv[4];
	const char *string;
	char color[4];
};

#pragma pack(push, 4)
struct dvar_t
{
	const char *name;
	const char *description;
	int hash;
	unsigned int flags;
	dvarType_t type;
	bool modified;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarLimits domain;
	dvar_t *hashNext;
	int unknown3;
};
#pragma pack(pop)

typedef struct // size 0x3C
{
	int time;		// 0x00-0x04
	int buttons;		// 0x04-0x08
	int Buf8;			// 0x08-0x0C
	int viewAngles[3];		// 0x0C-0x18
	int weapon;			// 0x18-0x1C
	int offHandIndex;	// 0x1C-0x20
	int Buf20;			// 0x20-0x24
	char fDir;	// 0x24-0x25
	char rDir;		// 0x25-0x26
	char Buf[0x16];		// 0x26-0x3C
}Usercmd_t;

typedef struct
{
	char padding00[0x44];		 //0x00
	bool ADS;					 //0x44
	char padding01[0xC3];		 //0x45
	Vector3 baseAngle;			 //0x108
	char padding02[0x2B75];		 //0x110
	Vector3 viewAngle;			 //0x2C8C
	char padding03[0x40010];	 //0x2C94
	Usercmd_t Usercmd[128];		 //0x42CA8
	int CurrentCmdNumber;		 //0x44AA8
}ClientActive_t;

typedef struct
{
	char padding00[0x8];		 //0x8
	int Width;					 //0x8
	int Height;					 //0xC
	char padding01[0x14];		 //0x10
	Vector3 Fov;				 //0x24
	char padding02[0x4];		 //0x30
	float flFov;					 //0x34
	Vector3 viewOrigin;			 //0x38
	char padding03[0x4];		 //0x44
	Vector3 viewAxis[3];		 //0x48
} RefDef_s;

typedef struct
{
	char padding01[0x2C];		 //0x0
	Vector3 Origin;				 //0x2C
	char padding02[0x11C];		 //0x38
	int Flags;					 //0x154
	char padding938[0x10];		//0x158
	Vector3 NewOrigin;			//0x168
	char _0x0174[0x38];
	int AltType;                   //0x1AC
	int WeaponID;
	int OldWeapon;
	char padding03[0x18];		 //0x1B0
	int ClientNumber;			 //0x1D0
	char padding04[0x14];       //0x1D4
	Vector3 OldOrigin;			//0x1E8
	char _0x1F4[0xB4];
	short Type;				//0x2A8
	char _0x02AA[0xC2];
	char State;					 //0x36C	
	char padding05[0x7];		 //0x36D
								 //size 0x374
}Centity_t, *pCentity_t;

typedef struct
{
	int somethinghax;			 //0x0
	int somethinghax1;			 //0x4
	int null;					 //0x8
	char Name[0x20];		 //0xC
	int Team;					 //0x2C
	char padding01[0x5F];		 //0x30
	bool Dead;					 //0x8F
	char padding04[0x24];		 //0x90
	char CurrentWeaponName[32];  //0xB4
	char paddin05[0x3F0];		 //D4
	Vector3 viewAngle;			 //0x4C4
	char _0x4D0[0xF4];
	int Weapon;					 //0x5C4
	char padding03[0x240];		 //0x5C8
								 //Size: 0x808
} ClientInfo;

typedef struct
{

}playerState_s;

typedef struct
{
	int ClientNumber;			 //0x0
	char padding00[0x1C];		 //0x4
	int Servertime;				 //0x20
	char padding03828[0x168];	 //0x24
	int Stance;					 //0x18C
	char padding01[0x138];		 //0x190
	int Health;					 //0x2C8
	char padding02[0x27D0];		 //0x2CC
	int MaxEntities;			 //0x2A9C
	char padding03[0x45608];	 //0x2AA0
	playerState_s playerState_t; //0x480A8
	char padding04[0x1F4];		 //0x480AC
	Vector3 ViewAngle;			//0x482A0
	char padding05[0x55D4];		 //0x482AC
	RefDef_s RefDef;			 //0x4D880
	char padding06[0x1C1A4];	 //0x4D8EC
	ClientInfo ClientInfo[18];	 //0x69A90
	char padding07[0xE060];		 //0x72B20
	float SpreadMultiplier;        //0x80B80
}cgArray_t;


enum Bit
{
	CMD_MASK_FIRE = (1 << 31),
	AUTO_AIM = (1 << 20),
	RELOAD = (1 << 25),
};

enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0,
	TRACE_HITTYPE_ENTITY = 1,
	TRACE_HITTYPE_DYNENT_MODEL = 2,
	TRACE_HITTYPE_DYNENT_BRUSH = 3,
	TRACE_HITTYPE_DYNENT_UNKNOWN = 4
};

#pragma pack(push, 1)

struct BulletFireParams
{
	int weaponEntIndex;			//0x00
	int ignoreEntIndex;			//0x04
	float damageMultiplier;		//0x08
	int methodOfDeath;			//0x0C
	Vector3 origStart;			//0x10
	Vector3 start;				//0x1C
	Vector3 end;				//0x28
	Vector3 dir;				//
};

typedef struct
{
	float normal[3];//0x00
	char unk0[0x04];//0x0C
	float fraction;//0x10
	int surfaceFlags;//0x14
	int contents;//0x18
	TraceHitType hitType;//0x1C
	short hitId;//0x20
	short modelIndex;//0x22
	short partName;//0x24
	short boneIndex;//0x26
	short partGroup;//0x28
	bool allsolid;//0x2A
	bool startsolid;//0x2B
	bool walkable;//0x2C
	char gayMcSwag[0x13];//0x2D
						 //0x40
}trace_t;

struct BulletTraceResults
{
	trace_t trace;//0x00
	int* hitEnt;//0x40
	float hitPos[3];//0x44
	bool ignoreHitEnt;//0x50
	char unk0[0x03];//0x54
	int hitSurfaceType;//0x57
	char unk1[0x08];//0x5A
					//0x63
};

cgArray_t* cgArray_s;
pCentity_t Centity_s;
ClientActive_t* ClientActive;

