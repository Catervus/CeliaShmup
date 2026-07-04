#include "main.h"


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
}