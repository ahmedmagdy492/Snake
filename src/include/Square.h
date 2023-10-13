#pragma once

#include <stdlib.h>
#include <raylib.h>

static int speed = 4;
static int score = 0;

struct Direction {
  int direction;
  char axis;
};

struct Square {
  struct Direction cur_dir;
  struct Direction prev_dir;
  int x;
  int y;
  int w;
  int h;
  Color color;
  struct Square* next;
  struct Square* prev;
};

struct DLinkedList {
  struct Square* head;
  struct Square* tail;
};

static struct DLinkedList snake = { NULL, NULL };

void Append(struct Square* square) {
  if(snake.head == NULL && snake.tail == NULL) {
    snake.head = snake.tail = square;
  }
  else {
    square->x = snake.tail->x + snake.tail->w;
    square->y = snake.tail->y;
    square->color = YELLOW;
    snake.tail->next = square;
    square->prev = snake.tail;
    snake.tail = snake.tail->next;
  }
  square->cur_dir.direction = square->prev_dir.direction = 1;
  square->cur_dir.axis = square->prev_dir.axis = 'x';
}

void Clear() {
  struct Square* ptr = snake.head;

  while(ptr != NULL) {
    struct Square* temp;
    if(ptr) {
      temp = ptr->next;
      free(ptr);
    }
    ptr = temp;
  }

  snake.head = NULL;
  snake.tail = NULL;
}

void DrawSnake() {
  struct Square* ptr = snake.head;

  while(ptr != NULL) {
    DrawRectangle(ptr->x, ptr->y, ptr->w, ptr->h, ptr->color);
    ptr = ptr->next;
  }
}

void Move(struct Direction* dir, int sw, int sh) {
  struct Square* ptr = snake.head;
  struct Direction temp;
  
  temp.direction = ptr->cur_dir.direction;
  temp.axis = ptr->cur_dir.axis;
  
  ptr->cur_dir.direction = dir->direction;
  ptr->cur_dir.axis = dir->axis;

  ptr->prev_dir.direction = temp.direction;
  ptr->prev_dir.axis = temp.axis;
  int prevX = ptr->x;
  int prevY = ptr->y;

  if(ptr->cur_dir.axis == 'x') {
    ptr->x += (speed * ptr->cur_dir.direction);
  }
  else if(ptr->cur_dir.axis == 'y') {
    ptr->y += (speed * ptr->cur_dir.direction);
  }

  ptr = ptr->next;

  while(ptr != NULL) {
    ptr->prev_dir.direction = ptr->cur_dir.direction;
    ptr->prev_dir.axis = ptr->cur_dir.axis;
    ptr->cur_dir.direction = temp.direction;
    ptr->cur_dir.axis = temp.axis;
    temp.direction = ptr->prev_dir.direction;
    temp.axis = ptr->prev_dir.axis;
    
    if(ptr->cur_dir.axis == 'x') {
      int tempX = ptr->x;
      ptr->x = prevX;
      prevX = tempX;
    }
    else if(ptr->cur_dir.axis == 'y') {
      int tempY = ptr->y;
      ptr->y = prevY;
      prevY = tempY;
    }
    ptr = ptr->next;
  }
}

void SetPlayerScore(int _score) {
  score = _score;
}

void ResetScore() {
  score = 0;
}

int GetPlayerScore() {
  return score;
}
