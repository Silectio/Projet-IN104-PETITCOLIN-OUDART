#ifndef INC_CHECKPOINT_H
#define INC_CHECKPOINT_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "utils.h"

class CheckPoint : public sf::Drawable
{
    public :
    CheckPoint(sf::Vector2f center, unsigned int id); //creates a Checkpoint from a position and its number
    CheckPoint();
    sf::Vector2f getPosition(); //returns Checkpoint's position

    private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    unsigned int id_; //unique id of CheckPoint
    sf::CircleShape circle_; //Shape of the Checkpoint
    sf::Font font_; //Font of text of the CheckPoint
    sf::Text fillingText_; //Text in the Checkpoint

    friend class Game;
};

class FinalCheckPoint : public sf::Drawable
{
    public :
    FinalCheckPoint(sf::Vector2f center);//creates a FinalCheckpoint from a position
    sf::Vector2f getPosition();//returns FinalCheckpoint's position

    private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::CircleShape circle_;//Shape of the FinalCheckPoint

    friend class Game;
};

#endif