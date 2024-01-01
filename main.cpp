#include "raylib.h"

int main() {

    InitWindow(200, 200, "Teste");
    
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        DrawCircle(100,100, 25, RED);

        EndDrawing();
    }
    
}