#include "utils.h"
#include <cmath>
#include <iostream>

void setOriginToCenter(sf::Sprite &object)
{
    //Set the origin of a Sprite to his center
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void normalise(sf::Vector2f &vect){
    //Normalise a Vector2f
    float norm = std::sqrt(vect.x*vect.x+vect.y*vect.y);
    vect = vect/norm;

}

float radtodeg(float f){
    //Convert radian to degree's
    float pi = 3.1415;
    float r = f*360/(2*pi);
    while(r<0){

        r = r+360;
    }

    r = (int)r%360;

    return r;
}

float normev(sf::Vector2f vect){
    //Return the norm of a vector
    return std::sqrt(vect.x*vect.x+vect.y*vect.y);
}

float vectAngle(sf::Vector2f vect){
    //Return the angle of a vector in radian
    sf::Vector2f f = vect;
    normalise(f);
    float theta = acos(f.x);
    if(f.y > 0){
        theta = 2*3.1415-theta;
    }
    return theta;
}

void setOriginToCenter(sf::Shape &object)
{
    //Set the origin of a Shape to his center
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y)
{
    //Set the size of a Sprite to a minimum
    double scalingFactor = std::max(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y)
{
    //Set the size of a Sprite to a maximum
    double scalingFactor = std::min(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleByRadius(sf::Sprite &sp, int radius)
{
    //Scale a Sprite by a radius number
    double scalingFactor = 2*radius/std::sqrt(sp.getTextureRect().width*sp.getTextureRect().width + sp.getTextureRect().height*sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center)
{
    //Set the origin of a Text to his center
    sf::Vector2f offset;
    offset.x = txt.getPosition().x - txt.getGlobalBounds().left - txt.getGlobalBounds().width/2.;
    offset.y = txt.getPosition().y - txt.getGlobalBounds().top - txt.getGlobalBounds().height/2.;

    txt.setPosition(center + offset);
}