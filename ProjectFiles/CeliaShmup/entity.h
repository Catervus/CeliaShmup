#pragma once
#include <pond.h>
#include "globals.h"

enum
{
	ENTITY_TYPE_NONE = 0,
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_PROJECTILE,
	ENTITY_TYPE_ENEMY,
};

typedef struct
{
	int type;
	Pond_Vector2Float position;
	Pond_Vector2Float velocity;
	float lifeTime;

} Entity;

#define MAX_ENTITY_COUNT 30

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