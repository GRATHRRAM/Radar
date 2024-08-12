#pragma once
#include <raylib.h>
#include <stdint.h>

class Radar {
    private:
        Camera2D Camera;

    public:
        Radar(uint16_t ResX, uint16_t ResY);
        ~Radar();

        void Run();
        void UpdateRender();
}; 
