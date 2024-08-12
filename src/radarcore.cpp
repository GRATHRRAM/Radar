#include <cstdint>
#include <raylib.h>
#include "radarcore.hpp"

Radar::Radar(uint16_t ResX, uint16_t ResY) {
    InitWindow(ResX,ResY,"Radar");
    Radar::Camera = {
        (Vector2){static_cast<float>(ResX/2),static_cast<float>(ResY/2)},
        (Vector2){0,0},
        0,
        1
    };
}

Radar::~Radar() {
    CloseWindow();
}

void Radar::Run() {
    while (!WindowShouldClose()) {
        UpdateRender();
    }
}

void Radar::UpdateRender() {
    BeginDrawing();
    ClearBackground(GRAY);
    DrawRectangle(0,0,10,10,WHITE);
    EndDrawing();
}
 
