#pragma once

struct Animation
{
    int index;
    int frames;
    int speed;

    Animation() 
    {
        this->index = 0;
        this->frames = 0;
        this->speed = 1;
    }

    Animation(int index, int frames, int speed)
    {
        this->index = index;
        this->frames = frames;
        this->speed = speed;
    }
};
