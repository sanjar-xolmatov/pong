#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>

typedef struct Player {
    float speed;
    Rectangle rec;
    int score;
    char score_text[32];
} player;

typedef struct Ball {
    Vector2 position;
    float speed;
    int directionX;
    int directionY;
    float radius;
    Color color;
} ball;

#endif
