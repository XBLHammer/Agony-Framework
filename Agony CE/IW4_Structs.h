#define FLAG_CROUCHED 0x04
#define FLAG_PRONE 0x08

typedef enum {
	ET_GENERAL,
	ET_PLAYER,
	ET_CORPSE,
	ET_ITEM,
	ET_MISSLE,
	ET_PLAYER_CORPSE,
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

struct GfxCmdHeader
{
	unsigned short id;
	unsigned short byteCount;
};

typedef struct
{
	char *cmds;
	int usedTotal;
	int usedCritical;
	GfxCmdHeader* lastCmd;
}GfxBackEndData;

typedef struct
{
	int time;						// 0x00-0x04
	int buttons;					// 0x04-0x08
	int viewAngles[3];				// 0x08-0x14
	short weapon;					// 0x14-0x16
	short offHandIndex;				// 0x16-0x18
	char Buf[0x02];					// 0x18-0x1A
	char fDir;						// 0x1A-0x1B
	char rDir;						// 0x1B-0x1C
	char Buf2[0x0C];				// 0x1C-0x28
}Usercmd_t;

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

struct BulletTraceResults
{
	trace_t trace;				// 0x0000
	int* hitEnt;				// 0x002C
	Vector3 hitPos;				// 0x0030
	int ignoreHitEnt;			// 0x003C
	int depthSurfaceType;		// 0x0040
	char _padding[0x04];		// 0x0044
}; // 0x48

struct BulletFireParams
{
	int MaxEntNum;					// 0000
	int ignoreEntIndex;				// 0004
	float damageMultiplier;			// 0008
	int methodOfDeath;				// 000C
	Vector3 origStart;				// 0010
	Vector3 start;					// 0001C
	Vector3 end;					// 00028
	Vector3 dir;					// 00034
									// 00040
};

struct usercmd_s // size 0x28
{
	int serverTime;					// 0x00-0x04
	int buttons;					// 0x04-0x08
	int ViewAngles[3];				// 0x08-0x14
	short weapon;					// 0x14-0x16
	short offHandIndex;				// 0x16-0x18
	char Buf[0x02];					// 0x18-0x1A
	char fDir;						// 0x1A-0x1B
	char rDir;						// 0x1B-0x1C
	char Buf2[0x0C];				// 0x1C-0x28
};

typedef struct
{
	bool ADS;						//0x0000
	char padding00[0xDF];			//0x0001
	Vector3 baseAngle;				//0x00E0
	char padding01[0x31B7];			//0x00EC
	char MapName[0x40];				//0x32A3
	char padding02[0x21];			//0x32E3
	int Stance;						//0x3304
	char padding03[0x28];			//0x3308
	Vector3 Origin;					//0x3330
	char padding04[0x1C];			//0x333C
	Vector3 viewAngle;				//0x3358
	Usercmd_t Usercmd[128];			//0x3364
	int CurrentCmdNumber;			//0x4764
}clientactive_t;


typedef struct
{
	char _0x0000[0x2];				//0x0000
	char Alive;						//0x0002
	char _0x0003[0x15];				//0x0003
	Vector3 Origin;					//0x0018
	char _0x0024[0x3C];				//0x0024
	int Flags;						//0x0060
	char _0x0064[0x14];				//0x0064
	Vector3 NewOrigin;				//0x0078
	char _0x0084[0x4C];				//0x0084
	int Handle;						//0x00D0
	int Type;						//0x00D4
	char _0x00D8[0x1C];				//0x00D8
	Vector3 OldOrigin;				//0x00F4
	char _0x0100[0x58];				//0x0100
	int PickupID;					//0x0158
	char _0x015C[0x40];				//0x015C
	short WeaponID;					//0x019C
	char _0x019E[8];				//0x019E
	short OldWeapon;				//0x01A6
	char _0x01B0[0x50];				//0x01A8
}Centity_t, *pCentity_t;			//0x01F8


typedef struct
{
	int X;							//0x00
	int Y;							//0x04
	int Width;						//0x08
	int Height;						//0x0C
	Vector2 Fov;					//0x10
	Vector3 viewOrigin;				//0x18
	Vector3 viewAxis[3];			//0x24
	char _0x0048[0x18];
	float flZoomProgress;//0x60
	//0x64
}refdef_t;

typedef struct
{
	int Valid;						//0x00
	char padding00[0x8];			//0x04
	char Name[32];					//0x0C
	int Team;						//0x2C
	char padding01[0x4];			//0x30
	int Rank;						//0x34
	int Prestige;					//0x38
	char padding02[0xC];			//0x3C
	unsigned int Perk[2];			//0x48
	char padding03[0x4];			//0x4C
	int Score;						//0x54
	char Model[0x40];				//0x58
	char HeadModel[0x40];			//0x98
	char WeaponModel[0x40];			//0xD8
	char WeaponModel2[0x40];		//0x117
	char padding04[0x2C0];			//0x158
	Vector3 viewAngle;				//0x418
	char _0x0424[0x90];				//0x424
	int Attacking;					//0x4B4
	char padding05[0x4];			//0x4B8
	int Zooming;					//0x4BC	
	char padding06[0x58];			//0x4C0
	int Weapon;						//0x518
	char padding07[0x28];			//0x51C

}clientinfo_t;

typedef struct // size 0x34
{
	int width;    //0x00
	int Height;    //0x04
	char padding00[0x10]; //0x08
	char gamemode[0x10]; //0x18
	char padding01[0x10]; //0x28
	char hostName[0x32]; //0x38
	char paddin02[0xDA]; //0x6A
	char mapName[0x32];  //0x144
}cgs;

typedef struct
{
	int Client; //0x0
	int Score; //0x4
	int Ping; //0x8
	int Deaths; //0xC
	int Assists; //0x10
	int team; //0x14
	char _0x0018[0x10];
}score_t;// size 0x28




typedef struct
{
	int Servertime;					//0x00
	char padding00[0x100];			//0x04
	int ClientNumber;				//0x104
	char padding01[0x4];			//0x108
	Vector3 ViewAngle;				//0x10C
	char padding03[0x38];			//0x118
	int Health;						//0x150
	char padding04[0x170];			//0x154
	float SpreadMultiplier;			//0x2C4
	char padding05[0xB0];			//0x2C8
	int MaxEntities;				//0x378
	char padding06[0x6A8AC];		//0x37C
	refdef_t RefDef;				//0x6AC28
	char _0x6AC8C[0x84E4];
	score_t Score[18];				//0x73170
	char _0x73440[0x90];
	int Weapon;						//0x734D0  
	char padding08[0x839AC];		//0x734D4
	clientinfo_t ClientInfo[18];	//0xF6E80
	char padding09[0x10C0];			//0xFCD48
	cgs pCgs;						//0xFDE08
} cgArray_t;

struct UiContext
{
	char _0x0000[0x20];
	int screenWidth;//0x20
	int screenHeight;//0x24
	char _0x0028[0x4];
	float FPS;
};

cgArray_t* cgArray_s;
pCentity_t Centity_s;
clientactive_t* ClientActive;
UiContext uicontext;

score_t* GetScoreForClient(int client)
{
	for (int i = 0; i < 18; i++)
	{
		if (client == cgArray_s->Score[i].Client)
			return &cgArray_s->Score[i];
	}
}