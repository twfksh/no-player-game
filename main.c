/*****************************************************************************
*
*   no_player_game - Conway's Game of Life
*	Author: toufiq7r
*	Time: 10:40 PM
*	Date: 27 September 2023
* 
******************************************************************************/

#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCR_WIDTH	600
#define SCR_HEIGHT	400
#define RESOLUTION	10
#define ROWS		((SCR_HEIGHT)/(RESOLUTION))
#define COLS		((SCR_WIDTH)/(RESOLUTION))
#define MAX_CELL	((ROWS)*(COLS))

#define DEAD	LIGHTGRAY
#define ALIVE	DARKGRAY

int count_neighbors(int* cell, int x, int y) {
	int res = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int _x = (x + i + ROWS) % ROWS;
			int _y = (y + j + COLS) % COLS;
			int _i = _x * COLS + _y; // Calculate the index of the rectangle
			res += cell[_i];
		}
	}
	int i = x * COLS + y; 
	res -= cell[i];
	return res;
}

int main(void) {

	InitWindow(SCR_WIDTH, SCR_HEIGHT, "no_player_game - Conway's Game of Life");

	Rectangle matrix[MAX_CELL] = { 0 }; // Initialize the game of life matrix

	for (int x = 0; x < ROWS; x++) {
		for (int y = 0; y < COLS; y++) {
			int i = x * COLS + y; // Calculate the index of the rectangle
			matrix[i].x			= y * RESOLUTION;
			matrix[i].y			= x * RESOLUTION;
			matrix[i].width		= RESOLUTION;
			matrix[i].height	= RESOLUTION;
		}
	}

	int state[MAX_CELL] = { 0 };

	bool initialized = false;

	srand(time(NULL)); // Seed the random number generator with current time

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		// Update cell state
		if (!initialized) {
			for (int i = 0; i < MAX_CELL; i++) state[i] = rand() % 2; // Generate a random number between 0 (dead) or 1 (alive)
			initialized = true;
		} else {
			for (int x = 0; x < ROWS; x++) {
				for (int y = 0; y < COLS; y++) {
					int neighbors = count_neighbors(state, x, y);
					int i = x * COLS + y;
					if (state[i] == 0 && neighbors == 3) state[i] = 1;
					else if (state[i] == 1 && (neighbors < 2 || neighbors > 3)) state[i] = 0;
				}
			}
		}

		BeginDrawing();

			ClearBackground(RAYWHITE);
			
			for (int i = 0; i < MAX_CELL; i++) {
				DrawRectangleRec(matrix[i], (state[i]) ? ALIVE : DEAD);
			}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}