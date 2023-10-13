#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "include/Square.h"
#include "include/Apple.h"
#include "include/Helper.h"

#define SCORE_LEN 1000
#define SQUARE_LEN 25

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
int timer = 0;
int isGameOver = 0;

void RandomizeApplePosition() {
  int x = GetRandNumber(SCREEN_WIDTH - GetAppleWidth());
  int y = GetRandNumber(SCREEN_HEIGHT - GetAppleHeight());
  SetApplePos(x, y);
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
  struct Square* square = (struct Square*)malloc(sizeof(struct Square));
  square->x = 10;
  square->y = 10;
  square->w = square->h = SQUARE_LEN;
  square->color = ORANGE;
  square->next = NULL;
  square->prev = NULL;
  Append(square);

  SetTargetFPS(60);

  char scoreText[SCORE_LEN];
  struct Direction dir = {1, 'x'};
  int prevKey = -1;

  while(!WindowShouldClose()) {
    if(!isGameOver) {
      if (IsKeyDown(KEY_RIGHT)) {
	if(prevKey == KEY_LEFT) {
	  isGameOver = 1;
	}
	prevKey = KEY_RIGHT;
	dir.direction = 1;
	dir.axis = 'x';
      }
      else if (IsKeyDown(KEY_LEFT)) {
	if(prevKey == KEY_RIGHT) {
	  isGameOver = 1;
	}
	prevKey = KEY_LEFT;
	dir.direction = -1;
	dir.axis = 'x';
      }
      else if (IsKeyDown(KEY_UP)) {
	if(prevKey == KEY_DOWN) {
	  isGameOver = 1;
	}
	prevKey = KEY_UP;
	dir.direction = -1;
	dir.axis = 'y';
      }
      else if (IsKeyDown(KEY_DOWN)) {
	if(prevKey == KEY_UP) {
	  isGameOver = 1;
	}
	prevKey = KEY_DOWN;
	dir.direction = 1;
	dir.axis = 'y';
      }

      Move(&dir, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    
      BeginDrawing();
      ClearBackground(DARKGREEN);
    
      DrawSnake();
      DrawApple();

      IntToAsci(GetPlayerScore(), scoreText);
      DrawText(scoreText, (SCREEN_WIDTH-20)/2, 10, 40, WHITE);

      if(AmICollidingWithMySelf()) {
	printf("Collided with my self\n");
	// TODO: GAME OVER
      }

      if(HasPlayerCollidedWithApple(square->x, square->y, square->w, square->h)) {
	SetPlayerScore(GetPlayerScore()+1);
	RandomizeApplePosition();

	struct Square* newSquare = (struct Square*)malloc(sizeof(struct Square));
	newSquare->w = newSquare->h = SQUARE_LEN;
	newSquare->next = NULL;
	newSquare->prev = NULL;
	Append(newSquare);
      }

      if(timer == APPLE_CHANGE_POS_TIME) {
	timer = 0;
	RandomizeApplePosition();
      }

      if(isGameOver) {
	DrawText("Game Over", (SCREEN_WIDTH-500)/2, (SCREEN_HEIGHT-120)/2, 120, WHITE);
	IntToAsci(GetPlayerScore(), scoreText);
	DrawText("Score: ", (SCREEN_WIDTH-500)/2, (SCREEN_HEIGHT-80)/2+120, 80, WHITE);
	DrawText(scoreText, (SCREEN_WIDTH)/2+100, (SCREEN_HEIGHT-80)/2+120, 80, WHITE);
      }
    
      EndDrawing();

      if(!isGameOver) {
	++timer;
      }
  }

  CloseWindow();

  Clear();

  return 0;
}
