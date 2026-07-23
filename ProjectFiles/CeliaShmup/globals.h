#pragma once

#define SCALE 5
#define WINDOW_WIDTH 160 * SCALE
#define WINDOW_HEIGHT 144 * SCALE
#define DEBUG 1

#define BLACK (Pond_Colour){ 0, 0, 0, 255 }
#define RED (Pond_Colour){ 255, 100, 100, 255 }

Pond_Font* defaultFont;
Pond_Texture* defaultTexture;
Pond_Texture* playerTexture;
Pond_Texture* projectileTexture;