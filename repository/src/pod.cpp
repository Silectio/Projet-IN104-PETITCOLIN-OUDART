#include "pod.h"
#include "game.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <math.h>
#include <vector>
#include <iostream>

Decision::Decision(sf::Vector2f target, float power) : target_(target), power_(power)
{};
Pod::Pod(){};
Pod::Pod(sf::Vector2f pos, float angle, sf::Vector2f vel) 
{
    //Set the angle, postition, velocity, next Checkpoint and current lap
    angle_=angle;
    pos_=pos;
    vel_=vel;
    nextCP_ = 0;
    lapCount_= 0;
};

Decision Pod::getDecision(GameInfos gameInfos) const
{
    //Return the position of next checkpoint of each pods
    sf::Vector2f Cp = gameInfos.cpPositions[nextCP_];
    return Decision(Cp, 100);
};

