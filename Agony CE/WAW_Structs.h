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
	int Command;
}playerState_t;

typedef struct
{
	int Valid;						//0x00
	char padding00[0x4];			//0x04
	int ClientNumber;				//0x08
	char Name[32];					//0x0C
	int Team;						//0x2C
	char padding01[0x30];			//0x30
	char Model[32];					//0x60
	char padding02[0x20];			//0x80
	char HeadModel[32];				//0xA0
	char padding03[0x20];			//0xC0
	char weaponName[32];			//0xE0
	char padding[0x308];			//0x100
	Vector3 viewAngle;				//0x408
	char padding04[0x148];				//0x414
									//0x55C
}Clientinfo;

typedef struct
{
	char padding00[0x8];			//0x0
	int Width;						//0x8
	int Height;						//0xC
	char padding01[0x10];			//0x10
	Vector2 Fov;					//0x20
	char padding02[0x4];			//0x28
	Vector3 viewOrigin;				//0x2C
	char padding03[0x4];			//0x38
	Vector3 viewAxis[3];			//0x3C
}RefDef_t;

typedef struct
{
	int ClientNumber;    //0x00
	char _0x0004[0x18];
	int NewServerTime; //0x001C
	char _0x0020[0xC];
	int Ping; //0x2C
	int Servertime; // 0x0030
	int OlServerTime; //0x0034
	char _0x0038[0x20];
	Vector3 Origin;     //0x58
	char padding02[0xD8];			//0x64
	int WeaponID;					//0x13C 
	char padding03[0x5C];			//0x140 
	int Health;					//0x19C
	char padding04[0x4FEB4];		//0x1A0
	playerState_t playerState;		//0x50054
	char padding05[0x120];			//0x50058
	Vector3 ViewAngle;		//0x50178
	char padding06[0x3B7C];			//0x50180
	RefDef_t RefDef;				//0x53D00
	char padding07[0x8F9D4];		//0x53D60
	Clientinfo ClientInfo[18];		//0xE3734
	char padding08[0x37B0];			//0xE97AC
	float SpreadMultiplier;			//0xECF5C 
}cgArray_t;

typedef struct
{
	int Valid;						//0x00
	char padding00[0x24];			//0x04
	Vector3 Origin;					//0x28
	char padding01[0x9C];			//0x34
	int Flags;      //0xD0
	char padding02[0xC];			//0xD4
	Vector3 OldOrigin;				//0x00E0
	char padding06[0x70];			//0xEC
	int Handle;						//0x15C
	char padding03[0x14];   //0x160
	Vector3 NewOrigin; //0x174
	char padding05[0xC4];   //0x180
	int WeaponID; //0x244
	char _0x0248[0x64];
	int isAlive;     //0x2AC
}Centity_t, *pCentity_t;

typedef struct
{
	int time;					//0x00
	int buttons;					//0x04
	int viewAngles[3];				//0x08
	short WeaponID;					//0x14
	char fDir;						//0x16
	char rDir;						//0x17
	char padding[0x14];				//0x18
}Usercmd_t;

typedef struct
{
	char padding00[0xA4];			//0x00
	Vector3 baseAngle;				//0xA4
	char padding02[0x269D0];		//0xAC
	Vector3 viewAngle;				//0x26A80
	char padding03[0x40014];		//0x26A88
	Usercmd_t Usercmd[128];			//0x66AA0
	int CurrentCmdNumber;
}ClientActive_t;

#pragma pack(push, 1)
struct trace_t
{
	Vector3 normal;
	char unk1[0x04];
	float fraction;
	char unk2[0x08];
	int hitType;
	short hitId;
	short modelIndex;
	short partName;
	short partGroup;
	char unk4[0x10];
}; // 0x38
#pragma pack(pop)

struct UiContext
{
	char _0x0000[0x1C];
	int screenWidth;//0x1C
	int screenHeight;//0x20
	char _0x0024[0x4];
	float FPS;//0x28
};

cgArray_t* cgArray_s;
pCentity_t Centity_s;
ClientActive_t* ClientActive;
UiContext uicontext;