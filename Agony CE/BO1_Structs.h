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

typedef struct // size 0x34
{
	int time;		// 0x00-0x04
	int buttons;		// 0x04-0x08
	char Buf8[4];		// 0x08-0x0C
	int viewAngles[3];		// 0x0C-0x18
	short weapon;		// 0x18-0x1A
	short offHandIndex;	// 0x1A-0x1C
	char padding[0x2];
	char fDir;	// 0x1C-0x1D
	char rDir;		// 0x1D-0x1E
	char Buf1E[0x14];	// 0x1E-0x34
}Usercmd_t;

typedef struct
{
	char padding00[0xAC];			//0x00
	Vector3 baseAngle;				//0xAC
	char padding01[0x2788];			//0xB4
	Vector3 viewAngle;				//0x2840
	char padding02[0x40010];		//0x2848
	Usercmd_t Usercmd[128];			//0x4285C
	int CurrentCmdNumber;			//0x4425C
}ClientActive_t;

typedef struct
{
	char padding00[0x8];			//0x0
	int Width;						//0x8
	int Height;						//0xC
	char padding01[0x14];			//0x10
	Vector2 Fov;					//0x24
	float Fov_f;					//0x2C
	Vector3 viewOrigin;				//0x30
	char padding02[0x4];			//0x3C
	Vector3 viewAxis[3];			//0x40
}RefDef_t;

typedef struct
{
	unsigned char _0x0000[48];
	Vector3 Origin; //0x0030 
	unsigned char _0x003C[300];
	int Flags; //0x0168 
	unsigned char _0x016C[4];
	unsigned char Valid; //0x0170 
	unsigned char _0x0171[11];
	Vector3 OldOrigin; //0x017C 
	unsigned char _0x0188[0x54];
	int Handle; // 0x01DC
	unsigned char _0x01E0[0x14];
	Vector3 NewOrigin; //0x01F4 
	unsigned char _0x0200[164];
	int WeaponID; //0x02A4 
	unsigned char _0x02A8[0x74]; // 0x2A8
}Centity_t, *pCentity_t;

typedef struct
{
	int Valid;						//0x00
	char padding00[0x4];			//0x04
	int ClientNumber;				//0x08
	char Name[32];					//0x0C
	int Team;						//0x2C
	char padding01[0x34];			//0x30
	int Dead;						//0x64
	char padding02[0x38];			//0x68
	char Model[0x40];			//0xA0
	char HeadModel[0x40];		//0xE0
	char padding03[0x330];			//0x120
	Vector3 viewAngle;		//0x450
	char padding04[0x174];			//0x45C
}clientinfo_t;

typedef struct
{
	unsigned char _0x0000[28];
	unsigned long  InGame; //0x001C 
	unsigned char _0x0020[100];
	unsigned long  Ping; //0x0084 
	unsigned long  iNewTime; //0x0088 
	unsigned long  Servertime; //0x008C 
	unsigned long  iOldTime; //0x0090 
	unsigned char _0x0094[32];
	Vector3 Origin; //0x00B4 
	unsigned char _0x00C0[256];
	unsigned char ClientNumber; //0x01C0 
	unsigned char _0x01C1[19];
	short WeaponID; //0x01D4 
	unsigned char _0x01D6[34];
	float fZoomProgress; //0x01F8 
	unsigned char _0x01FC[88];
	int Health; //0x0254 
	unsigned char _0x0258[4];
	int MaxHealth; //0x025C 
	unsigned char _0x0260[432];
	int iSecondaryAmmo; //0x0410 
	unsigned char _0x0414[4];
	int iPrimaryAmmo; //0x0418 
	unsigned char _0x041C[108];
	int iSecondaryClip; //0x0488 
	unsigned char _0x048C[4];
	int iPrimaryClip; //0x0490 
	unsigned char _0x0494[0x15C]; // 0x0840
	float SpreadMultiplier;// 0x05F0
	unsigned char _0x05F4[0x3EB28];
	Vector3 ViewAngle; // 0x3F11C
	char padding03[0x28D8];			//0x3F128
	RefDef_t RefDef;				//0x41A00
	char padding04[0x1C094];		//0x41A64
	clientinfo_t ClientInfo[18];	//0x5DAF8
	char padding05[0x4ECC];			//0x64398
	float SpreadMultiplier2;			//0x69264
} cgArray_t;


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

struct trace_t
{
	char Buf00[0x10];
	float fraction;
	char Buf04[0x60];
}; // 0x38
   //
#pragma pack(pop)

struct BulletFireParams
{
	int weaponEntIndex;
	int ignoreEntIndex;
	float damageMultiplier;
	int methodOfDeath;
	Vector3 origStart;
	Vector3 start;
	Vector3 end;
	Vector3 dir;
}; // 0x40

struct BulletTraceResults
{
	trace_t trace;
	int* hitEnt; // gentity_s*
	float hitPos[3];
	int ignoreHitEnt;
	int hitSurfaceType;
}; // 0x50

cgArray_t* cgArray_s;
pCentity_t Centity_s;
ClientActive_t* ClientActive;