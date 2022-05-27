#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "checkpoint.h"
#include "game.h"
#include "utils.h"
CheckPoint::CheckPoint(){};

CheckPoint::CheckPoint(sf::Vector2f center, unsigned int id)
{
    //Create a circle at given position and set the id of the Checkpoint
    circle_ =  sf::CircleShape(600,100);
    setOriginToCenter(circle_);
    circle_.setPosition(center);
    circle_.setFillColor(sf::Color(0,0,0,63));
    circle_.setOutlineColor(sf::Color(0,0,0));
    circle_.setOutlineThickness(-50);
    id_ = id;

};

void CheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Draw the circle shape of the Checkpoint
    target.draw(circle_,states);
};

sf::Vector2f CheckPoint::getPosition()
{
    //return the position of the Checkpoint
    return circle_.getPosition();
}

FinalCheckPoint::FinalCheckPoint(sf::Vector2f center)
{
    //Create a circle at given position
    circle_ =  sf::CircleShape(600,100);
    setOriginToCenter(circle_);
    circle_.setPosition(center);
    circle_.setFillColor(sf::Color(0,0,0,63));
    circle_.setOutlineColor(sf::Color(0,0,0));
    circle_.setOutlineThickness(-50);
};

void FinalCheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Draw the circle shape of the FinalCheckpoint
    target.draw(circle_,states);
};

sf::Vector2f FinalCheckPoint::getPosition()
{
    //return the position of the FinalCheckpoint
    return circle_.getPosition();
}
