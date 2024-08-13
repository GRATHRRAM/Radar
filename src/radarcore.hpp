#pragma once
#include <cstdint>
#include <raylib.h>
#include <stdint.h>
#include <vector>
#include <string>

class Radar {
    private:
        typedef struct Plane {
            Vector2 Position;
            Vector3 Velocity;
            std::string name;
            Color color;
        } Plane;
        
        uint16_t ResX;
        uint16_t ResY;
        Camera2D Camera;
        std::vector<Plane> Planes;
        float PlaneSpawnTime;
        float DeltaTime;
        
        void UpdateRender();
        void UpdatePlanes();
        void UpdateEvent();
        void SpawnPlane();
        void DestroyPlane(uint16_t VectorPosition);
    public:
        Radar(uint16_t ResX, uint16_t ResY);
        ~Radar();

        void Run();
}; 
