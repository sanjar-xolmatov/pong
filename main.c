#include "main.h"
#include <stdio.h>
#include <raylib.h>

int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 625;

    const int playerHeight = 120;
    const int playerWidth = 20;

    const Vector2 initialPosition = { 60, 60 };

    InitWindow(screenWidth, screenHeight, "Pong");

    ball Ball = { initialPosition, 250.0f, 1, 1, 20, RAYWHITE };
    player Player1 = { 200.0f, { 0, (screenHeight - playerHeight)/2.0, playerWidth, playerHeight }, 0, "SCORE: " };
    player Player2 = { 200.0f, { screenWidth - playerWidth, (screenHeight - playerHeight)/2.0, playerWidth, playerHeight }, 0, "SCORE: " };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_W)) Player1.rec.y -= Player1.speed * deltaTime;
        if (IsKeyDown(KEY_S)) Player1.rec.y += Player1.speed * deltaTime;
        if (IsKeyDown(KEY_DOWN)) Player2.rec.y += Player2.speed * deltaTime;
        if (IsKeyDown(KEY_UP)) Player2.rec.y -= Player2.speed * deltaTime;

        if (Player2.rec.y < 0) {
            Player2.rec.y = 0;
        }
        if (Player1.rec.y < 0) {
            Player1.rec.y = 0;
        }
        if (Player1.rec.y + Player1.rec.height > screenHeight) {
            Player1.rec.y = screenHeight - Player1.rec.height;
        }
        if (Player2.rec.y + Player2.rec.height > screenHeight) {
            Player2.rec.y = screenHeight - Player2.rec.height;
        }

        if (Ball.position.y + Ball.radius >= screenHeight) Ball.directionY = -1;
        else if (Ball.position.x + Ball.radius + playerWidth >= screenWidth && CheckCollisionCircleRec(Ball.position, Ball.radius, Player2.rec)) {
            Ball.directionX = -1;
            Player2.score++;
        }
        else if (Ball.position.y - Ball.radius <= 0) Ball.directionY = 1;
        else if (Ball.position.x - Ball.radius - playerWidth <= 0 && CheckCollisionCircleRec(Ball.position, Ball.radius, Player1.rec)) {
            Ball.directionX = 1;
            Player1.score++;
        }
        else if (Ball.position.x + Ball.radius >= screenWidth || Ball.position.x - Ball.radius <= 0) {
            Ball.position = initialPosition;
            Ball.directionX = 1;
            Ball.directionY = 1;
        }

        Ball.position.x += Ball.speed * deltaTime * Ball.directionX;
        Ball.position.y += Ball.speed * deltaTime * Ball.directionY;

        sprintf(Player1.score_text, "SCORE: %d", Player1.score);
        sprintf(Player2.score_text, "SCORE: %d", Player2.score);

        BeginDrawing();
            ClearBackground(BLACK);

            DrawText(Player1.score_text, 150, 10, 40, RAYWHITE);
            DrawText(Player2.score_text, screenWidth - 150 - MeasureText(Player2.score_text, 40), 10, 40, RAYWHITE);
            DrawCircleV(Ball.position, Ball.radius, Ball.color);
            DrawRectangle(Player1.rec.x, Player1.rec.y, playerWidth, playerHeight, RAYWHITE);
            DrawRectangle(Player2.rec.x, Player2.rec.y, playerWidth, playerHeight, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
