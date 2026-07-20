#pragma once
#include <pond.h>
#include "globals.h"

enum
{
	ENTITY_TYPE_NONE = 0,
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_PROJECTILE,
	ENTITY_TYPE_ENEMY,
	ENTITY_TYPE_ATTACHMENT,
};

enum
{
	ATTACHMENT_TYPE_NONE = 0,
	ATTACHMENT_TYPE_DEFAULT,
};

typedef union 
{
	int projectileType;
	int attachmentType;

} TypeData;

typedef struct
{
	int type;
	TypeData typeData;
	Pond_Vector2Float position;
	Pond_Vector2Float velocity;
	float lifeTime;

} Entity;

#define MAX_ENTITY_COUNT 100

Entity entityList[MAX_ENTITY_COUNT];

typedef int eid;

eid playerID;
#define SHOOT_COOLDOWN .1
float curShootCD;
#define PROJECTILE_LIFETIME 1
#define PROJECTILE_SPEED 5

void EntityInit(void);
void EntityUpdate(void);
void EntityDraw(void);

eid NewEntity(int type);

void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);
#define PLAYER_ACC 2
#define PLAYER_MAX_SPD 3
#define PLAYER_DECC 0.95

#define MAX_ATTACHMENT_COUNT 3

int attachments[MAX_ATTACHMENT_COUNT];
void AddAttachment(int type);
void RemoveAttachment();
void AttachmentDraw(void);
void AttachmentAction(void);