#include "entity.h"

// -- INIT --

void EntityInit(void) 
{
	for (int i = 0; i < MAX_ENTITY_COUNT; i++)
	{
		entityList[i].type = ENTITY_TYPE_NONE;
	}
	PlayerInit();
}

eid NewEntity(int type)
{
	for (int i = 1; i < MAX_ENTITY_COUNT; i++)
	{
		if (entityList[i].type == ENTITY_TYPE_NONE)
		{
			entityList[i].type = type;
			return i;
		}
	}
}

void PlayerInit(void)
{
	entityList[playerID].type = ENTITY_TYPE_PLAYER;
	entityList[playerID].position = (Pond_Vector2Float){ 50, 50 };
	entityList[playerID].velocity = (Pond_Vector2Float){ 0, 0 };
}

// -- UPDATE -- 

void EntityUpdate(void)
{
	PlayerUpdate();

	for (int i = 0; i < MAX_ENTITY_COUNT; i++)
	{
		if (entityList[i].type == ENTITY_TYPE_NONE)
			continue;

		entityList[i].position.x += entityList[i].velocity.x;
		entityList[i].position.y -= entityList[i].velocity.y;
	}
}

void PlayerUpdate(void)
{

	entityList[playerID].velocity.x = 0;
	entityList[playerID].velocity.y = 0;

	if (Pond_GetKey(POND_KEYBOARD_KEY_W))
	{
		entityList[playerID].velocity.y = PLAYER_ACC;
	}

	if (Pond_GetKey(POND_KEYBOARD_KEY_S))
	{
		entityList[playerID].velocity.y = -PLAYER_ACC;
	}

	if (Pond_GetKey(POND_KEYBOARD_KEY_D))
	{
		entityList[playerID].velocity.x = PLAYER_ACC;
	}

	if (Pond_GetKey(POND_KEYBOARD_KEY_A))
	{
		entityList[playerID].velocity.x = -PLAYER_ACC;
	}

	// entityList[playerID].velocity.x *= PLAYER_DECC;
	// entityList[playerID].velocity.y *= PLAYER_DECC;
}

// -- DRAW -- 

void EntityDraw(void)
{

	PlayerDraw();
}

void PlayerDraw(void)
{
	for (int i = 0; i < MAX_ENTITY_COUNT; i++)
	{
		if (entityList[i].type == ENTITY_TYPE_NONE)
			continue;

		Pond_DrawRectByDimensions(entityList[i].position.x * SCALE, entityList[i].position.y * SCALE,
			16 * SCALE, 16 * SCALE, BLACK, 1);
	}
}