#include "player.h"

void player::get_player_location(double &xCenter, double &yCenter, double &zCenter)
{
    xCenter = mLocationX;
    yCenter = mLocationY;
    zCenter = mLocationZ;
}

void player::set_player_location(double xCenter, double yCenter, double zCenter)
{
    mLocationX = xCenter;
    mLocationY = yCenter;
    mLocationZ = zCenter;
}

void player::set_game(bool state)
{
    mGameState = state;
}
