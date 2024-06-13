#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float runningTime;
    float updateTime;
};

AnimData updateAnimation(AnimData data, float dt, int maxFrames)
{

    if (data.runningTime >= data.updateTime)
    {

        data.runningTime = 0;
        data.rec.x = data.frame * data.rec.width;

        if (data.frame > maxFrames)
        {
            data.frame = 0;
        }

        data.frame++;
    }
    return data;
};

int main()
{

    const int windowWidth = 800;
    const int windowHeight = 600;

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    int velocityUp{0};
    int gravity{2000};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");

    // Main Character Texture

    Texture2D mainCharacter = LoadTexture("textures/scarfy.png");

    AnimData dasherData;
    dasherData.rec = {
        0,
        0,
        static_cast<float>(mainCharacter.width) / 6,
        static_cast<float>(mainCharacter.height)

    };
    dasherData.pos = {
        windowWidth / 2 - dasherData.rec.width / 2,
        windowHeight - dasherData.rec.height};

    dasherData.frame = 0;
    dasherData.runningTime = 0.0;
    dasherData.updateTime = 1.0 / 12.0;

    // Enemy Texture

    Texture2D enemy = LoadTexture("textures/enemy.png");
    int eneyArrLength{5};

    AnimData enemyArr[eneyArrLength]{};

    for (int i = 0; i < eneyArrLength; i++)
    {
        enemyArr[i].rec.x = 0.0;
        enemyArr[i].rec.y = 0.0;
        enemyArr[i].rec.width = enemy.width / 8;
        enemyArr[i].rec.height = enemy.height / 8;
        enemyArr[i].pos.y = windowHeight - enemy.height / 8;
        enemyArr[i].frame = 0;
        enemyArr[i].runningTime = 0.0;
        enemyArr[i].updateTime = 1.0 / 16.0;
        enemyArr[i].pos.x = windowWidth + i * 900;
    }

    int enemyXVelocity{-600};

    // teste

    bool isOnTheGround{true};

    float backgroundX{};
    float midGroundX{};
    float foregroundX{};

    float finishLine{enemyArr[eneyArrLength - 1].pos.x};
    bool collision{false};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(PURPLE);
        float dt{GetFrameTime()};

        backgroundX -= 20 * dt;
        if (backgroundX <= -background.width * 3.5)
        {
            backgroundX = 0;
        }

        Vector2 background1Pos{backgroundX, 0.0};
        Vector2 background2Pos{backgroundX + background.width * 3.5, 0.0};
        DrawTextureEx(background, background1Pos, 0.0, 3.5, WHITE);
        DrawTextureEx(background, background2Pos, 0.0, 3.5, WHITE);

        midGroundX -= 40 * dt;
        if (midGroundX <= -midground.width * 3.5)
        {
            midGroundX = 0;
        }

        Vector2 midgroundPos1 = {midGroundX, 0.0};
        Vector2 midgroundPos2 = {midGroundX + midground.width * 3.5, 0.0};

        DrawTextureEx(midground, midgroundPos1, 0.0, 3.5, WHITE);
        DrawTextureEx(midground, midgroundPos2, 0.0, 3.5, WHITE);

        foregroundX -= 80 * dt;
        if (foregroundX <= -foreground.width * 3.5)
        {
            foregroundX = 0;
        }

        Vector2 foregroundPos1 = {foregroundX, 0.0};
        Vector2 foregroundPos2 = {foregroundX + foreground.width * 3.5, 0.0};

        DrawTextureEx(foreground, foregroundPos1, 0.0, 3.5, WHITE);
        DrawTextureEx(foreground, foregroundPos2, 0.0, 3.5, WHITE);

        for (AnimData data : enemyArr)
        {

            float pad{50};
            Rectangle enemyRec{
                data.pos.x + pad,
                data.pos.y + pad,
                data.rec.width - 2 * pad,
                data.rec.height - 2 * pad,
            };
            Rectangle characterRec{
                dasherData.pos.x,
                dasherData.pos.y,
                dasherData.rec.width,
                dasherData.rec.height,
            };

            if (CheckCollisionRecs(enemyRec, characterRec))
            {
                collision = true;
            }
        }

        if (!collision && dasherData.pos.x < finishLine)
        {

            dasherData.runningTime += dt;

            isOnTheGround = dasherData.pos.y >= windowHeight - dasherData.rec.height;

            if (isOnTheGround)
            {
                velocityUp = 0;

                dasherData = updateAnimation(dasherData, dt, 5);
            }
            else
            {
                velocityUp += gravity * dt;
            }

            if (IsKeyPressed(KEY_SPACE) && isOnTheGround)
            {
                velocityUp -= 800;
            }

            finishLine += enemyXVelocity * dt;
            dasherData.pos.y += velocityUp * dt;

            for (int i = 0; i < eneyArrLength; i++)
            {

                enemyArr[i].runningTime += dt;
                enemyArr[i].pos.x += enemyXVelocity * dt;

                enemyArr[i] = updateAnimation(enemyArr[i], dt, 7);
                DrawTextureRec(enemy, enemyArr[i].rec, enemyArr[i].pos, WHITE);
            }

            DrawTextureRec(mainCharacter, dasherData.rec, dasherData.pos, WHITE);
        }
        else if (!collision && dasherData.pos.x >= finishLine)
        {
            DrawText("You WIN", windowWidth / 2, windowHeight / 2, 16, RED);
        }
        else
        {
            DrawText("You LOST", windowWidth / 2, windowHeight / 2, 16, RED);
        }

        EndDrawing();
    }

    UnloadTexture(mainCharacter);
    UnloadTexture(enemy);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}