#pragma once
#include <pond.h>
#include "globals.h"
#include "entity.h"

void Init(void);
void Update(void);
void Draw(void);

typedef enum 
{
	UNDEFINED = 0,
	MENU = 1,
	GAMEPLAY = 2

} E_GameState;

typedef struct
{
	E_GameState gameState;

} GameManager;

GameManager gameManager;
void InitialiseGameManager(void);
