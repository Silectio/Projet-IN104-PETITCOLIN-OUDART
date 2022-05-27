#ifndef INC_GameLOGIC_H
#define INC_GameLOGIC_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include "checkpoint.h"
#include "compteur.h"
#include "pod.h"

const unsigned int NUMBER_OF_LAPS = 3;
const float FRICTION_COEFF = 0.85;
const float ROTA_MAX = M_PI/10.;
const sf::Time PHYSICS_TIME_STEP = sf::milliseconds(100);
const std::string IMAGES_PATH = "/home/ensta/IN104/Projet/repository/Images/";
const std::string FONT_PATH = "/home/ensta/IN104/Projet/repository/";

struct GameInfos
{
    std::vector<Pod> pods;
    std::vector<sf::Vector2f> cpPositions;
};

class Game : public sf::Drawable
{
    public :
    Game(); //create a Game with 2 to 8 checkpoints at random positions (they shouldn't overlap)
    Game(std::vector<sf::Vector2f> checkpointsPositions); //create a Game with predefined checkpoints positions

    void addPod(); //can add various arguments here to chose the apparence or the decision making type of the pod
    void updatePhysics(double ratio);
    void updateGraphics(); //change pods sprites positions and rotations depending on the frame time

    Pod pod_player;
    sf::Texture podTexture_player;
    sf::Sprite podSprite_player;
    float pod_player_power = 50;
    bool endgame = false;
    
    private :
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    std::vector<Pod> pods_;
    std::vector<sf::Texture> podsTextures_;
    std::vector<sf::Sprite> podsSprites_;

    sf::Texture texturecircuit_;
    sf::Sprite spritecircuit_;
    
    sf::Sprite Gagnant;
    sf::Text textVictoire;
    
    std::vector<sf::Sprite> Spritecompteur;
    std::vector<sf::Text> Textcompteur;
    sf::Font fontg_;
    sf::Sprite spriteplayercompteur;
    sf::Texture drapeauTex_;
    sf::Sprite drapeauSp_;
    std::vector<sf::Text> textCP_;
    FinalCheckPoint finalCP_;
    std::vector<CheckPoint> otherCPs_;
    std::vector<sf::Vector2f> cpPositions_;

    sf::Time lastFrameTime_;
    sf::Time physicsTime_;  
    
    Compteur compteur_;
    sf::Text textCompt_;
};

#endif