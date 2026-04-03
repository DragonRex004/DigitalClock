#include <stdio.h>
#include <time.h>
#include "raylib/raylib.h"

#define WIDTH 650
#define HEIGHT 450
#define TITLE "Digital Clock"
#define CLOCK_COLOR RED

const Vector2 hour_ten            = {50, 150};
const Vector2 hour_one            = {120, 150};
const Vector2 first_doublepoint   = {200, 190};
const Vector2 min_ten             = {225, 150};
const Vector2 min_one             = {295, 150};
const Vector2 sec_doublepoint     = {375, 190};
const Vector2 sec_ten             = {400, 150};
const Vector2 sec_one             = {470, 150};

void DrawFancySegment(Vector2 pos, int length, int thickness, bool horizontal, Color color) {
    int bevel = thickness / 2;

    if (horizontal) {
        DrawRectangle(pos.x + bevel, pos.y, length - thickness, thickness, color);
        
        Vector2 v1 = { pos.x + bevel, pos.y };
        Vector2 v2 = { pos.x, pos.y + bevel };
        Vector2 v3 = { pos.x + bevel, pos.y + thickness };
        DrawTriangle(v1, v2, v3, color);
        
        Vector2 v4 = { pos.x + length - bevel, pos.y };
        Vector2 v5 = { pos.x + length - bevel, pos.y + thickness };
        Vector2 v6 = { pos.x + length, pos.y + bevel };
        DrawTriangle(v4, v5, v6, color);
    } else {
        DrawRectangle(pos.x, pos.y + bevel, thickness, length - thickness, color);
        
        Vector2 v1 = { pos.x + bevel, pos.y };
        Vector2 v2 = { pos.x, pos.y + bevel };
        Vector2 v3 = { pos.x + thickness, pos.y + bevel };
        DrawTriangle(v1, v2, v3, color);
        
        Vector2 v4 = { pos.x, pos.y + length - bevel };
        Vector2 v5 = { pos.x + bevel, pos.y + length };
        Vector2 v6 = { pos.x + thickness, pos.y + length - bevel };
        DrawTriangle(v4, v5, v6, color);
    }
}

void DrawStyledDigit(Vector2 pos, int number, Color color) {
    static const bool segments[10][7] = {
        {1,1,1,1,1,1,0}, {0,1,1,0,0,0,0}, {1,1,0,1,1,0,1}, {1,1,1,1,0,0,1}, {0,1,1,0,0,1,1},
        {1,0,1,1,0,1,1}, {1,0,1,1,1,1,1}, {1,1,1,0,0,0,0}, {1,1,1,1,1,1,1}, {1,1,1,1,0,1,1}
    };

    int L = 40;
    int T = 10;
    int G = 1;

    Color offColor = ColorAlpha(color, 0.05f);

    DrawFancySegment((Vector2){pos.x + T, pos.y}, L, T, true, segments[number][0] ? color : offColor);
    DrawFancySegment((Vector2){pos.x + L + T + G, pos.y + T + G}, L, T, false, segments[number][1] ? color : offColor);
    DrawFancySegment((Vector2){pos.x + L + T + G, pos.y + L + 2*T + 3*G}, L, T, false, segments[number][2] ? color : offColor);
    DrawFancySegment((Vector2){pos.x + T, pos.y + 2*L + 2*T + 4*G}, L, T, true, segments[number][3] ? color : offColor);
    DrawFancySegment((Vector2){pos.x, pos.y + L + 2*T + 3*G}, L, T, false, segments[number][4] ? color : offColor);
    DrawFancySegment((Vector2){pos.x, pos.y + T + G}, L, T, false, segments[number][5] ? color : offColor);
    DrawFancySegment((Vector2){pos.x + T, pos.y + L + T + 2*G}, L, T, true, segments[number][6] ? color : offColor);
}

int main() {
    time_t now;
    struct tm *local;
    float timer = 0;
    bool showColon = true;

    InitWindow(WIDTH, HEIGHT, TITLE);

    Image icon = LoadImage("clock.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        time(&now);
        local = localtime(&now);

        timer += GetFrameTime();
        if (timer >= 0.5f) {
            showColon = !showColon;
            timer = 0;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(ctime(&now), 10, 10, 20, WHITE);

            DrawStyledDigit(hour_ten, local->tm_hour / 10, CLOCK_COLOR);
            DrawStyledDigit(hour_one, local->tm_hour % 10, CLOCK_COLOR);
            if (showColon) {
                DrawCircle(first_doublepoint.x, first_doublepoint.y, 5, CLOCK_COLOR);
                DrawCircle(first_doublepoint.x, first_doublepoint.y + 40, 5, CLOCK_COLOR);
            }
            DrawStyledDigit(min_ten, local->tm_min / 10, CLOCK_COLOR);
            DrawStyledDigit(min_one, local->tm_min % 10, CLOCK_COLOR);
            if (showColon) {
                DrawCircle(sec_doublepoint.x, sec_doublepoint.y, 5, CLOCK_COLOR);
                DrawCircle(sec_doublepoint.x, sec_doublepoint.y + 40, 5, CLOCK_COLOR);
            }
            DrawStyledDigit(sec_ten, local->tm_sec / 10, CLOCK_COLOR);
            DrawStyledDigit(sec_one, local->tm_sec % 10, CLOCK_COLOR);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}