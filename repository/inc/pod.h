#ifndef INC_POD_H
#define INC_POD_H

#include <SFML/System.hpp>
#include <cmath>

struct GameInfos;

struct Decision
{
    Decision(sf::Vector2f target, float power);

    sf::Vector2f target_; //Target of the pods
    float power_; //Power of the pods
};

class Pod
{
    public :
    Pod();
    Pod(sf::Vector2f pos, float angle, sf::Vector2f vel = {0, 0});
    Decision getDecision(GameInfos gameInfos) const; 
    float angle_; //angle in radians

    private :
    sf::Vector2f pos_, vel_; //position and velocity vectors
    
    int nextCP_, lapCount_; //id of next CheckPoint and current number of lap
    
    friend class Game; //allows game to modify pod's private attributes
};

#endif