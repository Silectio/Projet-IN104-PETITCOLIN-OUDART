#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <cmath>
#include "game.h"
#include <vector>
#include <string>

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Jeu de gros gamos");
    window.setView(sf::View(sf::Rect(0.f,0.f,16000.f,9000.f)));


    //Petite musique sympa

    sf::Music music;
    if (!music.openFromFile("/home/ensta/IN104/Projet/repository/Music/Music.wav"))
        {return -1;} // erreur

    music.setVolume(65);
    music.play();
    





    
    //frame per second 
    float fps = 25;
    double ratio;
    //temps minimal entre deux frame
    sf::Time refreshTime = sf::microseconds(1e6/fps);

    //horloge depuis le début du jeu
    sf::Clock globalClock;
    //horloge réinitialisée à chaque frame
    sf::Clock refreshClock;
    bool rightPressed = false;
    bool leftPressed = false;
    bool upPressed = false;
    bool downPresssed = false;


    // Ici on va instancié l'objet game avec le constructeur par défaut mais on peut remplacer cet appel avec celui commenté en dessous.

    Game myGame;

    // Game myGame({{2000,2000},{8000,5000},{13000,7000}});


    myGame.addPod();

    

    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();

            }


            //Pour déplacer le vaisseau on va définir des booléens qui vont être actualisé à chaque fois qu'on presse ou qu'on relache une touche. Ils serons calculé par la suite juste avant la physique.

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
                {
                    rightPressed = true;
                }
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q)
                {
                    leftPressed = true;
                }
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z)
                {
                    upPressed = true;
                }
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                {
                    downPresssed = true;
                }
                
                
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
                {
                    rightPressed = false;
                }
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q)
                {
                    
                    leftPressed = false;
                }
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z)
                {
                    upPressed = false;
                }
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                {
                    downPresssed = false;
                }
                
            }
        }

        //si on a dépassé le refreshTime depuis la dernière frame
        if (refreshClock.getElapsedTime() >= refreshTime && !myGame.endgame) // On pourrait enlever cette condition avec notre méthode mais elle permet de garder un nombre de fsp + ou - constant ce qui est quand même agréable
        {
            
            ratio = (double)refreshClock.getElapsedTime().asMicroseconds();
            ratio = ratio/100000;
            


            // On va vérifier les entrée du joueur
            if(rightPressed){

                myGame.pod_player.angle_ = myGame.pod_player.angle_ + (0.31415*ratio);
            }

            if(leftPressed){

                myGame.pod_player.angle_ = myGame.pod_player.angle_ - (0.31415*ratio);
            }

            if(upPressed){

                if(myGame.pod_player_power <=(100-10*ratio)){myGame.pod_player_power = myGame.pod_player_power + (10*ratio);}
            }
            if(downPresssed){

                if(myGame.pod_player_power >=10*ratio){myGame.pod_player_power = myGame.pod_player_power - (10*ratio);}
            }


            myGame.updatePhysics(ratio); // On va faire nos calcules
            myGame.updateGraphics();
        
                
                
            
            window.draw(myGame);
            window.display();
            refreshClock.restart();
            
        }
    }

    return 0;
}