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

typedef struct
{
	int Team;					 //0x00
	char padding00[0x48];		 //0x04
	char Name[0x20];			//0x4C
	char padding01[0xC8];		 //0x6C
								 //Size: 0x134
}ClientInfo_t, *pClientInfo_t;

typedef struct
{
	int Team;					 //0x00
	char padding00[0x14];		 //0x04
	char ModelName[0x20];		 //0x18
	char padding02[0x20];		 //0x38
	char HeadModel[0x20];		 //0x58
	char padding03[0xBBC];
}TeamInfo_t, *pTeamInfo;

typedef struct
{
	short Width;				 //0x0
	short Height;				 //0x2
	char padding01[0x8];		 //0x4
	Vector2 Fov;				 //0xC
	Vector3 viewOrigin;			 //0x14
	Vector3 viewAxis[3];		 //0x20
	D3DXVECTOR3 EyePos;		     //0x14
								 //Size 0x44
}RefDef_s;

typedef struct
{
	char ClientNumber;				//0x00
	char padding00[0x4B];			//0x01
	int Servertime;					//0x4C
	char padding01[0xC];			//0x50
	int Stance;						//0x5C
	char padding02[0x18];			//0x60
	Vector3 Origin;					//0x78
	char padding03[0x12C];			//0x84
	Vector3 ViewAngle;				//0x1B0
	char padding04[0x24];			//0x1BC
	int Health;						//0x1E0
	char padding07[0x35080];		//0x1E4
	ClientInfo_t ClientInfo[12];	//0x35264
	char padding05[0x16F0];			//0x360D4
	RefDef_s RefDef;				//0x377C4
	char padding06[0x68D9C];		//0x37808
	TeamInfo_t TeamInfo[12];		//0xA05A4

}cgArray_t;

typedef struct// size 0x40
{
	int time;		// 0x00-0x04
	int buttons;		// 0x04-0x08
	int viewAngles[3];		// 0x08-0x14
	int weapon;			// 0x14-0x18
	int offHandIndex;	// 0x18-0x1C
	char fDir;	// 0x1C-0x1D
	char rDir;		// 0x1D-0x1E
	char Buf[0x22];		// 0x1E-0x40
}Usercmd_t;

typedef struct
{
	char padding00[0x110];		 //0x00
	Vector3 baseAngle;			 //0x110
	char padding01[0x344C];		 //0x11C
	Vector3 viewAngle;			 //0x3568
	Usercmd_t Usercmd[128];		 //0x3574
	int CurrentCmdNumber;		 //0x5574
}ClientActive_t;

typedef struct
{
	char padding00[0x2];		 //0x0
	bool Alive;					 //0x2
	char padding01[0x11];		 //0x3
	Vector3 Origin;				 //0x14
	char padding02[0x4C];		 //0x20
	int Flags;					 //0x6C
	char padding03[0xC];		 //0x70
	Vector3 NewOrigin;			 //0x7C
	char _0x0088[0x18];
	Vector3 viewAngle;			 //0xA0
	char padding13[0x2C];		 //0xAC
	short Handle;				 //0xD8
	char padding04[0xA];		 //0xDA
	char Type;					 //0xE4
	char padding05[0x0F];		 //0xE5
	bool isIAlive;				 //0xF4
	char padding06[0x2F];		 //0xF5
	int WeaponID;				 //0x124
	char padding07[0x18];		 //0x128
	Vector3 OldOrigin;			 //0x140
	char _0x014C[0xC0];
								 //size 0x20C
}Centity_t, *pCentity_t;

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
	float Fraction;
	char Buf04[0x60];
};

cgArray_t* cgArray_s;
ClientActive_t* ClientActive;
pCentity_t Centity_s;