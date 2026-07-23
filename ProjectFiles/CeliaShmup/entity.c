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
	playerID = NewEntity(ENTITY_TYPE_PLAYER);
	entityList[playerID].position = (Pond_Vector2Float){ 50, 50 };
	entityList[playerID].velocity = (Pond_Vector2Float){ 0, 0 };
	entityList[playerID].sprite = playerTexture;

	Entity e = entityList[playerID];

	for (int i = 0; i < MAX_ATTACHMENT_COUNT; i++)
	{
		attachments[i] = ATTACHMENT_TYPE_NONE;
	}
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

		if (entityList[i].type == ENTITY_TYPE_PROJECTILE)
		{
			if (entityList[i].lifeTime <= 0)
			{
				entityList[i].type = ENTITY_TYPE_NONE;
				continue;
			}
			entityList[i].lifeTime -= Pond_GetDeltaTime();
		}
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

	if (Pond_GetKey(POND_KEYBOARD_KEY_RETURN))
	{
		if (curShootCD <= 0)
		{
			eid id = NewEntity(ENTITY_TYPE_PROJECTILE);
			entityList[id].position = entityList[playerID].position;
			entityList[id].velocity = (Pond_Vector2Float){ PROJECTILE_SPEED, 0 };
			entityList[id].lifeTime = PROJECTILE_LIFETIME;
			entityList[id].sprite = projectileTexture;

			curShootCD = SHOOT_COOLDOWN;

			AttachmentAction();
		}
	}

	if (Pond_GetKeyDown(POND_KEYBOARD_KEY_SPACE))
	{
		AddAttachment(ATTACHMENT_TYPE_DEFAULT);
	}

	curShootCD -= Pond_GetDeltaTime();

	// entityList[playerID].velocity.x *= PLAYER_DECC;
	// entityList[playerID].velocity.y *= PLAYER_DECC;
}

void AddAttachment(int type)
{
	for (int i = 0; i < MAX_ATTACHMENT_COUNT; i++)
	{
		if (attachments[i] == ATTACHMENT_TYPE_NONE) 
		{
			attachments[i] = type;
			break;
		}
	}
}

void AttachmentAction(void)
{
	for (int i = 0; i < MAX_ATTACHMENT_COUNT; i++)
	{
		if (attachments[i] == ATTACHMENT_TYPE_NONE)
			continue;

		else if (attachments[i] == ATTACHMENT_TYPE_DEFAULT)
		{
			eid id = NewEntity(ENTITY_TYPE_PROJECTILE);
			entityList[id].position = entityList[playerID].position;
			entityList[id].position.y += (i + 1) * 16;
			entityList[id].velocity = (Pond_Vector2Float){ PROJECTILE_SPEED, 0 };
			entityList[id].lifeTime = PROJECTILE_LIFETIME;
			entityList[id].sprite = projectileTexture;
		}
	}
}

// -- DRAW -- 

void EntityDraw(void)
{
	for (int i = 0; i < MAX_ENTITY_COUNT; i++)
	{
		if (entityList[i].type == ENTITY_TYPE_NONE)
			continue;

		// if (entityList[i].type == ENTITY_TYPE_PROJECTILE)
		// {
		// 	Pond_DrawRectByDimensions(entityList[i].position.x * SCALE, entityList[i].position.y * SCALE,
		// 		8 * SCALE, 8 * SCALE, BLACK, 1);
		// 	continue;
		// }

		Pond_DrawTexture(entityList[i].sprite, entityList[i].position.x * SCALE,
			entityList[i].position.y * SCALE, SCALE, SCALE, 255);
		// Pond_DrawRectByDimensions(entityList[i].position.x * SCALE, entityList[i].position.y * SCALE,
		// 	16 * SCALE, 16 * SCALE, BLACK, 1);
	}

	PlayerDraw();
}

void PlayerDraw(void)
{
	AttachmentDraw();
}

void AttachmentDraw(void)
{
	for (int i = 0; i < MAX_ATTACHMENT_COUNT; i++)
	{
		if (attachments[i] == ATTACHMENT_TYPE_NONE)
			continue;

		else if (attachments[i] == ATTACHMENT_TYPE_DEFAULT)
		{
			Pond_Vector2Float pos = entityList[playerID].position;
			pos.y += (i + 1) * 16;

			Pond_DrawTexture(defaultTexture, pos.x * SCALE, pos.y * SCALE, SCALE, SCALE, 255);

			// Pond_DrawRectByDimensions(pos.x * SCALE, pos.y * SCALE,
			// 	16 * SCALE, 16 * SCALE, BLACK, 0);
		}
	}
}
