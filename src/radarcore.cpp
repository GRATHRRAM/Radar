#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include "radarcore.hpp"
#include <time.h>

Radar::Radar(uint16_t ResX, uint16_t ResY) {
    InitWindow(ResX,ResY,"Radar");
    Radar::Camera = {
        (Vector2){static_cast<float>(ResX/2),static_cast<float>(ResY/2)},
        (Vector2){0,0},
        0,
        1
    };

    Radar::PlaneSpawnTime = 0;
    Radar::ResX = ResX;
    Radar::ResY = ResY;

    srand(time(0));
    SetTargetFPS(60);
}

Radar::~Radar() {
    CloseWindow();
    for(uint16_t i = 0; i < Radar::Planes.size(); ++i) {
        DestroyPlane(i);
    }
}

void Radar::Run() {
    while (!WindowShouldClose()) {
        DeltaTime = GetFrameTime();
        SpawnPlane();
        UpdatePlanes();
        UpdateEvent();
        UpdateRender();
    }
}

void Radar::UpdateRender() {
    BeginDrawing();
    ClearBackground(GRAY);
    BeginMode2D(Radar::Camera);
        
    for(uint16_t i = 0; i < Radar::Planes.size(); ++i) {
        DrawCircle(
            Planes.at(i).Position.x,
            Planes.at(i).Position.y,
            10,
            Planes.at(i).color
        );
    }

    EndMode2D();
    EndDrawing();
}

void Radar::SpawnPlane() {
   if(Radar::PlaneSpawnTime <= 0 || Planes.size() < 2) {
        char *name = new char[16];
        sprintf(name,"PL%u",GetRandomValue(0,1000));
        Plane pl = {
            (Vector2){static_cast<float>(GetRandomValue(ResX*-1,ResX)),
                     static_cast<float>(GetRandomValue(ResY*-1,ResY))},
            (Vector3){static_cast<float>(GetRandomValue(-200,200)),
                     static_cast<float>(GetRandomValue(-200,200)),0},
            name,
        };
        
        pl.color = (Color){
            static_cast<uint8_t>(GetRandomValue(0,255)),
            static_cast<uint8_t>(GetRandomValue(0,255)),
            static_cast<uint8_t>(GetRandomValue(0,255)),
            255
        };

        Radar::Planes.push_back(pl);
        
        delete[] name;
        PlaneSpawnTime = 1;
    }
    Radar::PlaneSpawnTime -= DeltaTime; 
}

void Radar::DestroyPlane(uint16_t VectorPosition) {
    Radar::Planes.erase(Radar::Planes.begin() + VectorPosition);
}

void Radar::UpdatePlanes() {
    for(uint16_t i = 0; i < Radar::Planes.size(); ++i) {
        if(Planes.at(i).Position.x > ResX * 3  ||
           Planes.at(i).Position.x < ResX * -3 ||
           Planes.at(i).Position.y > ResY * 3  ||
           Planes.at(i).Position.y < ResY * -3 ) DestroyPlane(i);

        Radar::Planes.at(i).Position.x += Radar::Planes.at(i).Velocity.x * DeltaTime;
        Radar::Planes.at(i).Position.y += Radar::Planes.at(i).Velocity.y * DeltaTime;
    }
}

void Radar::UpdateEvent() {
    if(IsKeyDown(KEY_UP)   && Camera.zoom < 1)   Camera.zoom += 1 * DeltaTime;
    if(IsKeyDown(KEY_DOWN) && Camera.zoom > 0.1) Camera.zoom -= 1 * DeltaTime;
}
