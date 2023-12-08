#pragma once
struct GameInfoComponent
{
    bool advanceLevel = false;
    bool gameOver     = false;
    int  currLevel    = 0;
    int  bonus        = 8000;
};