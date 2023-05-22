#include "Files/Ships.h"
#include "Files/Map.h"

enum class PlayMode : int
{
    SOLO = 0,
    PVE = 1,
    PVP = 2
};

inline PlayMode HandlePlayMode(int Mode)
{
    switch (Mode)
    {
    case 0:
        printf("Chosen: Solo\n");
        return PlayMode::SOLO;
        break;
    case 1:
        printf("Chosen: PVE\n");
        return PlayMode::PVE;
        break;
    case 2:
        printf("Sorry, this mode is not supported yet (PVP)\n");
        return PlayMode::PVP;
        break;
    default:
        printf("Chosen: Solo\n");
        return PlayMode::SOLO; 
        break;
    }
}