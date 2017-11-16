#ifndef PLAYER_H
#define PLAYER_H

class player
{
private:
    double mLocationX{0};
    double mLocationY{0};
    double mLocationZ{0};
    bool mGameState{nullptr};
    int mLevel{0};

public:
    void get_player_location(double &xCenter, double &yCenter,double &zCenter);
    void set_player_location(double xCenter,double yCenter,double zCenter);
    void set_game(bool state);

};

#endif
