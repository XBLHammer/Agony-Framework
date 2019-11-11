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
	int Valid;
	char _0x0004[0x8];
	char Name[32];
	int Team;
	char _0x0030[0x4];
	int Rank;
	int Prestige;
	char _0x003C[0x24];
	char Model[0x40];
	char HeadModel[0x40];
	char _0x00E0[0x3D0];
	int Attacking;
	char _0x04B4[0x4];
	int Zooming;
	char _0x04BC[0x60];
	int Weapon;
	char _0x0520[0x74];
}clientinfo_t;

typedef struct
{
	char padding00[0x8];		 //0x0
	int Width;					 //0x8
	int Height;					 //0xC
	Vector2 Fov;				 //0x10
	Vector3 viewOrigin;		     //0x18
	Vector3 viewAxis[3];		 //0x24
}RefDef_t;

typedef struct
{
	int Servertime;					//0x0
	char padding00[0xA];			//0x4
	short Stance;					//0xE
	char padding01[0xC];			//0x10
	Vector3 Origin;					//0x1C
	char padding02[0x128];			//0x28
	int ClientNumber;				//0x150
	char padding03[0x4];			//0x154
	Vector3 ViewAngle;				//0x158
	char padding04[0x38];			//0x164
	int Health;						//0x19C
	char padding05[0xDC];			//0x1A0
	int WeaponPrimary;				//0x27C
	char padding06[0xF0];			//0x280
	int Weapon;						//0x370
	char padding07[0x8];			//0x374
	float SpreadMultiplier;			//0x37C
	char papdding08[0x6B72C];		//0x380
	RefDef_t RefDef;				//0x6BAAC
	char padding09[0x92494];		//0x6BAF4
	clientinfo_t ClientInfo[18];	//0xFDF88
}cgArray_t;

typedef struct
{
	int time;     //0x0
	int buttons;    //0x4
	int viewAngles[3];   //0x8
	char padding00[0x8];  //0x14
	char fDir;
	char rDir;
	char uDir;
	char yDir;     //0x1C
	char padding[0xC];   //0x20
						 //Size: 0x2C
}Usercmd_t;

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

typedef struct
{
	bool ADS;					 //0x00
	char padding00[0xDF];        //0x01
	Vector3 baseAngle;          //0xE0
	char paddig00[0x34C4];       //0xE8
	Vector3 viewAngle;          //0x35B0
	Usercmd_t Usercmd[128];      //0x35BC
	int CurrentCmdNumber;        //0x4BBC
}ClientActive_t;

typedef struct
{
	char padding03[0x2];		 //0x0
	char Alive;					 //0x2
	char padding04[0x10];		 //0x10
	Vector3 Origin;				 //0x14
	Vector3 viewAngle; //0x0020 
	char _0x002C[48];
	int Flags; //0x5C
	char _0x0060[12];
	Vector3 OldOrigin; //0x006C 
	char _0x0078[24];
	Vector3 ViewAngles1; //0x0090 
	char padding00[0x28];
	int Handle; //0xC4
	int Type;
	char padding01[0x10];
	Vector3 NewOrigin; //0x00DC
	char _0x00E8[24];
	Vector3 ViewAngles2; //0x0100 
	char _0x010C[131];
	char WeaponID; //0x018F 
	char _0x0190[55];
	char State; //0x01C7 
	char _0x01C8[0x24];
	//
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

enum Teams
{
	null,
	Axis,
	Allies,
	Spectator,
};

struct trace_t
{
	float fraction;					//0x0000
	Vector3 normal;					//0x0004
	int surfaceFlags;				//0x0010
	int contents;					//0x0014
	const char *material;			//0x0018
	int hitType;					//0x001c
	unsigned short hitId;			//0x0020
	unsigned short modelIndex;		//0x0022
	unsigned short partName;		//0x0024
	unsigned short partGroup;		//0x0026
	bool allsolid;					//0x0028
	bool startsolid;				//0x0029
	bool walkable;					//0x002A
	char _0x002B[5];
	Vector3 endpos;					//0x0030 
	char _0x003C[4];
	unsigned long materialType;		//0x0040 
	char _0x0044[0x20];
};

struct UiContext
{
	char _0x0000[0x20];
	int screenWidth;//0x20
	int screenHeight;//0x24
	char _0x0028[0x4];
	float FPS;
};

cgArray_t* cgArray_s; //8263EE60
ClientActive_t* ClientActive; //82713DC4
pCentity_t Centity_s; //826436B8
UiContext uicontext;