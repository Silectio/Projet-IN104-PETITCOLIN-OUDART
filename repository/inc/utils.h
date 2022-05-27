#ifndef INC_UTILS_H
#define INC_UTILS_H

#include <SFML/Graphics.hpp>

void setOriginToCenter(sf::Sprite &object); //Set the origin of a Sprite to his center
void setOriginToCenter(sf::Shape &object); //Set the origin of a Shape to his center

void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y);
void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y);
void scaleByRadius(sf::Sprite &sp, int radius);

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center);//Set the origin of a Text to his center
void normalise(sf::Vector2f &vect); //Normalize a sf::Vector2f
float vectAngle(sf::Vector2f vect); //Return the angle of a sf::Vector2f
float radtodeg(float rad); //Convert radian to degree's
float normev(sf::Vector2f vect);


#endif