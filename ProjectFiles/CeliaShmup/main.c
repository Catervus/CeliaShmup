#include "main.h"

Pond_Font* defaultFont;

int main(void)
{
	Pond_Init(&Init, &Update, &Draw);
	Pond_InitAudioSystem(8, 10, 20);
	Pond_Run(60, WINDOW_WIDTH, WINDOW_HEIGHT, "Celia Shmup", 1);

	return 0;
}

void Init(void)
{
	Pond_SetWindowMode(POND_WINDOW_MODE_WINDOWED);
	Pond_SetRenderClearColour(BLACK);
	Pond_SetWindowResizable(1);

	InitialiseGameManager();
	EntityInit();

	defaultFont = Pond_LoadFont("assets/monogram.ttf");
}

void InitialiseGameManager(void)
{
	gameManager.gameState = MENU;
}

void Update(void)
{
	switch (gameManager.gameState)
	{
		case MENU:
		{
			if (Pond_GetKeyDown(POND_KEYBOARD_KEY_E))
			{
				gameManager.gameState = GAMEPLAY;
			}

		} break;

		case GAMEPLAY:
		{
			EntityUpdate();

		} break;
	}
}

void Draw(void)
{
	switch (gameManager.gameState)
	{
		case MENU:
		{

		} break;

		case GAMEPLAY:
		{
			Pond_SetRenderClearColour(RED);
			EntityDraw();

		} break;
	}

	Pond_DrawRectByDimensions(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, (Pond_Colour) { 255, 0, 0, 255 }, 0);
	
	if (DEBUG)
	{
		int count = 0;
		for (int i = 0; i < MAX_ENTITY_COUNT; i++)
		{
			if (entityList[i].type != ENTITY_TYPE_NONE)
				count++;

		}
		
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "Entity: %i", count);

		Pond_DrawText(buffer, 0, 0, BLACK, SCALE, SCALE, defaultFont);
	}
}	