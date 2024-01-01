#include "raylib.h"

int main()
{
    int width = 800;
    int height = 450;

    int circleX = 200;
    int circleY = 200;
    int circleRadius = 25;
    int circleLeftEdge = circleX - circleRadius;
    int circleRightEdge = circleX + circleRadius;
    int circleTopEdge = circleY - circleRadius;
    int circleBottomEdge = circleY + circleRadius;

    int squareX = 400;
    int squareY = 0;
    int squareL = 50;
    int squareLeftEdge = squareX;
    int squareRightEdge = squareX + squareL;
    int squareTopEdge = squareY;
    int squareBottomEdge = squareY + squareL;

    int direction = 10;

    bool isGameOver =
        (squareBottomEdge >= circleTopEdge) &&
        (squareTopEdge <= circleBottomEdge) &&
        (squareRightEdge >= circleLeftEdge) &&
        (squareLeftEdge <= circleRightEdge);

    InitWindow(width, height, "ball");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(WHITE);

        if (isGameOver)
        {
            DrawText("Game Over!!", width / 2 -58, height / 2 -26, 26, RED);
        }
        else
        {   

            circleLeftEdge = circleX - circleRadius;
            circleRightEdge = circleX + circleRadius;
            circleTopEdge = circleY - circleRadius;
            circleBottomEdge = circleY + circleRadius;

            squareLeftEdge = squareX;
            squareRightEdge = squareX + squareL;
            squareTopEdge = squareY;
            squareBottomEdge = squareY + squareL;
            isGameOver =
                (squareBottomEdge >= circleTopEdge) &&
                (squareTopEdge <= circleBottomEdge) &&
                (squareRightEdge >= circleLeftEdge) &&
                (squareLeftEdge <= circleRightEdge);


            DrawCircle(circleX, circleY, circleRadius, BLUE);

            DrawRectangle(squareX, squareY, squareL, squareL, PURPLE);

            squareY += direction;

            if (squareY >= height - squareL / 2 || squareY <= 0)
            {
                direction = -direction;
            }

            if (IsKeyDown(KEY_RIGHT) && circleX < width - circleRadius)
            {
                circleX += 10;
            }
            if (IsKeyDown(KEY_LEFT) && circleX > circleRadius)
            {
                circleX -= 10;
            }

           
        }

        EndDrawing();
    }
}