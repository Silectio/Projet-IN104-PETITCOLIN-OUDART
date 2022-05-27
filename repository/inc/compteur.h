#ifndef INC_COMPTEUR_H
#define INC_COMPTEUR_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "utils.h"
#include "pod.h"

class Compteur : public sf::Drawable
{
    public :
    Compteur();
    Compteur(sf::Vector2f center); //creates a compteur from a position
    
    sf::Vector2f getPosition(); //returns Compteur's position

    private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    unsigned int nb_pod_;
    sf::RectangleShape rectangle_; // The outline of the compteur   
    sf::Font font_; // Font of the text
    sf::Text fillingText_; //Text in the compteur

    friend class Game;
};

#endif