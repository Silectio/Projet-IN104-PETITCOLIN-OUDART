#include "game.h"
#include "checkpoint.h"
#include "compteur.h"
#include "utils.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <string>



Game::Game(std::vector<sf::Vector2f> checkpointsPositions) : finalCP_(checkpointsPositions[0])
{


    // Les explications sont dans le constructeur par défaut et les deux ont essentiellement les mêmes étapes.


    srand(time(NULL));
    otherCPs_.resize(checkpointsPositions.size()-1);
    cpPositions_.resize(checkpointsPositions.size());
    textCP_.resize(checkpointsPositions.size()-1);
    fontg_.loadFromFile("/home/ensta/IN104/Projet/repository/Fredoka-Bold.ttf");
    drapeauTex_.loadFromFile("/home/ensta/IN104/Projet/repository/Images/149804.png");
    drapeauSp_.setTexture(drapeauTex_);
    setOriginToCenter(drapeauSp_);
    scaleByRadius(drapeauSp_, 550);
    drapeauSp_.setPosition(checkpointsPositions[0]);
    
    for(long unsigned int i = 0; i<checkpointsPositions.size()-1;i++){

        std::cout << i << std::endl;
        otherCPs_[i] = CheckPoint(checkpointsPositions[i+1],i+1);

        cpPositions_[i] = checkpointsPositions[i+1];

        textCP_[i].setFillColor(sf::Color(255,255,255,63));
        textCP_[i].setString(std::to_string(i+1));
        textCP_[i].setFont(fontg_);
        textCP_[i].setCharacterSize(500);
        textCP_[i].setFillColor(sf::Color::White);
        setTextCenterPosition(textCP_[i],checkpointsPositions[i+1]);
    }

    cpPositions_.push_back(finalCP_.getPosition());


    backgroundTexture_.loadFromFile("/home/ensta/IN104/Projet/repository/Images/background.png");
    backgroundSprite_.setTexture(backgroundTexture_);
    scaleToMinSize(backgroundSprite_,16000,9000);

    texturecircuit_.loadFromFile("/home/ensta/IN104/Projet/repository/Images/checkeredFlag.png");
    spritecircuit_.setTexture(texturecircuit_);
    scaleToMinSize(spritecircuit_,500,500);
    spritecircuit_.setPosition(200,200);

    compteur_ = Compteur(sf::Vector2f(8000,-100));
    

    textCompt_.setFont(fontg_);
    textCompt_.setCharacterSize(500);
    textCompt_.setFillColor(sf::Color::White);
    textCompt_.setString(std::to_string(0));
    textCompt_.setPosition(14600,300);

    textVictoire.setFont(fontg_);
    textVictoire.setCharacterSize(1500);
    textVictoire.setFillColor(sf::Color::White);
    textVictoire.setString("Victoire");
    textVictoire.setPosition(8000,4500);


    Textcompteur.resize(4);
    for(int i = 0; i < 4; i++){


        Textcompteur[i].setFont(fontg_);
        Textcompteur[i].setCharacterSize(500);
        Textcompteur[i].setFillColor(sf::Color::White);
        Textcompteur[i].setString(std::to_string(0));
        Textcompteur[i].setPosition(1400*(i+1)+500,300);

    }
    
}

Game::Game() : finalCP_({0,0})
{

    // On place le premier checkpoint au hasard sur la fenêtre

    srand(time(NULL));
    float r = rand() / static_cast<float>(RAND_MAX)*14000 +500; // le décalage avec +1500 et +500 est là pour que les checkpoints ne soit pas trop près du bord
    float r2 = rand() / static_cast<float>(RAND_MAX)*6500 +1500; // et dans le cas du y pour que les checkpoints ne soit pas derrière le compteur de tours
    sf::Vector2f v(r,r2);
    finalCP_ = FinalCheckPoint(v);


    otherCPs_.resize(7);
    cpPositions_.resize(7);
    textCP_.resize(7);
    fontg_.loadFromFile("/home/ensta/IN104/Projet/repository/Fredoka-Bold.ttf");

    //On place l'image du drapeau

    drapeauTex_.loadFromFile("/home/ensta/IN104/Projet/repository/Images/149804.png");
    drapeauSp_.setTexture(drapeauTex_);
    setOriginToCenter(drapeauSp_);
    scaleByRadius(drapeauSp_, 550);
    drapeauSp_.setPosition(v);

    //On créer notre compteur 

    compteur_ = Compteur(sf::Vector2f(8000,-100));
    

    //On préfabrique le texte de victoire et le compteur de notre vaisseau

    textCompt_.setFont(fontg_);
    textCompt_.setCharacterSize(500);
    textCompt_.setFillColor(sf::Color::White);
    textCompt_.setString(std::to_string(0));
    textCompt_.setPosition(14600,300);

    textVictoire.setFont(fontg_);
    textVictoire.setCharacterSize(1500);
    textVictoire.setFillColor(sf::Color::White);
    textVictoire.setString("Victoire");
    textVictoire.setPosition(8000,4500);


    //On place les textes pour les compteurs de tours 

    Textcompteur.resize(4);
    for(int i = 0; i < 4; i++){


        Textcompteur[i].setFont(fontg_);
        Textcompteur[i].setCharacterSize(500);
        Textcompteur[i].setFillColor(sf::Color::White);
        Textcompteur[i].setString(std::to_string(0));
        Textcompteur[i].setPosition(1400*(i+1)+500,300);

    }
   
    

    // On place les checkpoints en créant des positions aléatoires et en vérifiant qu'on est pas trop près d'un autre.
    // On aurait pu faire ça plus efficacement en utilisant la distribution en disques de Poisson

    for(int i = 0; i<7;i++){

        int nb = 0;
        r = rand() / static_cast<float>(RAND_MAX)*14000 +500;
        r2 = rand() / static_cast<float>(RAND_MAX)*6500 +1500;

        while(nb < i+1){
        nb = 0;
        r = rand() / static_cast<float>(RAND_MAX)*14000 +500;
        r2 = rand() / static_cast<float>(RAND_MAX)*6500 +1500;
    
        sf::Vector2f v = sf::Vector2f(r,r2)-finalCP_.getPosition();
        if(std::sqrt(v.x*v.x + v.y*v.y)>2500){nb++;}
        

        for(int j = 0;j < i;j++){

            sf::Vector2f v = sf::Vector2f(r,r2)-otherCPs_[j].getPosition();
            if(std::sqrt(v.x*v.x + v.y*v.y)>2500){nb++;}
            
        }}
        

        //une fois placé on ajoute le checkpoints à la liste des CP et on prépare le texte qui le remplira

        otherCPs_[i] = CheckPoint(sf::Vector2f(r,r2),i+1);
        

        cpPositions_[i] = sf::Vector2f(r,r2);

        textCP_[i].setFillColor(sf::Color(255,255,255,63));
        textCP_[i].setString(std::to_string(i+1));
        textCP_[i].setFont(fontg_);
        textCP_[i].setCharacterSize(500);
        textCP_[i].setFillColor(sf::Color::White);
        setTextCenterPosition(textCP_[i],sf::Vector2f(r,r2));
    }

    cpPositions_.push_back(finalCP_.getPosition());

    

    //On place les dernières images fixes

    backgroundTexture_.loadFromFile("/home/ensta/IN104/Projet/repository/Images/background.png");
    backgroundSprite_.setTexture(backgroundTexture_);
    scaleToMinSize(backgroundSprite_,16000,9000);

    texturecircuit_.loadFromFile("/home/ensta/IN104/Projet/repository/Images/checkeredFlag.png");
    spritecircuit_.setTexture(texturecircuit_);
    scaleToMinSize(spritecircuit_,500,500);
    spritecircuit_.setPosition(200,200);
    
}

void Game::addPod()
{

    // On met nos liste de la bonne taille 
    
    pods_.resize(4);
    podsTextures_.resize(4);
    podsSprites_.resize(4);
    Spritecompteur.resize(4);

    // On charge les textures

    podsTextures_[0].loadFromFile("/home/ensta/IN104/Projet/repository/Images/BSGCylon.png");
    podsTextures_[1].loadFromFile("/home/ensta/IN104/Projet/repository/Images/BSGViper.png");
    podsTextures_[2].loadFromFile("/home/ensta/IN104/Projet/repository/Images/NMSFighterG.png");
    podsTextures_[3].loadFromFile("/home/ensta/IN104/Projet/repository/Images/NMSFighterY.png");

    //On places les images pour les compteurs de tours

    for(int i = 0;i < 4;i++){

        Spritecompteur[i].setTexture(podsTextures_[i]);
        setOriginToCenter(Spritecompteur[i]);
        scaleToMinSize(Spritecompteur[i], 400, 400);
        Spritecompteur[i].setPosition(1400*(i+1),600);
        
    }

    // On crée le pod joueur

    podTexture_player.loadFromFile("/home/ensta/IN104/Projet/repository/Images/SWMilleniumFalcon.png");
    podSprite_player.setTexture(podTexture_player);
    setOriginToCenter(podSprite_player);
    scaleToMinSize(podSprite_player, 800, 800);
    pod_player = Pod(sf::Vector2f(14000,1000),90,{0,0});

    //Ainsi que son compteur

    spriteplayercompteur.setTexture(podTexture_player);
    setOriginToCenter(spriteplayercompteur);
    scaleToMinSize(spriteplayercompteur,500,500);
    spriteplayercompteur.setPosition(14000,600);

    //Puis on va placer de façon aléatoire les pods des robots

    for (int i=0; i<4; i++) {

    float r = rand() / static_cast<float>(RAND_MAX)*14000 +500;
    float r2 = rand() / static_cast<float>(RAND_MAX)*6500 +1500;

    podsSprites_[i].setTexture(podsTextures_[i]);
    setOriginToCenter(podsSprites_[i]);
    scaleToMinSize(podsSprites_[i], 800, 800);

    pods_[i] = Pod(sf::Vector2f(r,r2),0,{0,0});

    }
}

void Game::updatePhysics(double ratio)
{
    //Ici on va update la physique
    
    std::vector<Pod> PodsSnapshot = pods_;
    

    for (Pod &pod : pods_)
    {

        /* Nous avons fait le choix de mettre à jour la physique à chaque pas de temps 
        mais pour que les règles du jeu restes cohérente on va modifier la distance parcouru ainsi que l'angle maximal avec un ratio par rapport à ce qui était donné
        soit un pas de physique toutes les 100ms ainsi le ration sera de 1 si on tourne à 10fps 2 à 5 fps et ainsi de suite*/


        Decision d = pod.getDecision({pods_, cpPositions_});

        //on calcule le vecteur c - un puis on renvoie son angle 
        sf::Vector2f veccmun = d.target_ - pod.pos_;
        float psi = vectAngle({veccmun.x,-veccmun.y});

        // On vérifie que celui ci respecte les règles du jeu
        if(std::sqrt((psi-pod.angle_)*(psi-pod.angle_)) > (3.1415/10*ratio)){
        
            if(psi > pod.angle_ || (psi + 3.1415 < pod.angle_)){
            psi = pod.angle_ + (0.31415*ratio);
            
            }else{
                psi = pod.angle_ - (0.31415*ratio);
            }
            
            if(psi>6.283){
                psi = psi - 6.283;
            }
            if(psi < 0){
                psi = psi +6.283;
            }

            veccmun = sf::Vector2f(cos(psi),sin(psi));
        }
        
        pod.angle_ = psi; // On update les valueur du pod
        
        float norme = std::sqrt(veccmun.x*veccmun.x + veccmun.y*veccmun.y);
        veccmun = veccmun / norme;
        float c = 0.85*ratio;


        float powe = std::sqrt(d.power_*d.power_);
        if(d.power_ > 100.0) // On vérifie que la puissance respecte également les règles du jeu
            {powe = 100.0;}
        else{powe = d.power_;}

        sf::Vector2f Vtemp = c*(pod.vel_+ powe*veccmun);
        pod.vel_ = {Vtemp.x/ratio,Vtemp.y/ratio}; // Finalement on fait le calcul de vitesse et de positions
        pod.pos_ = pod.pos_ + Vtemp;

        if(normev(pod.pos_-cpPositions_[pod.nextCP_]) <= 600) // Pour passer les checkpoints on fait simplement un calcule de voir si le pod est passé dessus
        {                                                     // Ce n'est pas parfait mais ça ne pose pas problème dans notre cas à moins d'avoir un taux de rafraichissment très faible 
            pod.nextCP_++;
            if(pod.nextCP_ >= (int)cpPositions_.size()){
                pod.nextCP_ =0;
                pod.lapCount_++;
                for(int v =0;v< 4;v++){

                    Textcompteur[v].setString(std::to_string(pods_[v].lapCount_));
                    if(pods_[v].lapCount_ >= 3){ // Si un pod fait plus de 3 tours il arrète le jeu et deviens le seul à apparaitre

                        endgame = true;
                        Gagnant = podsSprites_[v];

                    }

                }

            }
        }


        


    }

        //Rien de très interessant c'est exactement la même logique mais pour le pod joueur


        sf::Vector2f veccmun(cos(pod_player.angle_),sin(pod_player.angle_));
        float norme = std::sqrt(veccmun.x*veccmun.x + veccmun.y*veccmun.y);
        veccmun = veccmun / norme;
        float c = 0.85*ratio;
        sf::Vector2f Vtemp = c*(pod_player.vel_+ pod_player_power*veccmun);
        pod_player.vel_ = {Vtemp.x/ratio,Vtemp.y/ratio};
        pod_player.pos_ = pod_player.pos_ + Vtemp;

        if(normev(pod_player.pos_-cpPositions_[pod_player.nextCP_]) <= 600)
        {

            if(pod_player.nextCP_ < (int)textCP_.size()){ // On à simplement cette partie en plus pour colorer les textes des checkpoints
            textCP_[pod_player.nextCP_].setFillColor(sf::Color::Red);}
            pod_player.nextCP_++;

            if(pod_player.nextCP_ >= (int)cpPositions_.size()){
                pod_player.nextCP_ =0;
                pod_player.lapCount_++;

                if(pod_player.lapCount_ >= 3){

                    endgame = true;
                    Gagnant = podSprite_player;

                }

                for(long unsigned int i = 0; i< textCP_.size();i++){

                    textCP_[i].setFillColor(sf::Color::White);

                }
                textCompt_.setString(std::to_string(pod_player.lapCount_));
            }
            
        }
        
    
}

void Game::updateGraphics()
{   
    for (int i=0;i<4;++i){

        podsSprites_[i].setPosition(pods_[i].pos_);
        podsSprites_[i].setRotation(radtodeg(pods_[i].angle_));

    }

    podSprite_player.setPosition(pod_player.pos_);
    podSprite_player.setRotation(radtodeg(pod_player.angle_));
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backgroundSprite_);
    if(!endgame){
        target.draw(finalCP_);
        
        for (const auto &cp : otherCPs_)
        {
            
            target.draw(cp, states);
            
        }
        
        target.draw(drapeauSp_);

        for (const auto &text : textCP_)
        {
            
            target.draw(text, states);
            
        }

        
        for (const auto &podSprite : podsSprites_)
        {
            
            target.draw(podSprite, states);
        }
        target.draw(podSprite_player);
        

        target.draw(compteur_);
        target.draw(textCompt_);
        target.draw(spritecircuit_);
        for (const auto &te : Textcompteur)
        {
            
            target.draw(te, states);
            
        }
        for (const auto &sp : Spritecompteur)
        {
            
            target.draw(sp, states);
            
        }
        target.draw(spriteplayercompteur,states);
    }
    else{

        target.draw(Gagnant,states);

        target.draw(textVictoire,states);
        // system("firefox https://www.youtube.com/watch?v=IgyX6K237xI");
        

    }
}