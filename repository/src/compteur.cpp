#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "compteur.h"
#include "game.h"
#include "utils.h"
Compteur::Compteur(){};

Compteur::Compteur(sf::Vector2f center)
{
    //Create a specific rectangle at the given center position
    rectangle_ =  sf::RectangleShape(sf::Vector2f(16000,3000));
    setOriginToCenter(rectangle_);
    rectangle_.setPosition(center);
    rectangle_.setFillColor(sf::Color(0,0,0,63));
    rectangle_.setOutlineColor(sf::Color(0,0,0));
    rectangle_.setOutlineThickness(-50);
};

void Compteur::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Draw the rectangle shape of the compteur
    target.draw(rectangle_,states);
};

sf::Vector2f Compteur::getPosition()
{
    //Return the position of the rectangle
    return rectangle_.getPosition();
}